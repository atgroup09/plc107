/* @page ai.h
 *       AI driver (+ MCU-temperature sensor)
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

/** @note AI
 *        + 12 bit
 *        + 0 .. 4095 (0 .. 3.3 V)
 *
 *        PC0 (ADC12_IN10) -> AI0 -> ADC1.Channel10 > DMA1.Channel1(ADC1)
 *
 *        Scale function:
 *
 *          RealValue = KaIn*In + KbIn
 *
 *        Scale factors:
 *
 *          Ka - slope of characteristic:
 *               >0
 *               =1 for ideal characteristic
 *
 *          Ka = (Y2In - Y1In)/(In2 - In1)
 *
 *          Kb - offset of characteristic:
 *               >=0
 *               =0 for ideal characteristic
 *
 *          Kb = (Y1In*In2 - Y2In*In1)/(In2 - In1)
 */

#ifndef PLC_AI_H
#define PLC_AI_H

#include <math.h>
#include "config.h"
#include "scale.h"
#include "rtos-task-log.h"


/** @def Channels
 */
#define PLC_AI_00                                (uint8_t)0
#define PLC_AI_MCU_TEMP                          (uint8_t)1

/** @def Quantity of channels
 */
#define PLC_AI_SZ                                (uint16_t)(PLC_AI_MCU_TEMP+1)


/** @def ADC-channel
 */
#define PLC_AI_00_ADC_CHANNEL                     ADC_Channel_10
#define PLC_AI_MCU_TEMP_ADC_CHANNEL               ADC_Channel_16

/** @def ADC-channel rank
 */
#define PLC_AI_00_ADC_CHANNEL_RANK                (uint8_t)1
#define PLC_AI_MCU_TEMP_ADC_CHANNEL_RANK          (uint8_t)2

/** @def Quantity of measurements per a ADC-channel
 *  @note ADC-code of a channel is a average of all its measurements
 */
#define PLC_AI_ADC_CHANNEL_MEASURES              100

/** @var Size of ADC buffer by channels
 */
#define PLC_AI_ADC_BUFF_SZ                       (uint16_t)(PLC_AI_SZ*PLC_AI_ADC_CHANNEL_MEASURES)


/** @def DMA settings
 */
#define PLC_AI_DMA_CHANNEL                       DMA1_Channel1 //channel (1)
#define PLC_AI_DMA_TC_FLAG                       DMA1_FLAG_TC1 //flag `Transfer completed` for channel (1)


/** @def Modes
 */
#define PLC_AI_MODE_SURVEY                       (uint8_t)0  //survey
#define PLC_AI_MODE_CALB                         (uint8_t)1  //calibration
#define PLC_AI_MODE_OFF                          (uint8_t)2  //off


/** @def Status codes
 */
#define PLC_AI_STATUS_SURVEY                     (uint8_t)0  //survey
#define PLC_AI_STATUS_CALB                       (uint8_t)1  //calibration
#define PLC_AI_STATUS_CALB_DONE                  (uint8_t)11 //calibration completed success
#define PLC_AI_STATUS_OFF                        (uint8_t)2  //off


/** @def Analog value by status codes
 */
#define PLC_AI_ANA_STATUS_CALB                   (float)0.0     //calibration
#define PLC_AI_ANA_STATUS_CALB_DONE              (float)0.0     //calibration completed success
#define PLC_AI_ANA_STATUS_OFF                    (float)0.0     //off


/** @def Survey period (ms)
 */
#define PLC_AI_SURVEY_PERIOD_MS                  (uint16_t)50   //ms


/** @def Digital levels (ADC-code)
 *       0 .. 12bit
 */
#define PLC_AI_DIG_MIN                           (uint16_t)0     //minumum
#define PLC_AI_DIG_MAX                           (uint16_t)4095  //maximum


/** @def Analog levels (V)
 */
