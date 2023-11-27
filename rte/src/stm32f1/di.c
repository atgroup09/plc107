/* @page di.c
 *       Discrete Inputs
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#include "di.h"


/** @brief  Init. DI.
 *  @param  none.
 *  @return none.
 */
void PlcDI_Init(void)
{
    GPIO_InitTypeDef PortDef;
    EXTI_InitTypeDef ExtiDef;
    NVIC_InitTypeDef NvicDef;

    //Enable clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);

	//Configure GPIO
	// GPIOE
    GPIO_StructInit(&PortDef);
    PortDef.GPIO_Pin   = (GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);
    PortDef.GPIO_Mode  = GPIO_Mode_IPD;
    PortDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &PortDef);

    //Connect EXTI-lines to Port pins
    // GPIOE
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource7);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource8);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource9);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource10);

    //Configure EXTI-lines
    EXTI_StructInit(&ExtiDef);
    ExtiDef.EXTI_Line    = EXTI_Line7|EXTI_Line8|EXTI_Line9|EXTI_Line10;
    ExtiDef.EXTI_Mode    = EXTI_Mode_Interrupt;
    ExtiDef.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    ExtiDef.EXTI_LineCmd = ENABLE;
    EXTI_Init(&ExtiDef);

    //Configure NVIC
    // EXTI_Line5-9
    NvicDef.NVIC_IRQChannel                   = EXTI9_5_IRQn;
    NvicDef.NVIC_IRQChannelPreemptionPriority = PLC_NVIC_PPRIO_DI012;
    NvicDef.NVIC_IRQChannelSubPriority        = PLC_NVIC_SPRIO_DI012;
    NvicDef.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NvicDef);
    // EXTI_Line10-15
    NvicDef.NVIC_IRQChannel                   = EXTI15_10_IRQn;
    NvicDef.NVIC_IRQChannelPreemptionPriority = PLC_NVIC_PPRIO_DI3;
    NvicDef.NVIC_IRQChannelSubPriority        = PLC_NVIC_SPRIO_DI3;
    NvicDef.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NvicDef);
}


/** @var Packed DI-values
 *  @note 0..15 bits === 0..15 DI-channels
 */
static uint16_t PlcDI_Values = 0;


/** @brief  Send DI-channel value to Queue (T_DI).
 *  @param  PortIn  - GPIO port.
 *  @param  PinIn   - GPIO pin number.
 *  @param  ChNumIn - DI-channel number.
 *  @return RTOS HiTaskWoken-flag:
 *  @arg    = pdTRUE - if was interrupted high-priority task.
 */
portBASE_TYPE PlcDI_SendValue(GPIO_TypeDef *PortIn, const uint16_t PinIn, const uint16_t ChNumIn)
{
    portBASE_TYPE HiTaskWoken = pdFALSE;

    (void)PlcDI_Values;

    if(PortIn && ChNumIn < PLC_DI_SZ)
    {
        PlcDI_IRQ_t QueueData;
        QueueData.ChNum = ChNumIn;
        QueueData.Val   = GPIO_ReadInputDataBit(PortIn, PinIn);

        //Write Queue (not blocking)
        //send channel value
        xQueueSendToBackFromISR(RTOS_Q_DiIrq, &QueueData, &HiTaskWoken);
    }


/*
    if(PortIn && ChNumIn < PLC_DI_SZ)
    {
        uint8_t Val     = GPIO_ReadInputDataBit(PortIn, PinIn);
        uint8_t ValPrev = BIT_GET_VALUE(PlcDI_Values, ChNumIn);

        //test value
        if(Val != ValPrev)
        {
            PlcDI_IRQ_t QueueData;
            QueueData.ChNum = ChNumIn;
            QueueData.Val   = Val;

            //Write Queue (not blocking)
            //send channel value
            xQueueSendToBackFromISR(RTOS_Q_DiIrq, &QueueData, &HiTaskWoken);

            PlcDI_Values = BIT_SET_VALUE(PlcDI_Values, ChNumIn, Val);
        }
    }
*/
    return (HiTaskWoken);
}


/** @brief  EXTI-line[9-5] interrupts handler.
 *  @param  none.
 *  @return none.
 */
void EXTI9_5_IRQHandler(void)
{
    portBASE_TYPE HiTaskWoken = pdFALSE;

    if(EXTI_GetITStatus(EXTI_Line7) == SET)
    {
        //test and send DI-channel value
        HiTaskWoken = PlcDI_SendValue(GPIOE, GPIO_Pin_7, PLC_DI_00);
        //clear EXTI-line pending bit
        EXTI_ClearITPendingBit(EXTI_Line7);
    }

    if(EXTI_GetITStatus(EXTI_Line8) == SET)
    {
        //test and send DI-channel value
        HiTaskWoken = PlcDI_SendValue(GPIOE, GPIO_Pin_8, PLC_DI_01);
        //clear EXTI-line pending bit
        EXTI_ClearITPendingBit(EXTI_Line8);
    }

    if(EXTI_GetITStatus(EXTI_Line9) == SET)
    {
        //test and send DI-channel value
        HiTaskWoken = PlcDI_SendValue(GPIOE, GPIO_Pin_9, PLC_DI_02);
        //clear EXTI-line pending bit
        EXTI_ClearITPendingBit(EXTI_Line9);
    }

    //fast switch to interrupted task
    if(HiTaskWoken == pdTRUE) taskYIELD();
}


/** @brief  EXTI-line[15-10] interrupts handler.
 *  @param  none.
 *  @return none.
 */
void EXTI15_10_IRQHandler(void)
{
    portBASE_TYPE HiTaskWoken = pdFALSE;

    if(EXTI_GetITStatus(EXTI_Line10) == SET)
    {
        //test and send DI-channel value
        HiTaskWoken = PlcDI_SendValue(GPIOE, GPIO_Pin_10, PLC_DI_03);
        //clear EXTI-line pending bit
        EXTI_ClearITPendingBit(EXTI_Line10);
    }

    //fast switch to interrupted task
    if(HiTaskWoken == pdTRUE) taskYIELD();
}
