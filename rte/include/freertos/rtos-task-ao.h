/* @page rtos-task-ao.h
 *       FreeRTOS Task
 *       Analog outputs
 *       2020-2022
 */

#ifndef RTOS_TASK_AO_H
#define RTOS_TASK_AO_H

#include "config.h"
#include "reg.h"
#include "ao.h"
#include "rtos.h"
#include "rtos-task-log.h"


/** @brief  Set normal value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - normal value:
 *  @arg      = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetNormVal(const uint8_t ChNumIn, const float ValIn);


/** @brief  Set postponed value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - value:
 *  @arg      = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetPostponedVal(const uint8_t ChNumIn, const float ValIn);


/** @brief  Set postponed value (apply all postponed valued).
 *  @param  ValIn - value:
 *  @arg      = 0 - not apply
 *  @arg      = 1 - apply
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetPostponedApply(const uint8_t ValIn);


/** @brief  Set fast value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - fast value:
 *  @arg      = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetFastVal(const uint8_t ChNumIn, const float ValIn);


/** @brief  Set Mode.
 *  @param  ChNumIn - channel number.
 *  @param  ModeIn - Mode:
 *  @arg      = PLC_AO_MODE_NORM
 *  @arg      = PLC_AO_MODE_FAST
 *  @arg      = PLC_AO_MODE_CALB
 *  @arg      = PLC_AO_MODE_OFF
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetMode(const uint8_t ChNumIn, const uint8_t ModeIn);


/** @brief  Set Safe-mode allow.
 *  @param  ChNumIn - channel number.
 *  @param  AllowIn - allow:
 *  @arg      = 0 - not allowed
 *  @arg      = 1 - allowed
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetSafeAllow(const uint8_t ChNumIn, const uint8_t AllowIn);


/** @brief  Set Safe-mode value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - value:
 *  @arg      = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetSafeVal(const uint8_t ChNumIn, const float ValIn);


/** @brief  Set calibrated Lo- or Hi-level (V).
 *  @param  ChNumIn - channel number.
 *  @param  CalbValIn - calibrated level.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetCalbVal(const uint8_t ChNumIn, const float CalbValIn);


/** @brief  Set calibrated Lo-level and current ADC-code.
 *  @param  ChNumIn - channel number.
 *  @param  CmdIn   - command (0, 1).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetCalbLoCmd(const uint8_t ChNumIn, const uint8_t CmdIn);


/** @brief  Set calibrated Hi-level and current ADC-code.
 *  @param  ChNumIn - channel number.
 *  @param  CmdIn   - command (0, 1).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetCalbHiCmd(const uint8_t ChNumIn, const uint8_t CmdIn);


/** @brief  Set calibrated factors.
 *  @param  ChNumIn - channel number.
 *  @param  CmdIn   - command (0, 1).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetCalbCmd(const uint8_t ChNumIn, const uint8_t CmdIn);


/** @brief  Unpack settings.
 *  @param  DataIn - pointer to settings.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_Set(const PlcAO_Set_t *DataIn);


/** @brief  Init. AO-channels.
 *  @param  none.
 *  @return none.
 */
void RTOS_TaskAO_Init(void);


/** @brief  Task `AO`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskAO(void *ParamsIn);


#endif //RTOS_TASK_AO_H