#define PLC_AI_ANA_MIN                           (float)0.0      //minumum
#define PLC_AI_ANA_MAX                           (float)3.3      //maximum
#define PLC_AI_ANA_DEF                           PLC_AI_ANA_MIN  //by default


/** @def Scale factors by default
 */
#define PLC_AI_KA_DEF                            (float)0.000805861
#define PLC_AI_KB_DEF                            (float)0.0


/** @typedef Channel settings
 *           packed data
 */
typedef struct PlcAI_Pack_t_
{
    //@var The channel number
    //@arg = 0..127
    uint32_t ChNum:7;

    //@var The channel mode
    //@arg = 0..15
    uint32_t Mode:4;

    //@var The channel mode (result)
    //@arg = 0..15
    uint32_t ModeRes:4;

    //@var The status code
    //@arg = 0..127
    uint32_t Status:7;

} PlcAI_Pack_t;


/** @typedef Channel settings
 *           main structure
 */
typedef struct PlcAI_t_
{
    //@var Packed data
    PlcAI_Pack_t Pack;

    //@var The channel value
    float Val;

    //@var Scale factors
    float Ka;
    float Kb;

    //@var Calibration values
    uint16_t I1;  //ADC value for Lo-level (code)
    uint16_t I2;  //ADC value for Hi-level (code)

} PlcAI_t;


/** @def Item of settings (for Queue)
 *       IDs
 */
#define PLC_AI_SET_VAL                           (uint8_t)0  //value
#define PLC_AI_SET_MODE                          (uint8_t)1  //mode
#define PLC_AI_SET_MODE_RES                      (uint8_t)2  //mode (result)
#define PLC_AI_SET_STATUS                        (uint8_t)3  //status
#define PLC_AI_SET_CALB_LO_CMD                   (uint8_t)4  //command to set calibrated values of Lo-level (current ADC-code)
#define PLC_AI_SET_CALB_HI_CMD                   (uint8_t)5  //command to set calibrated values of Hi-level (current ADC-code)
#define PLC_AI_SET_CALB_CMD                      (uint8_t)6  //command to calculate calibration factors


/** @def Item of settings (for Queue)
 *       main structure
 */
typedef struct PlcAI_Set_t_
{
    //@var Channel number
    uint8_t ChNum;

    //@var Settings ID
    uint8_t SetID;

    //@var Settings value
    float SetVal;

} PlcAI_Set_t;


/** @def Default values
 */
#define PLC_AI_MODE_DEF                          PLC_AI_MODE_SURVEY


/** @brief  Initialization.
 *  @param  none.
 *  @return none.
 */
void PlcAI_Init(void);


/** @brief  Get digital level of AI-channel.
 *  @param  ChNumIn - channel number.
 *  @return Digital level:
 *  @arg      = PLC_AI_DIG_MIN ... PLC_AI_DIG_MAX
 *  @note   Current ADC-code
 */
uint16_t PlcAI_GetDigLv(const uint8_t ChNumIn);


/** @brief  Get analog level of AI-channel.
 *  @param  DigLvIn - digital level:
 *  @arg      = PLC_AI_DIG_MIN ... PLC_AI_DIG_MAX
 *  @param  KaIn - scale Ka-factor.
 *  @param  KbIn - scale Kb-factor.
 *  @return Analog level (V):
 *  @arg      = PLC_AI_ANA_MIN ... PLC_AI_ANA_MAX
 *  @note   Current V
 */
float PlcAI_GetAnaLv(const uint16_t DigLvIn, const float KaIn, const float KbIn);


/** @brief  Get analog level of AI-channel.
 *  @param  ChNumIn - channel number.
 *  @param  KaIn - scale Ka-factor.
 *  @param  KbIn - scale Kb-factor.
 *  @return Analog level (V):
 *  @arg      = PLC_AI_ANA_MIN ... PLC_AI_ANA_MAX
 *  @note   Current V
 */
float PlcAI_GetAnaLvByChNum(const uint8_t ChNumIn, const float KaIn, const float KbIn);


#endif //PLC_AI_H
