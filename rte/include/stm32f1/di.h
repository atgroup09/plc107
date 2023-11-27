/* @page di.h
 *       Discrete Inputs
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

/** @note DI
 *        PE7  -> DI0
 *        PE8  -> DI1
 *        PE9  -> DI2
 *        PE10 -> DI3
 */

#ifndef PLC_DI_H
#define PLC_DI_H

#include "config.h"
#include "rtos.h"


/** @def DI channel: GPIO reference
 */
#define PLC_DI_00__PORT                          GPIOE
#define PLC_DI_00__PIN                           GPIO_Pin_7
#define PLC_DI_01__PORT                          GPIOE
#define PLC_DI_01__PIN                           GPIO_Pin_8
#define PLC_DI_02__PORT                          GPIOE
#define PLC_DI_02__PIN                           GPIO_Pin_9
#define PLC_DI_03__PORT                          GPIOE
#define PLC_DI_03__PIN                           GPIO_Pin_10


/** @def Channel number
 */
#define PLC_DI_00                                (uint8_t)0
#define PLC_DI_01                                (uint8_t)1
#define PLC_DI_02                                (uint8_t)2
#define PLC_DI_03                                (uint8_t)3


/** @def Quantity of channels
 */
#define PLC_DI_SZ                                (uint16_t)(PLC_DI_03+1)


/** @def    Test phase A of pair.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - the channel is not phase A of pair
 *  @arg      = 1 - the channel is phase A of pair
 */
#define PLC_DI_IS_PHASE_A(ChNumIn)               (uint8_t)((ChNumIn == PLC_DI_00 || ChNumIn == PLC_DI_02) ? BIT_TRUE : BIT_FALSE)

/** @def    Test phase B of pair.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - the channel is not phase B of pair
 *  @arg      = 1 - the channel is phase B of pair
 */
#define PLC_DI_IS_PHASE_B(ChNumIn)               (!PLC_DI_IS_PHASE_A(ChNumIn))


/** @def DI channel modes
 */
#define PLC_DI_MODE_NORM                         (uint8_t)0  //normal
#define PLC_DI_MODE_CNTR                         (uint8_t)1  //counter
#define PLC_DI_MODE_TACH                         (uint8_t)2  //tachometer
#define PLC_DI_MODE_INC1                         (uint8_t)3  //incremental encoder (counter)
#define PLC_DI_MODE_INC2                         (uint8_t)4  //incremental encoder (counter + tachometer)


/** @typedef DI pin
 */
typedef struct PlcDI_Pin_t_
{
    //@var GPIO-port
    GPIO_TypeDef *Port;

    //@var GPIO-pin
    uint16_t Pin;

} PlcDI_Pin_t;


/** @typedef DI channel
 *           packed data
 */
typedef struct PlcDI_Pack_t_
{
    //@var The channel number
    //@arg = 0..127
    uint32_t ChNum:7;

    //@var The channel mode
    //@arg = 0..4
    uint32_t Mode:4;

    //@var The channel normal value (0 or 1)
    //@arg = 0..1
    uint32_t Val:1;

    //@var Reset counters
    //@arg = 0 - no
    //@arg = 1 - yes
    uint32_t Reset:1;

    //@var Counter setpoint allow
    //@arg = 0 - no
    //@arg = 1 - yes
    uint32_t CntrSetpointAllow:1;

    //@var Counter setpoint reached
    //@arg = 0 - no
    //@arg = 1 - yes
    uint32_t CntrSetpointRes:1;

    //@var Tachometer setpoint allow
    //@arg = 0 - no
    //@arg = 1 - yes
    uint32_t TachSetpointAllow:1;

    //@var Tachometer setpoint reached
    //@arg = 0 - no
    //@arg = 1 - yes
    uint32_t TachSetpointRes:1;

    //@var Pair channel number
    //@arg = 0..127
    uint32_t ChNumPair:7;

} PlcDI_Pack_t;


/** @typedef DI channel
 *           Data from IRQ-handler
 */
typedef struct PlcDI_IRQ_t_
{
    //@var The channel number
    //@arg = 0..127
    uint8_t ChNum:7;

    //@var The channel value
    //@arg = 0..1
    uint8_t Val:1;

} PlcDI_IRQ_t;


/** @typedef DI channel
 */
typedef struct PlcDI_t_
{
    //@var Tachometer local counter
    uint16_t TachCntrVal;

    //@var Tachometer value
    uint16_t TachVal;

    //@var Tachometer setpoint (set)
    uint16_t TachSetpoint;

    //@var Counter value
    uint32_t CntrVal;

    //@var Counter setpoint (set)
    uint32_t CntrSetpoint;

    //@var Packed data
    PlcDI_Pack_t Pack;

    //@var Pin
    PlcDI_Pin_t *Pin;

} PlcDI_t;


/** @def DI channel settings ID
 */
#define PLC_DI_SET_CNTR_SETPOINT                 (uint8_t)0  //counter setpoint
#define PLC_DI_SET_CNTR_SETPOINT_ALLOW           (uint8_t)1  //counter setpoint allow
#define PLC_DI_SET_TACH_SETPOINT                 (uint8_t)2  //tachometer setpoint
#define PLC_DI_SET_TACH_SETPOINT_ALLOW           (uint8_t)3  //tachometer setpoint allow
#define PLC_DI_SET_RESET                         (uint8_t)4  //reset counters
#define PLC_DI_SET_MODE                          (uint8_t)5  //mode


/** @typedef DI channel settings
 */
typedef struct PlcDI_Set_t_
{
    //@var Channel number
    uint8_t ChNum;

    //@var Settings ID
    uint8_t SetID;

    //@var Settings value
    uint32_t SetVal;

} PlcDI_Set_t;


/** @def Default values
 */
#define PLC_DI_TACH_SETPOINT_DEF                 (uint16_t)0        //DI Tachometer setpoint
#define PLC_DI_TACH_SETPOINT_ALLOW_DEF            BIT_FALSE         //DI Tachometer setpoint allow
#define PLC_DI_CNTR_SETPOINT_DEF                 (uint32_t)0        //DI Counter setpoint
#define PLC_DI_CNTR_SETPOINT_ALLOW_DEF            BIT_FALSE         //DI Counter setpoint allow
#define PLC_DI_MODE_DEF                           PLC_DI_MODE_NORM


/** @brief  Init. DI.
 *  @param  none.
 *  @return none.
 */
void PlcDI_Init(void);


/** @brief  Send DI-channel value to Queue (T_DI).
 *  @param  PortIn  - GPIO port.
 *  @param  PinIn   - GPIO pin number.
 *  @param  ChNumIn - DI-channel number.
 *  @return RTOS HiTaskWoken-flag:
 *  @arg    = pdTRUE - if was interrupted high-priority task.
 */
portBASE_TYPE PlcDI_SendValue(GPIO_TypeDef *PortIn, const uint16_t PinIn, const uint16_t ChNumIn);


#endif //PLC_DI_H
