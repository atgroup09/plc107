/* @page do.h
 *       Discrete Outputs
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

/** @note
 *        PE11 - DO0
 *        PE12 - DO1
 *        PE13 - DO2
 *        PE14 - DO3
 */

#ifndef PLC_DO_H
#define PLC_DO_H

#include "config.h"
#include "rtos.h"
#include "rtos-task-log.h"


/** @def DO Pin-states
 */
#define PLC_DO_STATE_OFF                         (uint8_t)0
#define PLC_DO_STATE_ON                          (uint8_t)1

/** @def DO Pin-modes
 */
#define PLC_DO_PP                                (uint8_t)0  //push-pull
#define PLC_DO_OD                                (uint8_t)1  //open-drain


/** @def DO channel periphery
 */
#define PLC_DO_00__PORT                          GPIOE
#define PLC_DO_00__PIN                           GPIO_Pin_11
#define PLC_DO_00__PIN_MODE                      PLC_DO_PP
#define PLC_DO_01__PORT                          GPIOE
#define PLC_DO_01__PIN                           GPIO_Pin_12
#define PLC_DO_01__PIN_MODE                      PLC_DO_PP
#define PLC_DO_02__PORT                          GPIOE
#define PLC_DO_02__PIN                           GPIO_Pin_13
#define PLC_DO_02__PIN_MODE                      PLC_DO_PP
#define PLC_DO_03__PORT                          GPIOE
#define PLC_DO_03__PIN                           GPIO_Pin_14
#define PLC_DO_03__PIN_MODE                      PLC_DO_PP


/** @def DO channel numbers
 */
#define PLC_DO_00                                (uint8_t)0
#define PLC_DO_01                                (uint8_t)1
#define PLC_DO_02                                (uint8_t)2
#define PLC_DO_03                                (uint8_t)3


/** @def Quantity of DO channels
 */
#define PLC_DO_SZ                                (uint16_t)(PLC_DO_03+1)


/** @def DO channel modes
 */
#define PLC_DO_MODE_NORM                         (uint8_t)0  //normal
#define PLC_DO_MODE_FAST                         (uint8_t)1  //fast
#define PLC_DO_MODE_PWM                          (uint8_t)2  //PWM
#define PLC_DO_MODE_OFF                          (uint8_t)3  //off


/** @def PWM Period limites (ms)
 */
#define PLC_DO_PWM_PERIOD__MIN                   (uint32_t)100
#define PLC_DO_PWM_PERIOD__1000                  (uint32_t)1000
#define PLC_DO_PWM_PERIOD__MAX                   (uint32_t)4294967295


/** @def PWM Fill factor limites (%)
 */
#define PLC_DO_PWM_FILL_FACTOR__MIN              (float)0.0
#define PLC_DO_PWM_FILL_FACTOR__50               (float)50.0
#define PLC_DO_PWM_FILL_FACTOR__MAX              (float)100.0

/** @def PWM pulse length limites (us)
 */
#define PLC_DO_PWM_LEN__MIN                      (uint8_t)100


/** @typedef DO pin
 */
typedef struct PlcDO_Pin_t_
{
    //@var GPIO-port
    GPIO_TypeDef *Port;

    //@var GPIO-pin
    uint16_t Pin;

    //@var GPIO-pin mode
    uint8_t PinMode;

} PlcDO_Pin_t;


/** @typedef DO channel
 *           packed data
 */
typedef struct PlcDO_Pack_t_
{
    //@var The channel number
    //@arg = 0..127
    uint32_t ChNum:7;

    //@var The channel mode
    //@arg = 0..4
    uint32_t Mode:4;

    //@var The channel normal value
    //@arg = 0..1
    uint32_t Val:1;

    //@var The channel normal postpend value
    //@arg = 0..1
    uint32_t PostponedVal:1;

    //@var The channel normal postpend flag
    //@arg = 0..1
    uint32_t Postponed:1;

    //@var The channel fast value
    //@arg = 0..1
    uint32_t FastVal:1;

    //@var Allow PWM
    //@arg = 0..1
    uint32_t PwmAllow:1;

    //@var Allow Safe-mode
    //@arg = 0..1
    uint32_t SafeAllow:1;

    //@var Safe-mode value
    //@arg = 0..1
    uint32_t SafeVal:1;

} PlcDO_Pack_t;


/** @typedef DO channel
 */
