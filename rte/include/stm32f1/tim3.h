/* @page tim3.h
 *       TIM3 driver
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

/** @note TIM3
 *        plc_sys_timer
 *        tick = 10000Hz = 100us
 */

#ifndef PLC_TIM3_H
#define PLC_TIM3_H

#include "config.h"
#include "sysclock.h"


/** @def TIM tick frequency (Hz)
 */
#define PLC_TIM3_HZ                    (uint32_t)10000


/** #def TIM prescaler
 *       PSC
 */
#define PLC_TIM3_PRESCALER             (uint16_t)(PLC_APB1_PCLK_FREQ/PLC_TIM3_HZ)


/** @def TIM IRQ period (quantity of ticks)
 *       auto-reload period
 *       ARR
 */
#define PLC_TIM3_PERIOD                (uint32_t)10


/** @def TIM IRQ period (us)
 */
#define PLC_TIM3_PERIOD_US             (uint16_t)1000


/** @brief  TIM3 initialization.
 *  @param  none.
 *  @return none.
 */
void PlcTim3_Init(void);


#endif //PLC_TIM3_H
