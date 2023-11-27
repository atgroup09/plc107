/* @page tim2.h
 *       TIM2 driver
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

/** @note TIM2
 *        DO PWM
 *        period = 100 us (10 kHz) minimum
 *        tick   = 100000Hz = 10us
 */

#ifndef PLC_TIM2_H
#define PLC_TIM2_H

#include "config.h"
#include "sysclock.h"
#include "rtos.h"
#include "rtos-task-log.h"


/** @def TIM tick frequency (Hz)
 */
#define PLC_TIM2_HZ                    (uint32_t)100000


/** #def TIM prescaler
 *       PSC
 */
#define PLC_TIM2_PRESCALER             (uint16_t)(PLC_APB1_TCLK_FREQ/PLC_TIM2_HZ)


/** @def TIM IRQ period (quantity of ticks)
 *       auto-reload period
 *       ARR
 */
#define PLC_TIM2_PERIOD                (uint32_t)10


/** @def TIM IRQ period (us)
 */
#define PLC_TIM2_PERIOD_US             (uint8_t)100


/** @brief  TIM2 initialization.
 *  @param  none.
 *  @return none.
 */
void PlcTim2_Init(void);


/** @brief  TIM2 start.
 *  @param  none.
 *  @return none.
 */
void PlcTim2_Start(void);


/** @brief  TIM2 stop.
 *  @param  none.
 *  @return none.
 */
void PlcTim2_Stop(void);


#endif //PLC_TIM2_H
