/* @page main.c
 *       Main
 *       2020-2022
 */

#include "config.h"

#include "sysclock.h"
#include "systick.h"
#include "usart.h"
#include "reg.h"
#include "rtos.h"
#include "rtos-error.h"

#ifdef DEBUG
#include "rtos-task-log.h"
#include "usart3.h"
#endif // DEBUG

#ifdef RTE_MOD_DI
#include "di.h"
#include "rtos-task-di.h"
#endif // RTE_MOD_DI

#ifdef RTE_MOD_DO
#include "do.h"
#include "tim2.h"
#include "rtos-task-do.h"
#endif // RTE_MOD_DO

#ifdef RTE_MOD_MBRTU_SLAVE
#include "usart2.h"
#include "mbrtu.h"
#include "rtos-task-mbrtu.h"
#endif // RTE_MOD_MBRTU_SLAVE

#ifdef RTE_MOD_DATA
#include "rtos-task-data.h"
#endif // RTE_MOD_DATA

#ifdef RTE_MOD_APP_DEBUG
#include "usart1.h"
#endif // RTE_MOD_APP_DEBUG

#ifdef RTE_MOD_APP
#include "plc_app.h"
#include "app.h"
#include "rtos-task-app.h"
#endif // RTE_MOD_APP

#ifdef RTE_MOD_APP_TIM
#include "tim3.h"
#include "rtos-tim-app.h"
#endif // RTE_MOD_APP_TIM


/** @brief  Main function.
 *  @param  none.
 *  @return none.
 */
