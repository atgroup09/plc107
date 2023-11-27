/* @page usart2.h
 *       USART2 driver
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020-2022
 */

/** @note USART2
 *        ModBus RTU Slave
 *        PA2 -> TX
 *        PA3 <- RX
 */

#ifndef PLC_USART2_H
#define PLC_USART2_H

#include "config.h"
#include "bit.h"
#include "usart.h"
#include "mbrtu.h"
#include "rtos.h"
#include "rtos-task-log.h"


/** @def USART Settings
 */
#define PLC_USART2_BAUDRATE         (uint32_t)115200
#define PLC_USART2_DATABITS         USART_WordLength_8b
#define PLC_USART2_STOPBITS         USART_StopBits_1
#define PLC_USART2_PARITY           USART_Parity_No
#define PLC_USART2_FLOW_CTRL        USART_HardwareFlowControl_None
#define PLC_USART2_MODE             USART_Mode_Rx|USART_Mode_Tx

/** @def DE-pin
 */
#define PLC_USART2_DE_PORT          0
#define PLC_USART2_DE_PIN           0


/** @brief  USART2 initialization.
 *  @param  none.
 *  @return none.
 */
void PlcUsart2_Init(void);

#endif //PLC_USART2_H
