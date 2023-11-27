/* @page rtos-task-ai.h
 *       FreeRTOS Task
 *       AI
 *       2020-2022
 */

#ifndef RTOS_TASK_AI_H
#define RTOS_TASK_AI_H

#include "config.h"
#include "reg.h"
#include "ai.h"
#include "ai-mcu-temp.h"
#include "rtos.h"
#include "rtos-task-log.h"


/** @brief  Turn-off channel.
 *  @param  ChNumIn - channel number.
 *  @return None.
 */
void RTOS_TaskAI_Off(const uint8_t ChNumIn);


/** @brief  Start survey.
 *  @param  ChNumIn - channel number.
 *  @return None.
 */
void RTOS_TaskAI_StartSurvey(const uint8_t ChNumIn);


/** @brief  Start calibration.
 *  @param  ChNumIn - channel number.
 *  @return None.
 */
void RTOS_TaskAI_StartCalb(const uint8_t ChNumIn);


/** @brief  Set Mode.
 *  @param  ChNumIn - channel number.
 *  @param  ModeIn - Mode (see ai.h).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_SetMode(const uint8_t ChNumIn, const uint8_t ModeIn);


/** @brief  Set value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn   - value.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_SetVal(const uint8_t ChNumIn, const float ValIn);


/** @brief  Set status.
 *  @param  ChNumIn  - channel number.
 *  @param  StatusIn - status (see ai.h).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_SetStatus(const uint8_t ChNumIn, const uint8_t StatusIn);


/** @brief  Set calibrated current ADC-code for Lo-level.
 *  @param  ChNumIn - channel number.
 *  @param  CmdIn   - command (0, 1).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_SetCalbLoCmd(const uint8_t ChNumIn, const uint8_t CmdIn);


/** @brief  Set calibrated current ADC-code for Hi-level.
 *  @param  ChNumIn - channel number.
 *  @param  CmdIn   - command (0, 1).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_SetCalbHiCmd(const uint8_t ChNumIn, const uint8_t CmdIn);


/** @brief  Set calibrated factors.
 *  @param  ChNumIn - channel number.
 *  @param  CmdIn   - command (0, 1).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_SetCalbCmd(const uint8_t ChNumIn, const uint8_t CmdIn);


/** @brief  Unpack settings.
 *  @param  DataIn - pointer to settings.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_Set(const PlcAI_Set_t *DataIn);


/** @brief  Init. PT-channels.
 *  @param  none.
 *  @return none.
 */
void RTOS_TaskAI_Init(void);


/** @brief  Task `AI`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskAI(void *ParamsIn);


/** @brief  Restart TimAi.
 *  @param  PeriodIn - timer period (ms).
 *  @return None.
 */
void RTOS_TimAi_Restart(const uint16_t PeriodIn);


/** @brief  Start TimAi.
 *  @param  None.
 *  @return None.
 */
void RTOS_TimAi_Start(void);


/** @brief  Stop TimAi.
 *  @param  None.
 *  @return None.
 */
void RTOS_TimAi_Stop(void);


/** @brief  TimPt-handler (`Read value`).
 *  @param  None.
 *  @return Quantity of AI-channels with mode 'Survey' (read value).
 */
uint16_t RTOS_TimAi_Read(void);


/** @brief  TimAi-handler.
 *  @param  TimerIn - timer.
 *  @return none.
 */
void RTOS_TimAi(TimerHandle_t TimerIn);


#endif //RTOS_TASK_AI_H
