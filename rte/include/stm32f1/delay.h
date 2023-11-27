/* @page delay.h
 *       Delay functions
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020
 */

#ifndef DELAY_H
#define DELAY_H

#include "config.h"


/** @def DELAY
 *       settings
 */
#define DELAY_SYSTICK                   //use SysTick, otherwise will be used TIMn (comment the define to disable)
#define DELAY_TIM      TIM7             //use TIMn for delay
#define DELAY_TIM_IRQ  TIM7_IRQHandler  //use TIMn_IRQHandler


/** @brief   Init. Delay.
 *  @param   none.
 *  @return  none.
 */
void DelayInit(void);


/** @brief   Delay in microseconds.
 *  @param   UsIn - microseconds (16-bit value).
 *  @return  none.
 */
void DelayUs(const uint16_t UsIn);


/** @brief   Delay in milliseconds.
 *  @param   MsIn - milliseconds (16-bit value).
 *  @return  none.
 */
void DelayMs(const uint16_t MsIn);


/** @brief   Delay in seconds.
 *  @param   SecIn - seconds (16-bit value).
 *  @return  none.
 */
void DelaySec(const uint16_t SecIn);


/** @brief  Delay TIM start.
 *  @param  none.
 *  @return none.
 */
void DelayTim_Start(void);


/** @brief  Delay TIM stop.
 *  @param  none.
 *  @return none.
 */
void DelayTim_Stop(void);


#endif //DELAY_H
