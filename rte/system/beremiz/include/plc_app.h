/* @page plc_app.h
 *       PLC Application (YAPLC)
 *       2020-2022
 */

#ifndef PLC_APP_H_
#define PLC_APP_H_

#include "config.h"
#include "plc_abi.h"
#include "plc_glue_rte.h"
#include "rtos-task-log.h"


/** @def Application
 *       values by default
 */
#ifndef PLC_APP
#define PLC_APP                        ((plc_app_abi_t *)0x08020000)           //Pointer to application ABI-structure
#endif // PLC_APP

#ifndef PLC_APP_VER_MAJOR
#define PLC_APP_VER_MAJOR              (uint32_t)1                             //ABI-structure version (major)
#endif // PLC_APP_VER_MAJOR

#ifndef PLC_APP_VER_MINOR
#define PLC_APP_VER_MINOR              (uint32_t)0                             //ABI-structure version (minor)
#endif // PLC_APP_VER_MINOR

#ifndef PLC_APP_VER_PATCH
#define PLC_APP_VER_PATCH              (uint32_t)0                             //ABI-structure version (patch)
#endif // PLC_APP_VER_PATCH

#ifndef PLC_APP_HW_ID
#define PLC_APP_HW_ID                  (uint32_t)107                          //Hardware ID
#endif // PLC_APP_HW_ID


/** @def Application
 *       states
 */
#define PLC_APP_STATE_STOPED           (uint8_t)0x55
#define PLC_APP_STATE_STARTED          (uint8_t)0xAA


/** @var Application state (extern)
 */
extern uint8_t PLC_APP_STATE;


/** @brief  Init. ABI.
 *  @param  None.
 *  @return Result:
 *  @arg     = 0 - application is not loaded (not valid)
 *  @arg     = 1 - loaded (valid)
 */
uint8_t PlcApp_Init(void);


/** @brief  Start application.
 *  @param  none.
 *  @return none.
 */
void PlcApp_Start(void);


/** @brief  Stop application.
 *  @param  none.
 *  @return none.
 */
void PlcApp_Stop(void);


/** @brief  Run application.
 *  @param  none.
 *  @return none.
 */
void PlcApp_Run(void);


/** @brief  Test Located variable.
 *  @param  ZoneIn   - ID of zone           (plc_app.v_type).
 *  @param  TypeSzIn - ID of data type size (plc_app.v_size).
 *  @param  GroupIn  - ID of group          (plc_app.proto).
 *  @param  A00In    - ID of subgroup 0     (plc_app.a_data[0]) (<0 is not used).
 *  @param  A01In    - ID of subgroup 1     (plc_app.a_data[1]) (<0 is not used).
 *  @param  A02In    - ID of subgroup 2     (plc_app.a_data[2]) (<0 is not used).
 *  @return Pointer to located variable structure or 0 (if located variable is not supported)
 */
plc_loc_dsc_t *PlcApp_TestLocVar(const uint8_t ZoneIn, const uint8_t TypeSzIn, const uint16_t GroupIn, const int32_t A00In, const int32_t A01In, const int32_t A02In);


#ifdef DEBUG
/** @brief  Debug print of PLC_APP_CURR->l_tab[i].
 *  @param  None.
 *  @return None.
 */
void PlcApp_DebugPrint(void);

/** @brief  Debug print of PLC_APP item.
 *  @param  None.
 *  @return None.
 */
void PlcApp_DebugPrintItem(plc_loc_dsc_t *pAppVarIn);
#endif // DEBUG


#endif // PLC_APP_H_
