/* @page rtos-task-led.h
 *       FreeRTOS Task
 *       Led RUN/NET
 *       2020-2022
 */

#ifndef RTOS_TASK_LED_H
#define RTOS_TASK_LED_H

#include "led.h"
#include "rtos.h"
#include "rtos-task-log.h"


/** @brief  Task `Led`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 */
void RTOS_TaskLed(void *ParamsIn);


#endif //RTOS_TASK_LED_H
