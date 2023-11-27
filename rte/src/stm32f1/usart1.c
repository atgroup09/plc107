/* @page usart1.c
 *       USART1 driver
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020-2022
 */

#include "usart1.h"


static unsigned char usart_data = 0x00;
static dbg_fifo_t usart_rx_buf, usart_tx_buf;


/** @brief  USART1 initialization.
 *  @param  none.
 *  @return none.
 */
void PlcUsart1_Init(void)
{
    GPIO_InitTypeDef  GPIODef;
    USART_InitTypeDef UsartDef;

    //Flush Debug-buffer
    dbg_fifo_flush(&usart_rx_buf);
    dbg_fifo_flush(&usart_tx_buf);

    //Enable clock
    RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO), ENABLE);

    //GPIO config
    // PA9 -> TX
    GPIODef.GPIO_Pin   = GPIO_Pin_9;
    GPIODef.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIODef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIODef);
    // PA10 <- RX
    GPIODef.GPIO_Pin   = GPIO_Pin_10;
    GPIODef.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIODef);

    //USART config
    USART_StructInit(&UsartDef);
    UsartDef.USART_BaudRate            = PLC_USART1_BAUDRATE;
    UsartDef.USART_WordLength          = PLC_USART1_DATABITS;
    UsartDef.USART_StopBits            = PLC_USART1_STOPBITS;
    UsartDef.USART_Parity              = PLC_USART1_PARITY;
    UsartDef.USART_Mode                = PLC_USART1_MODE;
    UsartDef.USART_HardwareFlowControl = PLC_USART1_FLOW_CTRL;
    USART_Init(USART1, &UsartDef);

    //IRQ config
    NVIC_InitTypeDef NvicDef;
    NvicDef.NVIC_IRQChannel                   = USART1_IRQn;
    NvicDef.NVIC_IRQChannelPreemptionPriority = PLC_NVIC_PPRIO_USART_DBG;
    NvicDef.NVIC_IRQChannelSubPriority        = PLC_NVIC_SPRIO_USART_DBG;
    NvicDef.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NvicDef);

    //Enable IRQ
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
    USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);

    //Enable USART
    USART_Cmd(USART1, ENABLE);
}

static void USART1_DisableNVIC(void)
{
    NVIC_DisableIRQ(USART1_IRQn);
}

static void USART1_EnableNVIC(void)
{
    NVIC_EnableIRQ(USART1_IRQn);
}


/** @brief  USART1 interrupts handler.
 *  @param  none.
 *  @return none.
 */
void USART1_IRQHandler(void)
{
    //RXNE
    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);

        usart_data = (unsigned char)USART_ReceiveData(USART1);

        if(!dbg_fifo_write_byte(&usart_rx_buf, usart_data))
        {
            USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
        }
    }

    //TXE
    if(USART_GetITStatus(USART1, USART_IT_TXE) == SET)
    {
        //Put data into the transmit register
        if(dbg_fifo_read_byte(&usart_tx_buf, &usart_data))
        {
            USART_SendData(USART1, (uint16_t)usart_data);
        }
        else
        {
            //Disable the TXE interrupt as we don't need it anymore
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE);  //TXE
        }
    }
}


int dbg_serial_write(unsigned char *d, unsigned short n)
{
    int res = 0;
    USART1_DisableNVIC();
    res = dbg_fifo_write(&usart_tx_buf, d, n);
    //if(res && !(USART1->CR1 & USART_CR1_TXEIE))
    if(res)
    {
        if(dbg_fifo_read_byte(&usart_tx_buf, &usart_data))
        {
            while(!(USART1->SR & USART_SR_TXE));
            USART_SendData(USART1, usart_data);
            USART_ITConfig(USART1, USART_IT_TXE, ENABLE);  //TXE
        }
    }
    USART1_EnableNVIC();
    return res;
}

int dbg_serial_read(unsigned char *d, unsigned short n)
{
    int res = 0;

    while(n--)
    {
        USART1_DisableNVIC();
        if(dbg_fifo_read_byte(&usart_rx_buf, d))
        {
            USART1_EnableNVIC();
            d++;
            res++;
        }
        else
        {
            USART1_EnableNVIC();
            break;
        }
    }
    return res;
}
