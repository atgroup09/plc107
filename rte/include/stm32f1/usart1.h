/* @page usart1.h
 *       USART1 driver
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020-2022
 */

/** @note USART1
 *        System Bootloader, Beremiz debugger
 *        PA9  -> TX
 *        PA10 <- RX
 */

#ifndef PLC_USART1_H
#define PLC_USART1_H

#include "config.h"
#include "usart.h"
#include "rtos.h"
#include "plc_debug.h"
#include "rtos-task-log.h"


/** @def USART Settings
 */
#define PLC_USART1_BAUDRATE         (uint32_t)57600
#define PLC_USART1_DATABITS         (uint16_t)USART_WordLength_8b
#define PLC_USART1_STOPBITS         (uint16_t)USART_StopBits_1
#define PLC_USART1_PARITY           (uint16_t)USART_Parity_No
#define PLC_USART1_FLOW_CTRL        (uint16_t)USART_HardwareFlowControl_None
#define PLC_USART1_MODE             (uint16_t)(USART_Mode_Rx|USART_Mode_Tx)


/** @brief  USART1 initialization.
 *  @param  none.
 *  @return none.
 */
void PlcUsart1_Init(void);


//Debug serial port access functions
int dbg_serial_write(unsigned char *d, unsigned short n);
int dbg_serial_read(unsigned char *d, unsigned short n);


#endif //PLC_USART1_H
