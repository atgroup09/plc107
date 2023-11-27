/* @page usart3.h
 *       USART3 driver
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020-2022
 */

/** @note USART3
 *        Debug Log
 *        PB10 -> TX
 *        PB11 <- RX
 */

#ifndef PLC_USART3_H
#define PLC_USART3_H

#include "config.h"
#include "bit.h"


/** @def USART Settings
 */
#define PLC_USART3_BAUDRATE         (uint32_t)115200
#define PLC_USART3_DATABITS         USART_WordLength_8b
#define PLC_USART3_STOPBITS         USART_StopBits_1
#define PLC_USART3_PARITY           USART_Parity_No
#define PLC_USART3_FLOW_CTRL        USART_HardwareFlowControl_None
#define PLC_USART3_MODE             USART_Mode_Rx|USART_Mode_Tx


/** @brief  USART3 initialization.
 *  @param  none.
 *  @return none.
 */
void PlcUsart3_Init(void);


#endif //PLC_USART3_H
