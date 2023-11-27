/* @page rtos-tim-app.h
 *       FreeRTOS System timer
 *       2020-2022
 */

#include "rtos-tim-app.h"


volatile uint64_t plc_sys_timer = 0;


/** @brief  TIM3 interrupts handler.
 *  @param  none.
 *  @return none.
 */
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        plc_sys_timer++;
    }
}
