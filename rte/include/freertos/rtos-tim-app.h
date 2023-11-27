/* @page rtos-tim-app.h
 *       FreeRTOS System timer
 *       2020-2022
 */

#ifndef RTOS_TIM_APP_H
#define RTOS_TIM_APP_H

#include "config.h"
#include "rtos.h"


extern volatile uint64_t plc_sys_timer;

#define PLC_TIMER(t)        (plc_sys_timer - t)
#define PLC_CLEAR_TIMER(t)  (t = plc_sys_timer)


#endif //RTOS_TIM_APP_H
