/* @page app-scale.h
 *       Application functions / Scale
 *       2020-2022
 */

#ifndef APP_SCALE_H_
#define APP_SCALE_H_

#include <stdint.h>
#include "plc_abi.h"
#include "scale.h"


/** @brief ScaleA_Ka.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param In1 - low  input value.
 *  @param In2 - high input value.
 *  @param Y1  - low  scaled value.
 *  @param Y2  - high scaled value.
 *  @param Ka  - previous Ka.
 *  @param OKa - result Ka.
 *  @return None.
 */
void PlcApp_ScaleA_Ka(BOOL *Ex, REAL *In1, REAL *In2, REAL *Y1, REAL *Y2, REAL *Ka, REAL *OKa);


/** @brief ScaleA_Kb.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param In1 - low  input value.
 *  @param In2 - high input value.
 *  @param Y1  - low  scaled value.
 *  @param Y2  - high scaled value.
 *  @param Kb  - previous Kb.
 *  @param OKb - result Kb.
 *  @return None.
 */
void PlcApp_ScaleA_Kb(BOOL *Ex, REAL *In1, REAL *In2, REAL *Y1, REAL *Y2, REAL *Kb, REAL *OKb);


/** @brief ScaleA.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param In - input value.
 *  @param Ka - Ka.
 *  @param Kb - Kb.
 *  @param Oy - result.
 *  @return None.
 */
void PlcApp_ScaleA(BOOL *Ex, REAL *In, REAL *Ka, REAL *Kb, REAL *Oy);


#endif /* APP_SCALE_H_ */
