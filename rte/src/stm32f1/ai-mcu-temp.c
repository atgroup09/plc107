/* @page ai-mcu-temp.c
 *       MCU sensors
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#include "ai-mcu-temp.h"


/** @brief  Get analog level of MCU-temp.
 *  @param  DigLvIn - digital level:
 *  @arg      = PLC_AI_DIG_MIN ... PLC_AI_DIG_MAX
 *  @return Analog level (C*):
 *  @arg      = PLC_MCU_TEMP_ANA_MIN ... PLC_MCU_TEMP_ANA_MAX
 *  @note   Current C*
 */
float PlcMCUTemp_GetAnaLv(const uint16_t DigLvIn)
{
    float Vsense = ((float)DigLvIn/(float)PLC_AI_DIG_MAX)*PLC_MCU_TEMP_ADC_V_REF;
    return (((Vsense - PLC_MCU_TEMP_V25)/PLC_MCU_TEMP_AVG_SLOPE) + 25.0);
}

/** @brief  Get value of MCU-temp.
 *  @param  None.
 *  @return C*.
 */
float PlcMCUTemp_GetTemp(void)
{
    float Res = PLC_MCU_TEMP_ANA_DEF;

    uint16_t DigLv = PlcAI_GetDigLv(PLC_AI_MCU_TEMP);
    Res = PlcMCUTemp_GetAnaLv(DigLv);

#ifdef DEBUG_LOG_MCU_ADC
    DebugLog("PlcMCUTemp: DigLv=%d T=%d\n", DigLv, (uint32_t)Res);
#endif // DEBUG_LOG_MCU_ADC

    return (Res);
}
