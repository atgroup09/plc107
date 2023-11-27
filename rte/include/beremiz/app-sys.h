/* @page app-sys.h
 *       Application functions / System
 *       2020-2022
 */

#ifndef APP_SYS_H_
#define APP_SYS_H_

#include <stdint.h>
#include "plc_abi.h"
#include "soft-reset.h"


/** @brief Software Reset.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @return None.
 */
void PlcApp_SoftwareReset(BOOL Ex);


#endif /* APP_SYS_H_ */
