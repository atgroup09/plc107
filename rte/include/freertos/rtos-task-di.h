/* @page rtos-task-di.h
 *       FreeRTOS Task
 *       Discrete inputs
 *       2020-2022
 */

#ifndef RTOS_TASK_DI_H
#define RTOS_TASK_DI_H

#include "config.h"
#include "reg.h"
#include "di.h"
#include "rtos.h"
#include "rtos-task-log.h"


/** @brief  Start Tachometer reloading timer.
 *  @param  None.
 *  @return None.
 */
void RTOS_TimDiTach_Start(void);


/** @brief  Stop Tachometer reloading timer.
 *  @param  None.
 *  @return None.
 */
void RTOS_TimDiTach_Stop(void);


/** @brief  Refresh Tachometer channel.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_RefreshTach(const uint8_t ChNumIn);


/** @brief  Tachometer setpoint.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_TachSetpoint(const uint8_t ChNumIn);


/** @brief  Tachometer reset.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_TachReset(const uint8_t ChNumIn);


/** @brief  Tachometer counter.
 *  @param  ChNumIn   - channel number.
 *  @param  ValIn     - channel value.
 *  @param  ValPrevIn - channel previous value.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_TachCntr(const uint8_t ChNumIn, const uint8_t ValIn, const uint8_t ValPrevIn);


/** @brief  Counter setpoint.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_CntrSetpoint(const uint8_t ChNumIn);


/** @brief  Counter reset.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_CntrReset(const uint8_t ChNumIn);


/** @brief  Counter.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn   - channel value.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_Cntr(const uint8_t ChNumIn, const uint8_t ValIn);


/** @brief  Incremental encoder (counter).
 *  @param  ChNumIn - channel number.
 *  @param  ValIn   - channel value.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_Inc1(const uint8_t ChNumIn, const uint8_t ValIn);


/** @brief  Incremental encoder (counter + tachometer).
 *  @param  ChNumIn - channel number.
 *  @param  ValIn   - channel value.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_Inc2(const uint8_t ChNumIn, const uint8_t ValIn);


/** @brief  Test pair dependent.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - the channel is not dependent
 *  @arg      = 1 - the channel is dependent
 */
uint8_t RTOS_TaskDI_TestPair(const uint8_t ChNumIn);


/** @brief  Set tachometer setpoint and allow to work by setpoint.
 *  @param  ChNumIn - channel number.
 *  @param  SetPointIn - setpoint value.
 *  @param  SetPointAllowIn - allow to work by the setpoint.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_SetTachSetpoint(const uint8_t ChNumIn, const uint16_t SetPointIn, const uint8_t SetPointAllowIn);


/** @brief  Set counter setpoint and allow to work by setpoint.
 *  @param  ChNumIn - channel number.
 *  @param  SetPointIn - setpoint value.
 *  @param  SetPointAllowIn - allow to work by the setpoint.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_SetCntrSetpoint(const uint8_t ChNumIn, const uint32_t SetPointIn, const uint8_t SetPointAllowIn);


/** @brief  Set reset.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn   - value of command.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_SetReset(const uint8_t ChNumIn, const uint8_t ValIn);


/** @brief  Set mode.
 *  @param  ChNumIn - channel number.
 *  @param  ModeIn  - channel mode:
 *  @arg      = 0 - normal
 *  @arg      = 1 - counter
 *  @arg      = 2 - tachometer
 *  @arg      = 3 - incremental encoder (counter)
 *  @arg      = 4 - incremental encoder (counter + tachometer)
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_SetMode(const uint8_t ChNumIn, const uint8_t ModeIn);


/** @brief  Task `DI Settings`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskDI_Set(void *ParamsIn);


/** @brief  Task `DI IRQ`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskDI_IRQ(void *ParamsIn);


/** @brief  Unpack data from Timer-handler `DI.Tachometer.reload`.
 *  @param  None.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_TIM(void);


/** @brief  Init. DI-channels.
 *  @param  none.
 *  @return none.
 */
void RTOS_TaskDI_Init(void);


/** @brief  Timer-handler `Tachometer reloading`.
 *  @param  TimerIn - timer.
 *  @return none.
 */
void RTOS_TimDiTach(TimerHandle_t TimerIn);


#endif //RTOS_TASK_DI_H
