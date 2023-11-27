/* @page usart.c
 *       USART driver
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#include "usart.h"


/** @brief  Send byte over USART.
 *  @param  UsartIn - USART.
 *  @param  ByteIn - byte to send.
 *  @return None.
 */
void PlcUsart_SendByte(USART_TypeDef *UsartIn, const uint16_t ByteIn)
{
    if(UsartIn)
    {
        while(!(UsartIn->SR & USART_SR_TC));
        USART_SendData(UsartIn, ByteIn);
    }
}


/** @brief   Print string.
 *  @param   UsartIn - USART.
 *  @param   StrIn - pointer to the debug string.
 *  @param   StrLenIn - size of the debug string.
 *  @return  None.
 */
void PlcUart_SendStr(USART_TypeDef *UsartIn, char *StrIn, uint8_t StrLenIn)
{
  uint8_t i = 0;

  if(UsartIn && StrIn && StrLenIn > 0)
  {
      for(i=0; i<StrLenIn; i++)
      {
          if(StrIn[i] == '\0') break;
          PlcUsart_SendByte(UsartIn, (uint16_t)StrIn[i]);
          if(StrIn[i] == '\n') break;
      }
  }
}


/** @brief  Read byte.
 *  @param  UsartIn - USART.
 *  @return Received byte (0 by default).
 */
uint8_t PlcUsart_ReadByte(USART_TypeDef *UsartIn)
{
    if(UsartIn)
    {
        while(USART_GetFlagStatus(UsartIn, USART_FLAG_TC) == RESET);
        return ((uint8_t)USART_ReceiveData(UsartIn));
    }

    return (BIT_FALSE);
}


/** @brief  Start Tx over interrupts.
 *  @param  UsartIn - USART.
 *  @param  DataIn  - pointer to Tx-data.
 *  @param  LenIn   - length of Tx-data.
 *  @param  CntIn   - pointer to counter of sent data.
 *  @return None.
 */
void PlcUsart_StartTxISR(USART_TypeDef *UsartIn, const uint8_t *DataIn, const uint8_t LenIn, uint8_t *CntIn)
{
    if(DataIn && LenIn > 0)
    {
        *CntIn = 1;
        PlcUsart_SendByte(UsartIn, (uint16_t)DataIn[0]);
        USART_ITConfig(UsartIn, USART_IT_TXE, ENABLE);  //TXE
    }
}
