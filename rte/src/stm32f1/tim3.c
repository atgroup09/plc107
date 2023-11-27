/* @page tim3.c
 *       TIM3 driver
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#include "tim3.h"


/** @brief  TIM3 initialization.
 *  @param  none.
 *  @return none.
 */
void PlcTim3_Init(void)
{
    TIM_TimeBaseInitTypeDef TimDef;

    //Enable clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    //TIM base configuration
    TimDef.TIM_CounterMode   = TIM_CounterMode_Up;
    TimDef.TIM_Prescaler     = PLC_TIM3_PRESCALER;
    TimDef.TIM_ClockDivision = 0;
    TimDef.TIM_Period        = PLC_TIM3_PERIOD;
    TIM_TimeBaseInit(TIM3, &TimDef);

    //Enable interrupts
    NVIC_InitTypeDef NvicDef;
    NvicDef.NVIC_IRQChannel                   = TIM3_IRQn;
    NvicDef.NVIC_IRQChannelPreemptionPriority = PLC_NVIC_PPRIO_TIM3;
    NvicDef.NVIC_IRQChannelSubPriority        = PLC_NVIC_SPRIO_TIM3;
    NvicDef.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NvicDef);
    //IRQ
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //TIM_DIER_UIE
    //Counter
    TIM_SetCounter(TIM3, (uint32_t)0);
    //Start
    TIM_Cmd(TIM3, ENABLE);
}


/** @brief  TIM3 interrupts handler.
 *  @param  none.
 *  @return none.
 *  @note   Implementation of IRQ-handler in rtos-tim-sys.c
 */
/*
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        ...
    }
}
*/