typedef struct PlcDO_t_
{
    //@var Packed data
    PlcDO_Pack_t Pack;

    //@var Pin
    PlcDO_Pin_t *Pin;

    //@var PWM period (ms)
    uint32_t PwmPeriod;

    //@var PWM fill factor (%)
    float PwmFillFactor;

    //@var PWM length of FALSE-value (us)
    uint64_t PwmLen0;

    //@var PWM length of TRUE-value (us)
    uint64_t PwmLen1;

} PlcDO_t;


/** @typedef DO PWM
 */
typedef struct PlcDO_PWM_t_
{
    //@var Status
    //@arg = 0 - FALSE-value
    //@arg = 1 - TRUE-value
    uint32_t Stat:1;

    //@var Ticks (us)
    uint64_t Ticks;

} PlcDO_PWM_t;


/** @def DO channel settings ID
 */
#define PLC_DO_SET_NORM_VAL                      (uint8_t)0  //normal value
#define PLC_DO_SET_FAST_VAL                      (uint8_t)1  //fast value
#define PLC_DO_SET_PWM_FILL_FACTOR               (uint8_t)2  //PWM fill factor
#define PLC_DO_SET_PWM_PERIOD                    (uint8_t)3  //PWM period
#define PLC_DO_SET_PWM_ALLOW                     (uint8_t)4  //PWM allow
#define PLC_DO_SET_MODE                          (uint8_t)6  //mode
#define PLC_DO_SET_SAFE_ALLOW                    (uint8_t)8  //safe-mode allow
#define PLC_DO_SET_SAFE_VAL                      (uint8_t)9  //safe-mode value
#define PLC_DO_SET_POSTPONED_VAL                 (uint8_t)10 //normal value (postponed)
#define PLC_DO_SET_POSTPONED_APPLY               (uint8_t)11 //normal value (apply all postponed valued)


/** @def Default values
 */
#define PLC_DO_PWM_PERIOD_DEF                    PLC_DO_PWM_PERIOD__1000
#define PLC_DO_PWM_FILL_FACTOR_DEF               PLC_DO_PWM_FILL_FACTOR__MIN
#define PLC_DO_MODE_DEF                          PLC_DO_MODE_NORM
#define PLC_DO_SAFE_ALLOW_DEF                    BIT_FALSE
#define PLC_DO_SAFE_VAL_DEF                      BIT_FALSE


/** @var Postponed values (flag)
 *  @arg   = 0 - does not have postponed values
 *  @arg   = 1 - have postponed values
 */
extern uint8_t PLC_DO_POSTPONED;


/** @typedef DO channel settings
 */
typedef struct PlcDO_Set_t_
{
    //@var Channel number
    uint8_t ChNum;

    //@var Settings ID
    uint8_t SetID;

    //@var Settings value
    float SetVal;

} PlcDO_Set_t;


/** @brief  Init. DO.
 *  @param  none.
 *  @return none.
 */
void PlcDO_Init(void);


/** @brief DO on.
 *  @param  PortIn - port;
 *  @param  PinIn - pin number;
 *  @param  PinModeIn - pin mode:
 *  @arg      = 0 - push-pull,
 *  @arg      = 1 - open-drain.
 *  @return none.
 */
void PlcDO_On(GPIO_TypeDef *PortIn, const uint16_t PinIn, const uint8_t PinModeIn);


/** @brief DO off.
 *  @param  PortIn - port;
 *  @param  PinIn - pin number;
 *  @param  PinModeIn - pin mode:
 *  @arg      = 0 - push-pull,
 *  @arg      = 1 - open-drain.
 *  @return none.
 */
void PlcDO_Off(GPIO_TypeDef *PortIn, const uint16_t PinIn, const uint8_t PinModeIn);


/** @brief DO toggle.
 *  @param  PortIn - port;
 *  @param  PinIn - pin number;
 *  @param  PinModeIn - pin mode:
 *  @arg      = 0 - push-pull,
 *  @arg      = 1 - open-drain.
 *  @return Current Pin-status:
 *  @arg      = 0 - off,
 *  @arg      = 1 - on.
 */
uint8_t PlcDO_Toggle(GPIO_TypeDef *PortIn, const uint16_t PinIn, const uint8_t PinModeIn);


/** @brief  Set DO state.
 *  @param  PortIn - port;
 *  @param  PinIn - pin number;
 *  @param  PinModeIn - pin mode:
 *  @arg      = 0 - push-pull,
 *  @arg      = 1 - open-drain.
 *  @param  StateIn - state:
 *  @arg      = 0 - off,
 *  @arg      = 1 - on.
 *  @return none.
 */
void PlcDO_Set(GPIO_TypeDef *PortIn, const uint16_t PinIn, const uint8_t PinModeIn, const uint8_t StateIn);


#endif //PLC_DO_H
