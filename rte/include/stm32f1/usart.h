/* @page usart.h
 *       USART driver
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#ifndef PLC_USART_H
#define PLC_USART_H

#include "config.h"


/** @brief  Send byte.
 *  @param  UsartIn - USART.
 *  @param  ByteIn - byte to send.
 *  @return None.
 */
void PlcUsart_SendByte(USART_TypeDef *UsartIn, const uint16_t ByteIn);


/** @brief   Print string.
 *  @param   UsartIn - USART.
 *  @param   StrIn - pointer to the debug string.
 *  @param   StrLenIn - size of the debug string.
 *  @return  None.
 */
void PlcUart_SendStr(USART_TypeDef *UsartIn, char *StrIn, uint8_t StrLenIn);


/** @brief  Read byte.
 *  @param  UsartIn - USART.
 *  @return Received byte (0 by default).
 */
uint8_t PlcUsart_ReadByte(USART_TypeDef *UsartIn);


/** @brief  Start Tx over interrupts.
 *  @param  UsartIn - USART.
 *  @param  DataIn  - pointer to Tx-data.
 *  @param  LenIn   - length of Tx-data.
 *  @param  CntIn   - pointer to counter of sent data.
 *  @return None.
 */
void PlcUsart_StartTxISR(USART_TypeDef *UsartIn, const uint8_t *DataIn, const uint8_t LenIn, uint8_t *CntIn);


#endif //PLC_USART_H
