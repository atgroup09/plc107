/* @page app.h
 *       Application functions
 *       2020-2022
 */

#ifndef APP_H_
#define APP_H_

#include <stdint.h>
#include "config.h"
#include "plc_abi.h"

#ifdef RTE_MOD_DI
#include "app-di.h"
#endif // RTE_MOD_DI

#ifdef RTE_MOD_DO
#include "app-do.h"
#endif // RTE_MOD_DO

#ifdef RTE_MOD_AI
#include "app-ai.h"
#endif // RTE_MOD_AI

#ifdef RTE_MOD_AO
#include "app-ao.h"
#endif // RTE_MOD_AO

#ifdef RTE_MOD_SOFT_RESET
#include "app-sys.h"
#endif // RTE_MOD_SOFT_RESET

#ifdef RTE_MOD_APP_TIM
#include "rtos-tim-app.h"
#endif // RTE_MOD_APP_TIM


/** @brief  Init. Application functions.
 *  @param  None.
 *  @return None.
 */
void PlcApp_InitFuncs(void);


#ifdef RTE_MOD_SOFT_RESET
/** @brief  Get SysTime.
 *  @param  None.
 *  @return None.
 */
void PlcApp_GetTime(IEC_TIME *CurrentTimeIn);
#endif // RTE_MOD_SOFT_RESET

#endif /* APP_H_ */
