/* @page led.h
 *       LED Driver
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

/** @note
 *        PE15 - Led RUN/NET
 */

#ifndef PLC_LED_H
#define PLC_LED_H

#include "config.h"
#include "do.h"


/** @def GPIO defines
 */
#define PLC_LED_RCC                    RCC_APB2Periph_GPIOE
#define PLC_LED_PORT                   GPIOE

#define PLC_LED1_PIN                   GPIO_Pin_15
#define PLC_LED1_PIN_MODE              PLC_DO_PP


/** @def LED blink-mode
 *       pulse duration, msec
 */
#define PLC_LED_PULSE_LEN              (uint16_t)100


/** @brief  LED initialization.
 *  @param  none.
 *  @return none.
 */
void PlcLed_Init(void);


#endif //PLC_LED_H
