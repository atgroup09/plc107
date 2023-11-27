/* @page rtos-task-mbrtu.c
 *       FreeRTOS Task
 *       ModBus RTU
 *       2020-2022
 */

#include "rtos-task-mbrtu.h"


/** @brief  MBRTU Slave.
 *  @param  None.
 *  @return None.
 */
void RTOS_TaskMbRtu_Slave(void)
{
    uint8_t    QueueData;
    BaseType_t QueueStatus;

    //Read Queue (not-blocking)
    //get Rx-data
    QueueStatus = xQueueReceive(RTOS_Q_MbRtuRx, &QueueData, 0);
    if(QueueStatus == pdPASS)
    {
        switch(QueueData)
        {
            //RX-end
            case RTOS_MBRTU_Q_RX_END:

                //parse request
                if(MBRTU_COM.RxExc == MBRTU_EXC_OK)
                {
                    MBRTU_COM.RxExc = MBRTU_ParseReq(&MBRTU_COM);
                }

                //create answer
                if(MBRTU_COM.RxExc == MBRTU_EXC_OK)
                {
                    //wait LOCK (blocking on RTOS_MBRTU_M_RX_WAIT)
                    if(xSemaphoreTake(RTOS_MTX_MbTables, RTOS_MBRTU_M_RX_WAIT) == pdPASS)
                    {
                        //LOCK
                        MBRTU_COM.RxExc = MBRTU_CreateRes(&MBRTU_COM);
                        xSemaphoreGive(RTOS_MTX_MbTables);
                        //UNLOCK
                    }
                    else
                    {
                        //exception: Device is busy
                        MBRTU_COM.RxExc = MBRTU_EXC_PROCESS;
                    }
                }

                //create exc-answer
                if(MBRTU_COM.RxExc != MBRTU_EXC_OK)
                {
                    if(MBRTU_COM.RxExc < MBRTU_EXC_SLAVE_ERR)
                    {
                        MBRTU_CreateResExc(&MBRTU_COM, MBRTU_COM.RxExc);
                    }
                }

                //update diagnostic counters
                if(MBRTU_COM.RxExc)
                {
                    //cBusExcErr
                    if(MBRTU_COM.cBusExcErr < MBRTU_DIAG_COUNTER_MAX) MBRTU_COM.cBusExcErr++;
                    //cBusComErr
                    if(MBRTU_COM.RxExc == MBRTU_EXC_CRC_ERR && MBRTU_COM.cBusComErr < MBRTU_DIAG_COUNTER_MAX) MBRTU_COM.cBusComErr++;
                    //cNoRes
                    if(MBRTU_COM.RxExc >= MBRTU_EXC_SLAVE_ERR && MBRTU_COM.cNoRes < MBRTU_DIAG_COUNTER_MAX) MBRTU_COM.cNoRes++;
                }

                //send response
                MBRTU_SendRes(&MBRTU_COM);
                break;
        }
    }
}

/** @brief  Task MBRTU.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskMbRtu(void *ParamsIn)
{
    //VARIABLES

    //INIT
    (void)ParamsIn; //fix unused

    //START
    for(;;)
    {
        //Slave mode
        RTOS_TaskMbRtu_Slave();

        //fast switch to other task
        taskYIELD();
    }
}