int main(void)
{
    /** INIT
     */

    NVIC_PriorityGroupConfig(PLC_NVIC_PRIO_GROUP);

    PlcSysClock_Init();

    PLC_SYS_STAT1.Data = 0;


#ifdef DEBUG
    RTOS_TASK_LOG_STARTED = BIT_FALSE;
    PlcUsart3_Init();

    RTOS_MTX_Log = xSemaphoreCreateMutex();
    if(!RTOS_MTX_Log) RTOS_Error(RTOS_ERROR_CREATE_MUTEX, RTOS_MTX_LOG_ID);

    RTOS_Q_Log = xQueueCreate(RTOS_Q_LOG_SZ, RTOS_Q_LOG_ISZ);
    if(!RTOS_Q_Log) RTOS_Error(RTOS_ERROR_CREATE_QUEUE, RTOS_Q_LOG_ID);

    if(xTaskCreate(RTOS_TaskLog, RTOS_T_LOG_NAME, RTOS_T_LOG_STACK_SZ, NULL, RTOS_T_LOG_PRIORITY, NULL) != pdTRUE)
    {
        RTOS_Error(RTOS_ERROR_CREATE_TASK, RTOS_T_LOG_ID);
    }
#endif // DEBUG


#ifdef DEBUG_LOG_MAIN
    DebugLog("=======================================\n");
    DebugLog("HW=%d RTE=%d VAR=%d\n", PLC_HW_CODE, PLC_RTE_VERSION, PLC_HW_VAR);
#endif // DEBUG_LOG_MAIN


#ifdef RTE_MOD_APP
    PLC_SYS_STAT1.Pack.AppInited = PlcApp_Init();
    PlcApp_InitFuncs();

    RTOS_SEMA_App = xSemaphoreCreateBinary();
    if(!RTOS_SEMA_App) RTOS_Error(RTOS_ERROR_CREATE_SEMAPHORE, RTOS_SEMA_APP_ID);

    RTOS_TIM_App = xTimerCreate(RTOS_TIM_APP, RTOS_TIM_APP_TM, pdFALSE, 0, RTOS_TimApp);
    if(!RTOS_TIM_App) RTOS_Error(RTOS_ERROR_CREATE_TIMER, RTOS_TIM_APP_ID);

    if(xTaskCreate(RTOS_TaskApp, RTOS_T_APP_NAME, RTOS_T_APP_STACK_SZ, NULL, RTOS_T_APP_PRIORITY, NULL) != pdTRUE)
    {
        RTOS_Error(RTOS_ERROR_CREATE_TASK, RTOS_T_APP_ID);
    }
#ifdef DEBUG_LOG_MAIN
    DebugLog("APP [INITED]\n");
#endif // DEBUG_LOG_MAIN
#endif // RTE_MOD_APP


#ifdef RTE_MOD_APP_DEBUG
    PlcUsart1_Init();
#endif // RTE_MOD_APP_DEBUG


#ifdef RTE_MOD_APP_TIM
    PlcTim3_Init();
#endif // RTE_MOD_APP_TIM


    REG_Init();
    REG_SetDef();
#ifdef DEBUG_LOG_MAIN
    DebugLog("REG [INITED]\n");
#endif // DEBUG_LOG_MAIN


#ifdef RTE_MOD_DI
    PlcDI_Init();
    RTOS_TaskDI_Init();

    RTOS_MTX_Di = xSemaphoreCreateMutex();
    if(!RTOS_MTX_Di) RTOS_Error(RTOS_ERROR_CREATE_MUTEX, RTOS_MTX_DI_ID);

    RTOS_Q_DiIrq = xQueueCreate(RTOS_Q_DI_IRQ_SZ, RTOS_Q_DI_IRQ_ISZ);
    if(!RTOS_Q_DiIrq) RTOS_Error(RTOS_ERROR_CREATE_QUEUE, RTOS_Q_DI_IRQ_ID);

    RTOS_Q_DiSet = xQueueCreate(RTOS_Q_DI_SET_SZ, RTOS_Q_DI_SET_ISZ);
    if(!RTOS_Q_DiSet) RTOS_Error(RTOS_ERROR_CREATE_QUEUE, RTOS_Q_DI_SET_ID);

    RTOS_Q_DataDi = xQueueCreate(RTOS_Q_DATA_DI_SZ, RTOS_Q_DATA_DI_ISZ);
    if(!RTOS_Q_DataDi) RTOS_Error(RTOS_ERROR_CREATE_QUEUE, RTOS_Q_DATA_DI_ID);

    RTOS_TIM_DiTach = xTimerCreate(RTOS_TIM_DI_TACH, RTOS_TIM_DI_TACH_TM, pdTRUE, 0, RTOS_TimDiTach);
    if(!RTOS_TIM_DiTach) RTOS_Error(RTOS_ERROR_CREATE_TIMER, RTOS_TIM_DI_TACH_ID);

    if(xTaskCreate(RTOS_TaskDI_IRQ, RTOS_T_DI_IRQ_NAME, RTOS_T_DI_IRQ_STACK_SZ, NULL, RTOS_T_DI_IRQ_PRIORITY, NULL) != pdTRUE)
    {
        RTOS_Error(RTOS_ERROR_CREATE_TASK, RTOS_T_DI_IRQ_ID);
    }

    if(xTaskCreate(RTOS_TaskDI_Set, RTOS_T_DI_SET_NAME, RTOS_T_DI_SET_STACK_SZ, NULL, RTOS_T_DI_SET_PRIORITY, NULL) != pdTRUE)
    {
        RTOS_Error(RTOS_ERROR_CREATE_TASK, RTOS_T_DI_SET_ID);
    }
#ifdef DEBUG_LOG_MAIN
    DebugLog("DI [INITED]\n");
#endif // DEBUG_LOG_MAIN
#endif // RTE_MOD_DI


#ifdef RTE_MOD_DO
    PlcDO_Init();
    PlcTim2_Init();
    RTOS_TaskDO_Init();

    RTOS_Q_DoSet = xQueueCreate(RTOS_Q_DO_SET_SZ, RTOS_Q_DO_SET_ISZ);
    if(!RTOS_Q_DoSet) RTOS_Error(RTOS_ERROR_CREATE_QUEUE, RTOS_Q_DO_SET_ID);

    RTOS_Q_DataDo = xQueueCreate(RTOS_Q_DATA_DO_SZ, RTOS_Q_DATA_DO_ISZ);
    if(!RTOS_Q_DataDo) RTOS_Error(RTOS_ERROR_CREATE_QUEUE, RTOS_Q_DATA_DO_ID);

    if(xTaskCreate(RTOS_TaskDO, RTOS_T_DO_NAME, RTOS_T_DO_STACK_SZ, NULL, RTOS_T_DO_PRIORITY, NULL) != pdTRUE)
    {
        RTOS_Error(RTOS_ERROR_CREATE_TASK, RTOS_T_DO_ID);
    }
#ifdef DEBUG_LOG_MAIN
    DebugLog("DO [INITED]\n");
#endif // DEBUG_LOG_MAIN
#endif // RTE_MOD_DO


#ifdef RTE_MOD_MBRTU_SLAVE
    MBRTU_InitDef(&MBRTU_COM, USART2, PLC_MBRTU_SLAVE_ADDR, PLC_USART2_DE_PORT, PLC_USART2_DE_PIN, PlcUsart2_Init);
    PlcUsart2_Init();

    RTOS_MTX_MbTables = xSemaphoreCreateMutex();
    if(!RTOS_MTX_MbTables) RTOS_Error(RTOS_ERROR_CREATE_MUTEX, RTOS_MTX_MBTABLES_ID);

    RTOS_Q_MbRtuRx = xQueueCreate(RTOS_Q_MBRTU_RX_SZ, RTOS_Q_MBRTU_RX_ISZ);
    if(!RTOS_Q_MbRtuRx) RTOS_Error(RTOS_ERROR_CREATE_QUEUE, RTOS_Q_MBRTU_RX_ID);

    RTOS_Q_MbRtuSet = xQueueCreate(RTOS_Q_MBRTU_SET_SZ, RTOS_Q_MBRTU_SET_ISZ);
    if(!RTOS_Q_MbRtuSet) RTOS_Error(RTOS_ERROR_CREATE_QUEUE, RTOS_Q_MBRTU_SET_ID);

    if(xTaskCreate(RTOS_TaskMbRtu, RTOS_T_MBRTU_NAME, RTOS_T_MBRTU_STACK_SZ, NULL, RTOS_T_MBRTU_PRIORITY, NULL) != pdTRUE)
    {
        RTOS_Error(RTOS_ERROR_CREATE_TASK, RTOS_T_MBRTU_ID);
    }
#ifdef DEBUG_LOG_MAIN
    DebugLog("MBRTU [INITED]\n");
#endif // DEBUG_LOG_MAIN
#endif // RTE_MOD_MBRTU_SLAVE


#ifdef RTE_MOD_REG_MONITOR
    RTOS_Q_DataRegMonitor = xQueueCreate(RTOS_Q_DATA_REG_MONITOR_SZ, RTOS_Q_DATA_REG_MONITOR_ISZ);
    if(!RTOS_Q_DataRegMonitor) RTOS_Error(RTOS_ERROR_CREATE_QUEUE, RTOS_Q_DATA_REG_MONITOR_ID);
#endif // RTE_MOD_REG_MONITOR


#ifdef RTE_MOD_DATA
    if(xTaskCreate(RTOS_TaskData, RTOS_T_DATA_NAME, RTOS_T_DATA_STACK_SZ, NULL, RTOS_T_DATA_PRIORITY, NULL) != pdTRUE)
    {
        RTOS_Error(RTOS_ERROR_CREATE_TASK, RTOS_T_DATA_ID);
    }
#ifdef DEBUG_LOG_MAIN
    DebugLog("DATA [INITED]\n");
#endif // DEBUG_LOG_MAIN
#endif // RTE_MOD_DATA


    /** PRESTART
     */

    PlcSysTick_Init();


    /** START RTOS SCHEDULER
     */

#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS [START]\n");
#endif // DEBUG

#ifdef DEBUG
    RTOS_TASK_LOG_STARTED = BIT_TRUE;
#endif // DEBUG

    vTaskStartScheduler();


    /** RTOS Scheduler doesn't start
     */

#ifdef DEBUG
    RTOS_TASK_LOG_STARTED = BIT_FALSE;
#endif // DEBUG

    RTOS_Error(RTOS_ERROR_START_SCHED, RTOS_TARGET_DUMMY);

    return (0);
}
