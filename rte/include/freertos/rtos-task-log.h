/* @page rtos-log.h
 *       FreeRTOS Task
 *       Debug Log
 *       2020-2022
 */

#ifndef RTOS_TASK_LOG_H
#define RTOS_TASK_LOG_H

#include "config.h"
#include "rtos.h"
#include "usart.h"
#include "xprintf.h"

#if   (DEBUG_LOG_DST == DEBUG_LOG_DST_SWD)
#include "swd-debug.h"
#elif (DEBUG_LOG_DST == DEBUG_LOG_DST_USART)
#include "usart.h"
#endif


/** @def Size of local buffer
 */
#define DEBUG_LOG_BUFF_SZ  100


/** @var Flag of RTOS started
 */
extern uint8_t RTOS_TASK_LOG_STARTED;


/** @brief  Task: LOG.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskLog(void *ParamsIn);


/** @brief  Debug Log.
 *  @param  FmtIn - pointer to string with format specificators.
 *  @param  ...   - arguments of format specificators.
 *  @return None.
 *  @note   !!! DON'T EXECUTE FROM IRQ !!!
 */
void DebugLog(const char *FmtIn, ...);


#endif //RTOS_TASK_LOG_H
