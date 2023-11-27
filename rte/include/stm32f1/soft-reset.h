/* @page soft-reset.h
 *       Software reset
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#ifndef PLC_SOFT_RESET_H
#define PLC_SOFT_RESET_H

#include "config.h"


/** @brief  Software reset.
 *  @param  none.
 *  @return none.
 */
void Plc_SoftwareReset(void);

#endif //PLC_SOFT_RESET_H
