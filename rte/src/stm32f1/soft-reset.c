/* @page soft-reset.h
 *       Software reset
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#include "soft-reset.h"


/** @brief  Software reset.
 *  @param  none.
 *  @return none.
 */
void Plc_SoftwareReset(void)
{
    SCB->AIRCR  = (uint32_t)((0x5FAUL << SCB_AIRCR_VECTKEY_Pos)  |
                           (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
                            SCB_AIRCR_SYSRESETREQ_Msk);

    //wait until reset
    while(1);
}
