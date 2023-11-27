/* @page ai-mcu-temp.h
 *       MCU sensors
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

/** @note MCU Temperature sensor
 *        + 12 bit
 *        + 0 .. 4095 (–40 .. 125 C*)
 *
 *        Temp-sensor -> ADC1.Channel16 > DMA1.Channel1(ADC1)
 *        used AI-buffer (PLC_AI_ADC_BUFF, see ai.h and ai.c)
 *
 *        Temperature = {(Vsense – V25) / Avg_Slope} + 25 (C*)
 *
 *             Vsense = (ADCcur/ADCmax)*Vref
 *
 *        where, ADCcur    - current ADC-code
 *               ADCmax    - maximum ADC-code (4095 for 12bit ADC)
 *               Vref      - ADC Vref (V)
 *               Vsense    - current sensor value (V)
 *               V25       - Vsense value for 25 C* (constant)
 *               Avg_Slope - average slope of the temperature vs. Vsense curve (V/C*) (constant)
 */

#ifndef PLC_MCU_H
#define PLC_MCU_H

#include <math.h>
#include "config.h"
#include "ai.h"
#include "rtos-task-log.h"


/** @def ADC Vref
 */
#define PLC_MCU_TEMP_ADC_V_REF                   (float)3.3    //V


/** @def Avg_Slope (mV/C*)
 *       average slope
 */
#define PLC_MCU_TEMP_AVG_SLOPE                   (float)0.0025  //V/C*


/** @def V25 (V)
 *       value for 25 C*
 */
#define PLC_MCU_TEMP_V25                         (float)0.76   //V


/** @def Analog levels (C*)
 */
#define PLC_MCU_TEMP_ANA_MIN                     (float)-40.0    //minumum
#define PLC_MCU_TEMP_ANA_MAX                     (float)125.0    //maximum
#define PLC_MCU_TEMP_ANA_DEF                     PLC_MCU_TEMP_ANA_MIN  //by default


/** @def Item of settings (for Queue)
 *       IDs
 */
#define PLC_MCU_SET_TEMP                         (uint8_t)0  //value of MCU Temperature sensor


/** @brief  Get analog level of MCU-temp.
 *  @param  DigLvIn - digital level:
 *  @arg      = PLC_AI_DIG_MIN ... PLC_AI_DIG_MAX
 *  @return Analog level (C*):
 *  @arg      = PLC_MCU_TEMP_ANA_MIN ... PLC_MCU_TEMP_ANA_MAX
 *  @note   Current C*
 */
float PlcMCUTemp_GetAnaLv(const uint16_t DigLvIn);

/** @brief  Get value of MCU-temp.
 *  @param  None.
 *  @return C*.
 */
float PlcMCUTemp_GetTemp(void);

#endif //PLC_MCU_H
