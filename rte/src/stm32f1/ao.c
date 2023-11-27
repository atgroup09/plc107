/* @page ao.c
 *       AO driver
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#include "ao.h"


uint8_t PLC_AO_POSTPONED;


/** @brief  AO initialization.
 *  @param  none.
 *  @return none.
 */
void PlcAO_Init(void)
{
    GPIO_InitTypeDef PortDef;

    //Enable clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);

    //GPIO configuration
    // analog mode
    GPIO_StructInit(&PortDef);
    PortDef.GPIO_Pin  = GPIO_Pin_4;
    PortDef.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &PortDef);

    //DAC configuration
    DAC_DeInit();
    DAC_Cmd(PLC_AO_00_DAC_CHANNEL, ENABLE);
}


/** @brief  Set digital level to AO.
 *  @param  ChNumIn - channel number.
 *  @param  DigLvIn - digital level:
 *  @arg      = PLC_AO_DIG_MIN ... PLC_AO_DIG_MAX
 *  @return Result:
 *  @arg      = 0 - not set
 *  @arg      = 1 - set
 */
uint8_t PlcAO_SetDigLv(const uint8_t ChNumIn, const uint16_t DigLvIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        uint16_t DigLv = ((DigLvIn <= PLC_AO_DIG_MAX) ? DigLvIn : PLC_AO_DIG_MAX);

#ifdef DEBUG_LOG_AO
        DebugLog("Ao: ch=%d DigLv=%d\0", ChNumIn, DigLv);
#endif // DEBUG_LOG_AO

        DAC_SetChannel1Data(DAC_Align_12b_R, DigLv);

#ifdef DEBUG_LOG_AO
        DebugLog(" [OK]\n");
#endif // DEBUG_LOG_AO

        return (BIT_TRUE);
    }

    return (BIT_FALSE);
}


/** @brief  Set analog level to AO.
 *  @param  ChNumIn - channel number.
 *  @param  AnaLvIn - analog level:
 *  @arg      = PLC_AO_ANA_MIN ... PLC_AO_ANA_MAX
 *  @param  KaIn - scale Ka-factor.
 *  @param  KbIn - scale Kb-factor.
 *  @return Result:
 *  @arg      = 0 - not set
 *  @arg      = 1 - set
 */
uint8_t PlcAO_SetAnaLv(const uint8_t ChNumIn, const float AnaLvIn, const float KaIn, const float KbIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        float AnaLv = ((AnaLvIn >= PLC_AO_ANA_MIN) ? AnaLvIn : PLC_AO_ANA_MIN);
        if(AnaLv > PLC_AO_ANA_MAX) AnaLv = PLC_AO_ANA_MAX;

        uint16_t DigLv = (uint16_t)ScaleA(AnaLv, KaIn, KbIn);
        //float    Ana   = (((AnaLv - KbIn)/KaIn)/1.05);
        //uint16_t DigLv = (uint16_t)((Ana*PLC_AO_DIG_MAX_FLO)/PLC_AO_ANA_MAX);

        return (PlcAO_SetDigLv(ChNumIn, DigLv));
    }

    return (BIT_FALSE);
}
