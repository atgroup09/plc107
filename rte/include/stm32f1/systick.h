/* @page systick.h
 *       SysTick initialization
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020-2022
 */

/** @note SYSTICK
 *
 *        FreeRTOS tick
 *
 *        1-tick = 1000Hz = 1000us = 1ms
 */

#ifndef PLC_SYSTICK_H
#define PLC_SYSTICK_H

#include "config.h"


/** @def SysTick freq.
 *       1kHz = 1000Hz = 1ms
 *       1MHz = 1000000Hz = 1us
 */
#define PLC_SYSTICK_FREQ_HZ            1000   //Hz


/** @brief   SysTick initialization.
 *  @param   none.
 *  @return  none.
 */
void PlcSysTick_Init(void);


#endif //PLC_SYSTICK_H
