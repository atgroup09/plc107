/* @page ai.c
 *       AI driver (+ MCU-temperature sensor)
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#include "ai.h"


/** @var ADC buffer by channels
 */
static volatile uint16_t PLC_AI_ADC_BUFF[PLC_AI_ADC_BUFF_SZ];


/** @brief  Initialization.
 *  @param  none.
 *  @return none.
 */
void PlcAI_Init(void)
{
    GPIO_InitTypeDef PortDef;
    ADC_InitTypeDef ADCDef;
    DMA_InitTypeDef DMADef;

    //Enable clock
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);

    //GPIO configuration
    // analog mode
    GPIO_StructInit(&PortDef);
    PortDef.GPIO_Pin  = GPIO_Pin_0;
    PortDef.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &PortDef);

    //DMA configuration
    DMA_DeInit(PLC_AI_DMA_CHANNEL);
    DMADef.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMADef.DMA_M2M                = DMA_M2M_Disable;
    DMADef.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
    DMADef.DMA_MemoryBaseAddr     = (uint32_t)&(PLC_AI_ADC_BUFF[0]);
    DMADef.DMA_BufferSize         = (uint32_t)PLC_AI_ADC_BUFF_SZ;
    DMADef.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMADef.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMADef.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMADef.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
    DMADef.DMA_Mode               = DMA_Mode_Circular;
    DMADef.DMA_Priority           = DMA_Priority_High;
    DMA_Init(PLC_AI_DMA_CHANNEL, &DMADef);
    DMA_Cmd(PLC_AI_DMA_CHANNEL, ENABLE);

    //ADC configuration
    ADC_StructInit(&ADCDef);
    ADCDef.ADC_Mode               = ADC_Mode_Independent;
    ADCDef.ADC_ScanConvMode       = ENABLE;
    ADCDef.ADC_ContinuousConvMode = ENABLE;
    ADCDef.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
    ADCDef.ADC_DataAlign          = ADC_DataAlign_Right;
    ADCDef.ADC_NbrOfChannel       = PLC_AI_SZ;
    ADC_Init(ADC1, &ADCDef);
    // regular channels by  rank
    ADC_RegularChannelConfig(ADC1, PLC_AI_00_ADC_CHANNEL, PLC_AI_00_ADC_CHANNEL_RANK, ADC_SampleTime_7Cycles5);
    ADC_RegularChannelConfig(ADC1, PLC_AI_MCU_TEMP_ADC_CHANNEL, PLC_AI_MCU_TEMP_ADC_CHANNEL_RANK, ADC_SampleTime_7Cycles5);
    // enable Temp sensor
    ADC_TempSensorVrefintCmd(ENABLE);
    // enable ADC
    ADC_Cmd(ADC1, ENABLE);
    // enable ADC over DMA
    ADC_DMACmd(ADC1, ENABLE);

    //Calibration
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);

    //Start conversion
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


/** @brief  Get digital level of AI-channel.
 *  @param  ChNumIn - channel number.
 *  @return Digital level:
 *  @arg      = PLC_AI_DIG_MIN ... PLC_AI_DIG_MAX
 *  @note   Current ADC-code
 */
uint16_t PlcAI_GetDigLv(const uint8_t ChNumIn)
{
    uint16_t Res = PLC_AI_DIG_MIN;

    if(ChNumIn < PLC_AI_SZ)
    {
        while(DMA_GetFlagStatus(PLC_AI_DMA_TC_FLAG) == RESET);
        DMA_ClearFlag(PLC_AI_DMA_TC_FLAG);

#if (PLC_AI_ADC_CHANNEL_MEASURES > 1)
        //summ of all measurements of a channel
        uint32_t DigLvSum = 0;
        uint16_t iBuff;

        for(uint16_t i=0; i<PLC_AI_ADC_CHANNEL_MEASURES; i++)
        {
            iBuff     = ((PLC_AI_SZ*i)+ChNumIn);
            DigLvSum += PLC_AI_ADC_BUFF[iBuff];
        }
        //average value
        Res = (uint16_t)(DigLvSum/PLC_AI_ADC_CHANNEL_MEASURES);
#else
        //single value
        Res = PLC_AI_ADC_BUFF[ChNumIn];
#endif //PLC_AI_ADC_CHANNEL_MEASURES
    }

    return ((Res <= PLC_AI_DIG_MAX) ? Res : PLC_AI_DIG_MAX);
}


/** @brief  Get analog level of AI-channel.
 *  @param  DigLvIn - digital level:
 *  @arg      = PLC_AI_DIG_MIN ... PLC_AI_DIG_MAX
 *  @param  KaIn - scale Ka-factor.
 *  @param  KbIn - scale Kb-factor.
 *  @return Analog level (V):
 *  @arg      = PLC_AI_ANA_MIN ... PLC_AI_ANA_MAX
 *  @note   Current V
 */
inline float PlcAI_GetAnaLv(const uint16_t DigLvIn, const float KaIn, const float KbIn)
{
    return (ScaleA(DigLvIn, KaIn, KbIn));
}


/** @brief  Get analog level of AI-channel.
 *  @param  ChNumIn - channel number.
 *  @param  KaIn - scale Ka-factor.
 *  @param  KbIn - scale Kb-factor.
 *  @return Analog level (Om):
 *  @arg      = PLC_AI_ANA_MIN ... PLC_AI_ANA_MAX
 *  @note   Current V
 */
float PlcAI_GetAnaLvByChNum(const uint8_t ChNumIn, const float KaIn, const float KbIn)
{
    float Res = PLC_AI_ANA_DEF;

    if(ChNumIn < PLC_AI_SZ)
    {
        uint16_t DigLv = PlcAI_GetDigLv(ChNumIn);
        Res = PlcAI_GetAnaLv(DigLv, KaIn, KbIn);

#ifdef DEBUG_LOG_AI_ADC
        DebugLog("PlcAI: ChNum=%d DigLv=%d V=%d\n", ChNumIn, DigLv, (uint32_t)Res);
#endif // DEBUG_LOG_AI_ADC
    }

    return (Res);
}
