/* @page rtos.c
 *       FreeRTOS
 *       defines
 *       2020-2022
 */

#include "rtos.h"


#ifdef DEBUG
QueueHandle_t RTOS_Q_Log;
SemaphoreHandle_t RTOS_MTX_Log;
#endif // DEBUG


#ifdef RTE_MOD_DI
QueueHandle_t RTOS_Q_DiIrq;
QueueHandle_t RTOS_Q_DiSet;
QueueHandle_t RTOS_Q_DataDi;
SemaphoreHandle_t RTOS_MTX_Di;
TimerHandle_t RTOS_TIM_DiTach;
#endif // RTE_MOD_DI


#ifdef RTE_MOD_DO
QueueHandle_t RTOS_Q_DoSet;
QueueHandle_t RTOS_Q_DataDo;
#endif // RTE_MOD_DO


#ifdef RTE_MOD_MBRTU_SLAVE
QueueHandle_t RTOS_Q_MbRtuRx;
QueueHandle_t RTOS_Q_MbRtuSet;
SemaphoreHandle_t RTOS_MTX_MbTables;
#endif // RTE_MOD_MBRTU_SLAVE


#ifdef RTE_MOD_APP
SemaphoreHandle_t RTOS_SEMA_App;
TimerHandle_t RTOS_TIM_App;
#endif // RTE_MOD_APP


#ifdef RTE_MOD_APP_DEBUG

#endif // RTE_MOD_APP_DEBUG


#ifdef RTE_MOD_REG_MONITOR
QueueHandle_t RTOS_Q_DataRegMonitor;
#endif // RTE_MOD_REG_MONITOR
