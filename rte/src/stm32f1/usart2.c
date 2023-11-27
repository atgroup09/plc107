/* @page usart2.h
 *       USART2 driver
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020-2022
 */

#include "usart2.h"


/** @brief  USART2 initialization.
 *  @param  none.
 *  @return none.
 */
void PlcUsart2_Init(void)
{
    GPIO_InitTypeDef  GPIODef;
    USART_InitTypeDef UsartDef;

    //Enable clock
    RCC_APB1PeriphClockCmd((RCC_APB1Periph_USART2), ENABLE);
    RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO), ENABLE);

    //GPIO configuration
    // PA2 -> TX
    GPIODef.GPIO_Pin   = GPIO_Pin_2;
    GPIODef.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIODef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIODef);
    // PA3 <- RX
    GPIODef.GPIO_Pin   = GPIO_Pin_3;
    GPIODef.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIODef);

    //USART configuration
    USART_StructInit(&UsartDef);
    UsartDef.USART_BaudRate            = MBRTU_UsartDefBaudRate(MBRTU_COM.Settings.BaudRate);
    UsartDef.USART_WordLength          = MBRTU_UsartDefDataBits(MBRTU_COM.Settings.DataBits);
    UsartDef.USART_StopBits            = MBRTU_UsartDefStopBits(MBRTU_COM.Settings.StopBits);
    UsartDef.USART_Parity              = MBRTU_UsartDefParity(MBRTU_COM.Settings.Parity);
    UsartDef.USART_Mode                = PLC_USART2_MODE;
    UsartDef.USART_HardwareFlowControl = PLC_USART2_FLOW_CTRL;
    USART_Init(USART2, &UsartDef);

    //IRQ config
    NVIC_InitTypeDef NvicDef;
    NvicDef.NVIC_IRQChannel                   = USART2_IRQn;
    NvicDef.NVIC_IRQChannelPreemptionPriority = PLC_NVIC_PPRIO_USART_MBRTU;
    NvicDef.NVIC_IRQChannelSubPriority        = PLC_NVIC_SPRIO_USART_MBRTU;
    NvicDef.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NvicDef);

    //Enable IRQ
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);

    //Enable USART
    MBRTU_Start(&MBRTU_COM, MBRTU_RX);
    USART_Cmd(USART2, ENABLE);
}


/** @var Result of xQueueSendToBackFromISR(), xQueueSendToFrontFromISR()
 *       = pdTRUE - if sending to the queue caused a task to unblock, and the unblocked task has a priority higher than the currently running task
 */
static portBASE_TYPE RTOS_Usart2ISR_TaskWoken = pdFALSE;


/** @brief  USART2 interrupts handler.
 *  @param  none.
 *  @return none.
 */
void USART2_IRQHandler(void)
{
    //send data to T_COM1
    RTOS_Usart2ISR_TaskWoken = pdTRUE;
    uint8_t QueueData;

    //IDLE
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
    {
        if(MBRTU_COM.RxTx == MBRTU_RX || MBRTU_COM.RxTx == MBRTU_RX_EXC)
        {
            //send RX-end to T_MBRTU
            QueueData = RTOS_MBRTU_Q_RX_END;
            xQueueSendToBackFromISR(RTOS_Q_MbRtuRx, &QueueData, &RTOS_Usart2ISR_TaskWoken);
        }

        //disable and reset IDLE
        (void)USART_GetFlagStatus(USART2, USART_FLAG_IDLE);
        (void)USART_GetITStatus(USART2, USART_IT_RXNE);
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        (void)USART_ReceiveData(USART2);
    }
    //IDLE End

    //RXNE
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        if(MBRTU_COM.RxTx == MBRTU_RX)
        {
            if(MBRTU_COM.RxCnt < MBRTU_BUFF_SZ-1)
            {
                //add RxByte to RxBuff
                MBRTU_COM.RxBuff[MBRTU_COM.RxCnt] = (uint8_t)USART_ReceiveData(USART2);

                if(MBRTU_COM.RxCnt == MBRTU_ADU_FUNC_POS)
                {
                    MBRTU_COM.RxFunc = MBRTU_COM.RxBuff[MBRTU_COM.RxCnt];
                }

                MBRTU_COM.RxCnt++;
            }
            else
            {
                //exception: RxBuff is overflow
                MBRTU_COM.RxExc = MBRTU_EXC_NONRECOV_ERR;
            }

            if(MBRTU_COM.RxExc != MBRTU_EXC_OK)
            {
                MBRTU_COM.RxTx = MBRTU_RX_EXC;
            }
        }
        else
        {
            //dummy
            (void)USART_ReceiveData(USART2);
        }

        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
    //RXNE End

    //TC
    if(USART_GetITStatus(USART2, USART_IT_TC) != RESET)
    {
        if(MBRTU_COM.RxTx == MBRTU_TX)
        {
            if(MBRTU_COM.cTx < MBRTU_COM.TxCnt)
            {
                //send to port
                USART_SendData(USART2, (uint16_t)MBRTU_COM.TxBuff[MBRTU_COM.cTx]);
                MBRTU_COM.cTx++;
            }
            else
            {
                MBRTU_Start(&MBRTU_COM, MBRTU_RX);
            }
        }

        USART_ClearITPendingBit(USART2, USART_IT_TC);
    }
    //TC End

    //fast switch to other task
    if(RTOS_Usart2ISR_TaskWoken == pdTRUE) taskYIELD();
}
