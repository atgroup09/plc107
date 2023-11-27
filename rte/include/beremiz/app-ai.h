/* @page app-ai.h
 *       Application functions / AI
 *       2020-2022
 */

#ifndef APP_AI_H_
#define APP_AI_H_

#include <stdint.h>
#include "plc_abi.h"
#include "ai.h"
#include "reg.h"
#include "rtos.h"


/** @def Result codes
 */
#define PLC_APP_AI_OK                  0  //OK
#define PLC_APP_AI_ERR_CHN             1  //invalid channel number
#define PLC_APP_AI_ERR_M               2  //invalid mode


/** @brief AIMode.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param AIn - channel number.
 *  @param M   - mode (see ai.h).
 *  @param Om  - set mode.
 *  @param Os  - status code.
 *  @param Ok  - result code.
 *  @return None.
 */
void PlcApp_AIMode(BOOL *Ex, BYTE *AIn, BYTE *M, BYTE *Om, BYTE *Os, BYTE *Ok);


/** @brief AIVal.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param AIn - channel number.
 *  @param Ov  - value.
 *  @param Os  - status code.
 *  @param Ok  - result code.
 *  @return None.
 */
void PlcApp_AIVal(BOOL *Ex, BYTE *AIn, REAL *Ov, BYTE *Os, BYTE *Ok);


#endif /* APP_AI_H_ */
