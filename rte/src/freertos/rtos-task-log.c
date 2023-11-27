/* @page rtos-log.c
 *       FreeRTOS Task
 *       Debug Log
 *       2020-2022
 */

#include "rtos-task-log.h"


/** @var Local buffer
 */
#ifdef DEBUG
static char DEBUG_LOG_BUFF[DEBUG_LOG_BUFF_SZ];
#endif // DEBUG

uint8_t RTOS_TASK_LOG_STARTED;


/** @brief  Log Out one byte.
 *  @param  ByteIn - byte.
 *  @return none.
 */
void RTOS_TaskLog_Out(const uint8_t ByteIn)
{
#ifdef DEBUG
#if   (DEBUG_LOG_DST == DEBUG_LOG_DST_SWD)
    SWDDebug_PrintByte(ByteIn);
#elif (DEBUG_LOG_DST == DEBUG_LOG_DST_USART)
#ifdef DEBUG_LOG_USART_DE_USE
    GPIO_SetBits(DEBUG_LOG_USART_DE_PORT, DEBUG_LOG_USART_DE_PIN);
#endif // DEBUG_LOG_USART_DE_USE
    PlcUsart_SendByte(DEBUG_LOG_USART, (uint16_t)ByteIn);
#else
    (void)ByteIn;
#endif
#else
    (void)ByteIn;
#endif // DEBUG
}


/** @brief  Task: LOG.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskLog(void *ParamsIn)
{
    //variables
#ifdef DEBUG
    uint8_t QueueData = 0;
    BaseType_t QueueStatus;
#endif

    (void)ParamsIn; //fix unused

    //start
    for(;;)
    {
#ifdef DEBUG
        //Read Queue (blocking)
        QueueStatus = xQueueReceive(RTOS_Q_Log, &QueueData, portMAX_DELAY);
        if(QueueStatus == pdPASS)
        {
            RTOS_TaskLog_Out(QueueData);
        }
#endif
        //fast switch to other task
        taskYIELD();
    }
}


/** @brief  Debug Log.
 *  @param  FmtIn - pointer to string with format specificators.
 *  @param  ...   - arguments of format specificators.
 *  @return None.
 *  @note   !!! DON'T EXECUTE FROM IRQ !!!
 */
void DebugLog(const char *FmtIn, ...)
{
#ifdef DEBUG
    if(FmtIn)
    {
        //LOCK
        if(RTOS_TASK_LOG_STARTED) xSemaphoreTake(RTOS_MTX_Log, portMAX_DELAY);

        va_list arp;
        va_start(arp, FmtIn);
        xsprintfa(DEBUG_LOG_BUFF, FmtIn, arp);

        BaseType_t QueueStatus;
        char *Buff = DEBUG_LOG_BUFF;

        for(uint16_t i=0; i<DEBUG_LOG_BUFF_SZ; i++)
        {
            if(*(Buff+i) == '\0') break;

            if(RTOS_TASK_LOG_STARTED)
            {
                QueueStatus = xQueueSendToBack(RTOS_Q_Log, (Buff+i), 0);
                if(QueueStatus != pdTRUE) break;
            }
            else
            {
                RTOS_TaskLog_Out(*(Buff+i));
            }

            if(*(Buff+i) == '\n') break;
        }

        va_end(arp);

        if(RTOS_TASK_LOG_STARTED) xSemaphoreGive(RTOS_MTX_Log);
        //UNLOCK
    }
#else
    (void)FmtIn;
#endif // DEBUG
}
