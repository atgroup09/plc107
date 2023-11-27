/* @page app-ao.h
 *       Application functions / AO
 *       2020-2022
 */

#ifndef APP_AO_H_
#define APP_AO_H_

#include <stdint.h>
#include "plc_abi.h"
#include "ao.h"
#include "reg.h"
#include "rtos.h"


/** @def Result codes
 */
#define PLC_APP_AO_OK                  0  //OK
#define PLC_APP_AO_ERR_AON             1  //invalid channel number
#define PLC_APP_AO_ERR_M               2  //invalid mode
#define PLC_APP_AO_ERR_NOT_NORM        2  //the channel is not Normal
#define PLC_APP_AO_ERR_NOT_FAST        2  //the channel is not Fast
#define PLC_APP_AO_ERR_SAFE            3  //the channel was set in Safe-value


/** @brief AOMode.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param AOn  - channel number.
 *  @param M - mode (see ao.h):
 *  @arg     = 0 — normal
 *  @arg     = 1 — fast
 *  @arg     = 3 – off
 *  @param Om - set mode
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_AOMode(BOOL *Ex, BYTE *AOn, BYTE *M, BYTE *Om, BYTE *Ok);


/** @brief AOVal.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param AOn - channel number.
 *  @param V - output level (Volt).
 *  @param Ov - normal value.
 *  @param Ok - result code.
 *  @return None.
 */
void PlcApp_AOVal(BOOL *Ex, BYTE *AOn, REAL *V, REAL *Ov, BYTE *Ok);


/** @brief AOFast.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param AOn  - channel number.
 *  @param V  - output level (Volt).
 *  @param Ov - fast value.
 *  @param Ok - result code.
 *  @return None.
 */
void PlcApp_AOFast(BOOL *Ex, BYTE *AOn, REAL *V, REAL *Ov, BYTE *Ok);


/** @brief AOSafe.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param En - safe-mode state:
 *  @arg     = false - off
 *  @arg     = true  - on
 *  @param AOn  - channel number.
 *  @param V  - output level for safe-mode (Volt).
 *  @param Ov - output level for safe-mode.
 *  @param Ow - safe-mode state.
 *  @param Ok - result code.
 *  @return None.
 */
void PlcApp_AOSafe(BOOL *Ex, BOOL *En, BYTE *AOn, REAL *V, REAL *Ov, BOOL *Ow, BYTE *Ok);


#endif /* APP_AO_H_ */
