/* @page rtos-task-led.c
 *       FreeRTOS Task
 *       Led RUN/NET
 *       2020-2022
 */

#include "rtos-task-led.h"


/** @var LED control counter.
 *  @note
 *  == 0 - LED is off
 *  == 1 - LED is on (blink mode)
 */
static uint8_t PLC_LED_CNT;


/** @brief  Task `Led`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 */
void RTOS_TaskLed(void *ParamsIn)
{
    //variables
    uint8_t    QueueData;
    BaseType_t QueueStatus;

    (void)ParamsIn; //fix unused
    PLC_LED_CNT = 0;

    //start
    for(;;)
    {
        QueueData = 0;

        //Read Queue (not-blocking)
        //get control bytes
        QueueStatus = xQueueReceive(RTOS_Q_Led, &QueueData, 0);
        if(QueueStatus == pdPASS)
        {
            if(QueueData && PLC_LED_CNT < 4) PLC_LED_CNT++;
        }

        if(PLC_LED_CNT)
        {
            if(!PlcDO_Toggle(PLC_LED_PORT, PLC_LED1_PIN, PLC_LED1_PIN_MODE)) PLC_LED_CNT--;
            vTaskDelay(PLC_LED_PULSE_LEN); //ms
        }

        //fast switch to other task
        taskYIELD();
    }
}
