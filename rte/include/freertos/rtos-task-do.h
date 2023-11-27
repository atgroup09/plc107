/* @page rtos-task-do.h
 *       FreeRTOS Task
 *       Discrete outputs
 *       2020-2022
 */

#ifndef RTOS_TASK_DO_H
#define RTOS_TASK_DO_H

#include "config.h"
#include "tim2.h"
#include "reg.h"
#include "do.h"
#include "rtos.h"
#include "rtos-task-log.h"


/** @brief  Calc PWM length of TRUE-value.
 *  @param  PeriodIn     - period (ms).
 *  @param  FillFactorIn - fill factor (%).
 *  @return Length of TRUE-value (us).
 *  @note
 *          Len1 = ((PeriodIn*1000)/100)*FillFactorIn
 */
uint64_t RTOS_TaskDO_CalcPwmLen1(const uint32_t PeriodIn, const float FillFactorIn);


/** @brief  Calc PWM length of FALSE-value.
 *  @param  PeriodIn - period (ms).
 *  @param  Len1In   - length of TRUE-value (us).
 *  @return Length of FALSE-value (us).
 *  @note
 *          Len0 = (PeriodIn*1000)-Len1In
 */
uint64_t RTOS_TaskDO_CalcPwmLen0(const uint32_t PeriodIn, const uint64_t Len1In);


/** @brief  Refresh PWM.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_RefreshPwm(const uint8_t ChNumIn);


/** @brief  Set output value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - value:
 *  @arg      = 0
 *  @arg      = 1
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetVal(const uint8_t ChNumIn, const uint8_t ValIn);


/** @brief  Set normal value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - normal value:
 *  @arg      = 0
 *  @arg      = 1
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetNormVal(const uint8_t ChNumIn, const uint8_t ValIn);


/** @brief  Set postponed value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - value:
 *  @arg      = 0
 *  @arg      = 1
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetPostponedVal(const uint8_t ChNumIn, const uint8_t ValIn);


/** @brief  Set postponed value (apply all postponed valued).
 *  @param  ValIn - value:
 *  @arg      = 0 - not apply
 *  @arg      = 1 - apply
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetPostponedApply(const uint8_t ValIn);


/** @brief  Set fast value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - fast value:
 *  @arg      = 0
 *  @arg      = 1
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetFastVal(const uint8_t ChNumIn, const uint8_t ValIn);


/** @brief  Set PWM fill factor.
 *  @param  ChNumIn - channel number.
 *  @param  FillFactorIn - fill factor (%).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetPwmFillFactor(const uint8_t ChNumIn, const float FillFactorIn);


/** @brief  Set PWM period.
 *  @param  ChNumIn - channel number.
 *  @param  PeriodIn - period (ms).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetPwmPeriod(const uint8_t ChNumIn, const uint32_t PeriodIn);


/** @brief  Set PWM allow.
 *  @param  ChNumIn - channel number.
 *  @param  AllowIn - allow:
 *  @arg      = 0 - not allowed
 *  @arg      = 1 - allowed
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetPwmAllow(const uint8_t ChNumIn, const uint8_t AllowIn);


/** @brief  Set Mode.
 *  @param  ChNumIn - channel number.
 *  @param  ModeIn - Mode:
 *  @arg      = PLC_DO_MODE_NORM
 *  @arg      = PLC_DO_MODE_FAST
 *  @arg      = PLC_DO_MODE_PWM
 *  @arg      = PLC_DO_MODE_OFF
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetMode(const uint8_t ChNumIn, const uint8_t ModeIn);


/** @brief  Set Safe-mode allow.
 *  @param  ChNumIn - channel number.
 *  @param  AllowIn - allow:
 *  @arg      = 0 - not allowed
 *  @arg      = 1 - allowed
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetSafeAllow(const uint8_t ChNumIn, const uint8_t AllowIn);


/** @brief  Set Safe-mode value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - value:
 *  @arg      = 0
 *  @arg      = 1
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetSafeVal(const uint8_t ChNumIn, const uint8_t ValIn);


/** @brief  Unpack settings.
 *  @param  DataIn - pointer to settings.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_Set(const PlcDO_Set_t *DataIn);


/** @brief  Init. DO-channels.
 *  @param  none.
 *  @return none.
 */
void RTOS_TaskDO_Init(void);


/** @brief  Task `DO`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskDO(void *ParamsIn);


#endif //RTOS_TASK_DO_H
