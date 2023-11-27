/* @page usart3.h
 *       USART3 driver
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020-2022
 */

#include "usart3.h"


/** @brief  USART3 initialization.
 *  @param  none.
 *  @return none.
 */
void PlcUsart3_Init(void)
{
    GPIO_InitTypeDef  GPIODef;
    USART_InitTypeDef UsartDef;

    //Enable clock
    RCC_APB1PeriphClockCmd((RCC_APB1Periph_USART3), ENABLE);
    RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO), ENABLE);

    //GPIO configuration
    // PB10 -> TX
    GPIODef.GPIO_Pin   = GPIO_Pin_10;
    GPIODef.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIODef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIODef);
    // PB11 <- RX
    GPIODef.GPIO_Pin   = GPIO_Pin_11;
    GPIODef.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIODef);

    //USART configuration
    USART_StructInit(&UsartDef);
    UsartDef.USART_BaudRate            = PLC_USART3_BAUDRATE;
    UsartDef.USART_WordLength          = PLC_USART3_DATABITS;
    UsartDef.USART_StopBits            = PLC_USART3_STOPBITS;
    UsartDef.USART_Parity              = PLC_USART3_PARITY;
    UsartDef.USART_Mode                = PLC_USART3_MODE;
    UsartDef.USART_HardwareFlowControl = PLC_USART3_FLOW_CTRL;
    USART_Init(USART3, &UsartDef);

    //Enable USART
    USART_Cmd(USART3, ENABLE);
}
