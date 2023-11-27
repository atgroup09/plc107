/* @page tim2.c
 *       TIM2 driver
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#include "tim2.h"


/** @var  TIM2 status.
 *  @arg    = 0 - off
 *  @arg    = 1 - on
 */
static uint8_t PlcTim2Status = BIT_FALSE;


/** @brief  TIM2 initialization.
 *  @param  none.
 *  @return none.
 */
void PlcTim2_Init(void)
{
    TIM_TimeBaseInitTypeDef TimDef;

    //Enable clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    //TIM base configuration
    TimDef.TIM_CounterMode   = TIM_CounterMode_Up;
    TimDef.TIM_Prescaler     = PLC_TIM2_PRESCALER;
    TimDef.TIM_ClockDivision = 0;
    TimDef.TIM_Period        = PLC_TIM2_PERIOD;
    TIM_TimeBaseInit(TIM2, &TimDef);

    //Enable interrupts
    NVIC_InitTypeDef NvicDef;
    NvicDef.NVIC_IRQChannel                   = TIM2_IRQn;
    NvicDef.NVIC_IRQChannelPreemptionPriority = PLC_NVIC_PPRIO_TIM2;
    NvicDef.NVIC_IRQChannelSubPriority        = PLC_NVIC_SPRIO_TIM2;
    NvicDef.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NvicDef);
    //IRQ
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //TIM_DIER_UIE
    //Stop
    PlcTim2_Stop();
}


/** @brief  TIM2 start.
 *  @param  none.
 *  @return none.
 */
void PlcTim2_Start(void)
{
    if(!PlcTim2Status)
    {
        TIM_SetCounter(TIM2, (uint32_t)0);
        TIM_Cmd(TIM2, ENABLE);
        PlcTim2Status = BIT_TRUE;
    }
}


/** @brief  TIM2 stop.
 *  @param  none.
 *  @return none.
 */
void PlcTim2_Stop(void)
{
    if(PlcTim2Status)
    {
        TIM_Cmd(TIM2, DISABLE);
        TIM_SetCounter(TIM2, (uint32_t)0);
        PlcTim2Status = BIT_FALSE;
    }
}


/** @brief  TIM2 interrupts handler.
 *  @param  none.
 *  @return none.
 *  @note   Implementation of IRQ-handler in rtos-task-do.c
 */
/*
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        ...
    }
}
*/
