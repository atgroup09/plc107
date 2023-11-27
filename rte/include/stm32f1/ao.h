/* @page ao.h
 *       AO driver
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

/** @note AO
 *        + 12 bit
 *        + 0 .. 4095 (0 .. 3.3 V)
 *
 *        PA4 (DAC_OUT1) <- AO0 <- DAC1
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

#ifndef PLC_AO_H
#define PLC_AO_H

#include "config.h"
#include "scale.h"
#include "rtos.h"
#include "rtos-task-log.h"


/** @def AO channel numbers
 */
#define PLC_AO_00                                (uint8_t)0

/** @def Quantity of AO channels
 */
#define PLC_AO_SZ                                (uint16_t)(PLC_AO_00+1)


/** @def DAC-channel
 */
#define PLC_AO_00_DAC_CHANNEL                     DAC_Channel_1


/** @def AO channel modes
 */
#define PLC_AO_MODE_NORM                         (uint8_t)0  //normal
#define PLC_AO_MODE_FAST                         (uint8_t)1  //fast
#define PLC_AO_MODE_CALB                         (uint8_t)2  //calibration
#define PLC_AO_MODE_OFF                          (uint8_t)3  //off


/** @def AO digital levels (ADC code)
 *       0 .. 10bit
 */
#define PLC_AO_DIG_MIN                           (uint16_t)0
#define PLC_AO_DIG_MAX                           (uint16_t)4095
#define PLC_AO_DIG_MIN_FLO                       (float)0.0
#define PLC_AO_DIG_MAX_FLO                       (float)4095.0


/** @def AO analog levels (V)
 */
#define PLC_AO_ANA_MIN                           (float)0.0
#define PLC_AO_ANA_MAX                           (float)3.3
#define PLC_AO_ANA_DEF                           (float)0.0   //by default


/** @def Scale factors by default
 */
#define PLC_AO_KA_DEF                            (float)1240.9091
#define PLC_AO_KB_DEF                            (float)0.0


/** @typedef AO pin description (SPI: CS/SYNC)
 */
typedef struct PlcAO_Pin_t_
{
    //@var GPIO-port
    GPIO_TypeDef *Port;

    //@var GPIO-pin
    uint16_t Pin;

    //@var GPIO-pin mode
    uint8_t PinMode;

} PlcAO_Pin_t;


/** @typedef AO channel (packed data)
 */
typedef struct PlcAO_Pack_t_
{
    //@var The channel number
    //@arg = 0..127
    uint32_t ChNum:7;

    //@var The channel mode
    //@arg = 0..4
    uint32_t Mode:4;

    //@var The channel mode (result)
    //@arg = 0..4
    uint32_t ModeRes:4;

    //@var The channel normal postpend flag
    //@arg = 0..1
    uint32_t Postponed:1;

    //@var Allow Safe-mode
    //@arg = 0..1
    uint32_t SafeAllow:1;

} PlcAO_Pack_t;


/** @typedef AO channel
 */
typedef struct PlcAO_t_
{
    //@var Packed data
    PlcAO_Pack_t Pack;

    //@var The channel normal value
    //@arg = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
    float Val;

    //@var The channel normal postpend value
    //@arg = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
    float PostponedVal;

    //@var The channel fast value
    //@arg = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
    float FastVal;

    //@var Safe-mode value
    //@arg = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
    float SafeVal;

    //@var Scale factors
    float Ka;
    float Kb;

    //@var Calibration values
    float I;   //real value for Lo- or Hi-level (V)
    float I1;  //real value for Lo-level (V)
    float I2;  //real value for Hi-level (V)

} PlcAO_t;


/** @def AO channel settings ID
 */
#define PLC_AO_SET_NORM_VAL                      (uint8_t)0  //normal value
#define PLC_AO_SET_FAST_VAL                      (uint8_t)1  //fast value
#define PLC_AO_SET_MODE                          (uint8_t)2  //mode
#define PLC_AO_SET_MODE_RES                      (uint8_t)3  //mode (result)
#define PLC_AO_SET_SAFE_ALLOW                    (uint8_t)4  //safe-mode allow
#define PLC_AO_SET_SAFE_VAL                      (uint8_t)5  //safe-mode value
#define PLC_AO_SET_POSTPONED_VAL                 (uint8_t)6 //normal value (postponed)
#define PLC_AO_SET_POSTPONED_APPLY               (uint8_t)7 //normal value (apply all postponed valued)
#define PLC_AO_SET_CALB_VAL                      (uint8_t)8  //set calibrated value of Lo- or Hi-level
#define PLC_AO_SET_CALB_LO_CMD                   (uint8_t)9  //command to set calibrated values of Lo-level (fix. Lo-level and current ADC-code)
#define PLC_AO_SET_CALB_HI_CMD                   (uint8_t)10  //command to set calibrated values of Hi-level (fix. Hi-level and current ADC-code)
#define PLC_AO_SET_CALB_CMD                      (uint8_t)11  //command to calculate calibration factors


/** @var Postponed values (flag)
 *  @arg   = 0 - does not have postponed values
 *  @arg   = 1 - have postponed values
 */
extern uint8_t PLC_AO_POSTPONED;


/** @typedef AO channel settings
 */
typedef struct PlcAO_Set_t_
{
    //@var Channel number
    uint8_t ChNum;

    //@var Settings ID
    uint8_t SetID;

    //@var Settings value
    float SetVal;

} PlcAO_Set_t;


/** @def Default values
 */
#define PLC_AO_MODE_DEF                          PLC_AO_MODE_OFF
#define PLC_AO_SAFE_ALLOW_DEF                    BIT_FALSE
#define PLC_AO_SAFE_VAL_DEF                      PLC_AO_ANA_MIN


/** @brief  AO initialization.
 *  @param  none.
 *  @return none.
 */
void PlcAO_Init(void);


/** @brief  Set digital level to AO.
 *  @param  ChNumIn - channel number.
 *  @param  DigLvIn - digital level:
 *  @arg      = PLC_AO_DIG_MIN ... PLC_AO_DIG_MAX
 *  @return Result:
 *  @arg      = 0 - not set
 *  @arg      = 1 - set
 */
uint8_t PlcAO_SetDigLv(const uint8_t ChNumIn, const uint16_t DigLvIn);


/** @brief  Set analog level to AO.
 *  @param  ChNumIn - channel number.
 *  @param  AnaLvIn - analog level:
 *  @arg      = PLC_AO_ANA_MIN ... PLC_AO_ANA_MAX
 *  @param  KaIn - scale Ka-factor.
 *  @param  KbIn - scale Kb-factor.
 *  @return Result:
 *  @arg      = 0 - not set
 *  @arg      = 1 - set
 */
uint8_t PlcAO_SetAnaLv(const uint8_t ChNumIn, const float AnaLvIn, const float KaIn, const float KbIn);


#endif //PLC_AO_H
