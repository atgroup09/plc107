/* @page swd-debug.c
 *       Debug print over SWD
 *       platform-dependent code
 *       stm32f2xx, SPL
 *       2020
 */

#include "swd-debug.h"


#ifdef SWD_DEBUG_CMSIS
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0UL) &&      /* ITM enabled */
      ((ITM->TER & 1UL               ) != 0UL)   )     /* ITM Port #0 enabled */
  {
    while (ITM->PORT[0U].u32 == 0UL)
    {
        asm("NOP");
    }
    ITM->PORT[0U].u8 = (uint8_t)ch;
  }
  return (ch);
}
#endif // SWD_DEBUG_CMSIS


/** @brief   Print string.
 *  @param   StrIn - pointer to the debug string.
 *  @param   StrLenIn - size of the debug string.
 *  @return  None.
 */
void SWDDebug_PrintStr(char *StrIn, uint8_t StrLenIn)
{
  uint8_t i = 0;

  if(StrIn && StrLenIn > 0)
  {
      for(i=0; i<StrLenIn; i++)
      {
          if(StrIn[i] == '\0') break;
          ITM_SendChar(StrIn[i]);
          if(StrIn[i] == '\n') break;
      }
  }
}


/** @brief   Print byte.
 *  @param   ByteIn - byte.
 *  @return  None.
 */
inline void SWDDebug_PrintByte(uint8_t ByteIn)
{
    ITM_SendChar((uint32_t)ByteIn);
}


/** @brief   Print word.
 *  @param   WordIn - word.
 *  @return  None.
 */
inline void SWDDebug_PrintWord(uint16_t WordIn)
{
    ITM_SendChar((uint32_t)WordIn);
}


/** @brief   Print dword.
 *  @param   DWordIn - dword.
 *  @return  None.
 */
inline void SWDDebug_PrintDWord(uint32_t DWordIn)
{
    ITM_SendChar(DWordIn);
}
