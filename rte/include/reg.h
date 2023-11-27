/* @page reg-plc.h
 *       Registers
 *       2022
 */

#ifndef REG_H
#define REG_H

#include "reg-base.h"


/** @typedef RTE version (major minor) (packed)
 *           bit-fields
 */
typedef struct REG_RTE_VER_Pack_t_ {

    uint16_t Major:4;  //major
    uint16_t Minor:4;  //minor
    uint16_t Patch:4;  //patch

} REG_RTE_VER_Pack_t;

typedef union {

    REG_RTE_VER_Pack_t Pack;
    uint16_t Data;

}  REG_RTE_VER_Pack_ut;


/** @typedef RTE DDMM (day month) (packed)
 *           bit-fields
 */
typedef struct REG_RTE_DDMM_Pack_t_ {

    uint16_t DD:5;  //day
    uint16_t MM:5;  //month

} REG_RTE_DDMM_Pack_t;

typedef union {

    REG_RTE_DDMM_Pack_t Pack;
    uint16_t Data;

}  REG_RTE_DDMM_Pack_ut;



/** @brief  Init. registers.
 *  @param  None.
 *  @return The number of inited registers.
 */
uint16_t REG_Init(void);

#ifdef RTE_MOD_APP
/** @brief  Copy from ModBus (Data) Tables into Located variables.
 *  @param  None.
 *  @return The number of copied registers.
 */
uint16_t REG_CopyMbToApp(void);

/** @brief  Copy from Located variables into ModBus (Data) Tables.
 *  @param  None.
 *  @return The number of copied registers.
 */
uint16_t REG_CopyAppToMb(void);
#endif // RTE_MOD_APP


/** @brief  Set values by default.
 *  @param  None.
 *  @return None.
 */
void REG_SetDef(void);

#endif //REG_H
