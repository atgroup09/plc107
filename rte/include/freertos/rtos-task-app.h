/* @page rtos-task-app.h
 *       FreeRTOS Task
 *       TaskApp
 *       2020-2022
 */

#ifndef RTOS_TASK_APP_H
#define RTOS_TASK_APP_H

#include "config.h"

#ifdef RTE_MOD_DO
#include "do.h"
#endif // RTE_MOD_DO

#ifdef RTE_MOD_AO
#include "ao.h"
#endif // RTE_MOD_AO

#include "plc_app.h"
#include "plc_debug.h"
#include "reg.h"
#include "rtos.h"
#include "rtos-task-log.h"


/** @brief  Init. TimApp.
 *  @param  None.
 *  @return None.
 */
void RTOS_TaskApp_InitTimApp(void);


/** @brief  Task `Application`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 */
void RTOS_TaskApp(void *ParamsIn);


/** @brief  Timer-handler.
 *  @param  TimerIn - timer.
 *  @return none.
 */
void RTOS_TimApp(TimerHandle_t TimerIn);


#endif //RTOS_TASK_APP_H
