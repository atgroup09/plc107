/* @page rtos-task-mbrtu.h
 *       FreeRTOS Task
 *       ModBus RTU
 *       2020-2022
 */

#ifndef RTOS_TASK_MBRTU_H
#define RTOS_TASK_MBRTU_H

#include "config.h"
#include "mbrtu.h"
#include "reg-base.h"
#include "rtos.h"
#include "rtos-task-log.h"


/** @brief  MBRTU Slave.
 *  @param  None.
 *  @return None.
 */
void RTOS_TaskMbRtu_Slave(void);

/** @brief  Task MBRTU.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskMbRtu(void *ParamsIn);


#endif //RTOS_TASK_MBRTU_H
