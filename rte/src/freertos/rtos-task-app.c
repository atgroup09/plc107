/* @page rtos-task-app.h
 *       FreeRTOS Task
 *       TaskApp
 *       2020-2022
 */

#include "rtos-task-app.h"


/** @brief  Init. TimApp.
 *  @param  None.
 *  @return None.
 */
void RTOS_TaskApp_InitTimApp(void)
{
    if(PLC_APP_CURR)
    {
        if(PLC_APP_CURR->common_ticktime)
        {
            uint32_t TimerPeriod = (uint32_t)(*PLC_APP_CURR->common_ticktime/RTOS_TICK_NS);
            if(!TimerPeriod) TimerPeriod = RTOS_TIM_APP_TM;
            xTimerChangePeriod(RTOS_TIM_App, (TickType_t)TimerPeriod, (TickType_t)0);
#ifdef DEBUG_LOG_MAIN
            DebugLog("TimApp: %d(ms)\n", TimerPeriod);
#endif // DEBUG_LOG_MAIN
        }
    }
}

/** @brief  Task `Application`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 */
void RTOS_TaskApp(void *ParamsIn)
{
    //VARIABLES
    BaseType_t  SemaStatus;

#ifdef RTE_MOD_DO
    PlcDO_Set_t QueueData_DoSet;
    PLC_DO_POSTPONED = BIT_FALSE;
#endif // RTE_MOD_DO

#ifdef RTE_MOD_AO
    PlcAO_Set_t QueueData_AoSet;
    PLC_AO_POSTPONED = BIT_FALSE;
#endif // RTE_MOD_AO

    //INIT
    (void)ParamsIn; //fix unused

#ifdef DEBUG_LOG_MAIN
    DebugLog("WORK [START]\n");
#endif // DEBUG_LOG_MAIN
    xSemaphoreGive(RTOS_SEMA_App);
    dbg_init();
    PlcApp_Start();

#ifdef RTE_MOD_APP_TIM
    RTOS_TaskApp_InitTimApp();
#endif // RTE_MOD_APP_TIM

#ifdef DEBUG_LOG_MAIN
    if(PLC_APP_STATE == PLC_APP_STATE_STARTED)
    {
        DebugLog("Application [STARTED] {%d}\n", PLC_APP_STATE);
    }
    else
    {
        DebugLog("Application [NOT STARTED] {%d}\n", PLC_APP_STATE);
    }
#endif // DEBUG_LOG_MAIN

    //START
    for(;;)
    {
        dbg_handler();

        if(PLC_APP_STATE == PLC_APP_STATE_STARTED)
        {
            //Waiting for Application cycle
            SemaStatus = xSemaphoreTake(RTOS_SEMA_App, (TickType_t)0);
            if(SemaStatus == pdPASS)
            {
                //Save ModBus Data into AppData
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);
                REG_CopyMbToApp();
                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK

                //Run Application
                PlcApp_Run();

#ifdef DEBUG_LOG_APP
                PlcApp_DebugPrint();
#endif // DEBUG_LOG_APP

                //Save AppData into ModBus Tables
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);
                REG_CopyAppToMb();
                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK

#ifdef RTE_MOD_DO
                //Update DO (normal)
                if(PLC_DO_POSTPONED)
                {
                    QueueData_DoSet.SetID  = PLC_DO_SET_POSTPONED_APPLY;
                    QueueData_DoSet.SetVal = (float)BIT_TRUE;
                    xQueueSendToBack(RTOS_Q_DoSet, &QueueData_DoSet, 0);
                    PLC_DO_POSTPONED = BIT_FALSE;
                }
#endif // RTE_MOD_DO

#ifdef RTE_MOD_AO
                //Update AO (normal)
                if(PLC_AO_POSTPONED)
                {
                    QueueData_AoSet.SetID  = PLC_AO_SET_POSTPONED_APPLY;
                    QueueData_AoSet.SetVal = (float)BIT_TRUE;
                    xQueueSendToBack(RTOS_Q_AoSet, &QueueData_AoSet, 0);
                    PLC_AO_POSTPONED = BIT_FALSE;
                }
#endif // RTE_MOD_AO

                //Reset TimApp
                xTimerReset(RTOS_TIM_App, 0);
            }
        }

        //fast switch to other task
        taskYIELD();
    }
}


/** @brief  Timer-handler.
 *  @param  TimerIn - timer.
 *  @return none.
 */
void RTOS_TimApp(TimerHandle_t TimerIn)
{
    (void)TimerIn; //fix unused
    xSemaphoreGive(RTOS_SEMA_App);
}
