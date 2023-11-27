/* @page rtos-error.h
 *       FreeRTOS Error
 *       defines and handlers
 *       2020, lamsystems-it.ru
 */

#ifndef RTOS_ERROR_H
#define RTOS_ERROR_H

#include "rtos-task-log.h"


/** @def RTOS Error codes
 */
#define RTOS_ERROR_CREATE_QUEUE        1
#define RTOS_ERROR_CREATE_MUTEX        2
#define RTOS_ERROR_CREATE_SEMAPHORE    3
#define RTOS_ERROR_CREATE_TASK         4
#define RTOS_ERROR_CREATE_TIMER        5
#define RTOS_ERROR_START_SCHED         6
#define RTOS_MODE_DEFAULTS             10

#define RTOS_TARGET_DUMMY              0



/** @brief  Handler of error init. RTOS.
 *  @param  ErrIn      - error code.
 *  @param  TargetIdIn - ID of target (task, queue, mutex, ...).
 *  @return none.
 */
void RTOS_Error(const uint8_t ErrIn, const uint8_t TargetIdIn);


#endif //RTOS_ERROR_H
