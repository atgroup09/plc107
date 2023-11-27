/* @page app-do.h
 *       Application functions / DO
 *       2020-2022
 */

#ifndef APP_DO_H_
#define APP_DO_H_

#include <stdint.h>
#include "plc_abi.h"
#include "do.h"
#include "reg.h"
#include "rtos.h"


/** @def Result codes
 */
#define PLC_APP_DO_OK                  0  //OK
#define PLC_APP_DO_ERR_DON             1  //invalid channel number
#define PLC_APP_DO_ERR_M               2  //invalid mode
#define PLC_APP_DO_ERR_NOT_NORM        2  //the channel is not Normal
#define PLC_APP_DO_ERR_NOT_FAST        2  //the channel is not Fast
#define PLC_APP_DO_ERR_NOT_PWM         2  //the channel is not PWM


/** @brief DOMode.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param DOn  - channel number:
 *  @arg     = 0..7
 *  @param M - mode (see di.h).
 *  @param Om - set mode
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DOMode(BOOL *Ex, BYTE *DOn, BYTE *M, BYTE *Om, BYTE *Ok);


/** @brief DOVal.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param DOn  - channel number:
 *  @arg     = 0..7
 *  @param V  - output level:
 *  @arg     = 0
 *  @arg     = 1
 *  @param Ov - normal value
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DOVal(BOOL *Ex, BYTE *DOn, BOOL *V, BOOL *Ov, BYTE *Ok);


/** @brief DOFast.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param DOn  - channel number:
 *  @arg     = 0..7
 *  @param V  - output level:
 *  @arg     = 0
 *  @arg     = 1
 *  @param Ov - normal value
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DOFast(BOOL *Ex, BYTE *DOn, BOOL *V, BOOL *Ov, BYTE *Ok);


/** @brief DOPwm.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param En - PWM state:
 *  @arg     = false - off
 *  @arg     = true  - on
 *  @param DOn  - channel number:
 *  @arg     = 0..7
 *  @param Tm  - period (ms):
 *  @arg     = 100..4294967295
 *  @param D  - fill factor (%):
 *  @arg     = 0.0..100.0
 *  @param Ow - PWM state
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DOPwm(BOOL *Ex, BOOL *En, BYTE *DOn, DWORD *Tm, REAL *D, BOOL *Ow, BYTE *Ok);


/** @brief DOSafe.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param En - safe-mode state:
 *  @arg     = false - off
 *  @arg     = true  - on
 *  @param DOn  - channel number:
 *  @arg     = 0..7
 *  @param V  - output level for safe-mode:
 *  @arg     = 0
 *  @arg     = 1
 *  @param Ov - output level for safe-mode.
 *  @param Ow - safe-mode state
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DOSafe(BOOL *Ex, BOOL *En, BYTE *DOn, BOOL *V, BOOL *Ov, BOOL *Ow, BYTE *Ok);


#endif /* APP_DO_H_ */
