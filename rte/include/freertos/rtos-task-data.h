/* @page rtos-task-data.h
 *       FreeRTOS Task
 *       Data manager
 *       2020-2022
 */

#ifndef RTOS_TASK_DATA_H
#define RTOS_TASK_DATA_H

#include "config.h"
#include "reg.h"
#include "rtos.h"

#ifdef DEBUG
#include "rtos-task-log.h"
#endif // DEBUG


#ifdef RTE_MOD_DI

#include "di.h"

/** @brief  Send DI settings.
 *  @param  RegIn - pointer to register.
 *  @param  SetIdIn  - settings ID.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_DiSet(REG_t *RegIn, const uint8_t SetIdIn);

/** @brief  Send DI settings (bit-pack).
 *  @param  RegIn - pointer to register.
 *  @param  SetIdIn - settings ID.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_DiSetBitPack(REG_t *RegIn, const uint8_t SetIdIn);

/** @brief  Unpack DI-channel data.
 *  @param  DataIn - pointer to data.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_Di(const PlcDI_t *DataIn);

#endif // RTE_MOD_DI


#ifdef RTE_MOD_DO

#include "do.h"

/** @brief  Send DO settings (INT).
 *  @param  RegIn - pointer to register.
 *  @param  SetIdIn  - settings ID.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_DoSetInt(REG_t *RegIn, const uint8_t SetIdIn);

/** @brief  Send DO settings (REAL).
 *  @param  RegIn - pointer to register.
 *  @param  SetIdIn  - settings ID.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_DoSetReal(REG_t *RegIn, const uint8_t SetIdIn);

/** @brief  Send DO settings (bit-pack).
 *  @param  RegIn - pointer to register.
 *  @param  SetIdIn - settings ID.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_DoSetBitPack(REG_t *RegIn, const uint8_t SetIdIn);

/** @brief  Unpack DO-channel data.
 *  @param  DataIn - pointer to data.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_Do(const PlcDO_Set_t *DataIn);

#endif // RTE_MOD_DO


#ifdef RTE_MOD_REG_MONITOR

/** @brief  Unpack updated register.
 *  @param  IDxIn - register IDx (position in REGS).
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_RegMonitor(const uint16_t IDxIn);

#endif // RTE_MOD_REG_MONITOR


/** @brief  Task `Data manager`
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskData(void *ParamsIn);

#endif //RTOS_TASK_DATA_H
