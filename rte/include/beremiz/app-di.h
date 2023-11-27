/* @page app-di.h
 *       Application functions / DI
 *       2020-2022
 */

#ifndef APP_DI_H_
#define APP_DI_H_

#include <stdint.h>
#include "plc_abi.h"
#include "di.h"
#include "reg.h"
#include "rtos.h"


/** @def Result codes
 */
#define PLC_APP_DI_OK                  0  //OK
#define PLC_APP_DI_ERR_DIN             1  //invalid channel number
#define PLC_APP_DI_ERR_M               2  //invalid mode
#define PLC_APP_DI_ERR_NOT_NORM        2  //the channel is not Normal
#define PLC_APP_DI_ERR_NOT_TACH        2  //the channel is not Tachometer
#define PLC_APP_DI_ERR_NOT_CNTR        2  //the channel is not Counter
#define PLC_APP_DI_ERR_INC             3  //try to set inc-mode for not Master-channels


/** @brief DIMode.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param DIn  - channel number:
 *  @arg     = 0..7
 *  @param M - mode (see di.h).
 *  @param Om - set mode
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DIMode(BOOL *Ex, BYTE *DIn, BYTE *M, BYTE *Om, BYTE *Ok);


/** @brief DI.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param DIn  - channel number:
 *  @arg     = 0..7
 *  @param Ov - normal value
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DIVal(BOOL *Ex, BYTE *DIn, BOOL *Ov, BYTE *Ok);


/** @brief DICntT.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param DIn  - channel number:
 *  @arg     = 0..7
 *  @param Ref - reference
 *  @param RefEn - allow to work by reference
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param Ov   - tachometer value
 *  @param Oref - reference status
 *  @param Ok   - result code
 *  @return None.
 */
void PlcApp_DICntT(BOOL *Ex, BYTE *DIn, WORD *Ref, BOOL *RefEn, WORD *Ov, BOOL *Oref, BYTE *Ok);


/** @brief DICnt.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param DIn  - channel number:
 *  @arg     = 0..7
 *  @param Ref - reference
 *  @param RefEn - allow to work by reference
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param Ov   - counter value
 *  @param Oref - reference status
 *  @param Ok   - result code
 *  @return None.
 */
void PlcApp_DICnt(BOOL *Ex, BYTE *DIn, DWORD *Ref, BOOL *RefEn, DWORD *Ov, BOOL *Oref, BYTE *Ok);


/** @brief DICntRst.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param DIn  - channel number:
 *  @arg     = 0..7
 *  @param Rst - reset command
 *  @arg     = false - no reset
 *  @arg     = true  - reset
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DICntRst(BOOL *Ex, BYTE *DIn, BOOL *Rst, BYTE *Ok);


/** @brief DIEnc.
 *  @param Ex - allow to execution:
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param DIn  - channel number:
 *  @arg     = 0..7
 *  @param RefA - reference of phase A counter
 *  @param RefAEn - allow to work of phase A counter by reference
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param RefB - reference of phase B counter
 *  @param RefBEn - allow to work of phase B counter by reference
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param RefT - reference of tachometer
 *  @param RefTEn - allow to work of tachometer by reference
 *  @arg     = false - not allow
 *  @arg     = true  - allow
 *  @param OA - phase A counter value
 *  @param OAref - phase A counter reference status
 *  @param OB - phase B counter value
 *  @param OBref - phase B counter reference status
 *  @param OT - tachometer value
 *  @param OTref - tachometer reference status
 *  @param Ok - result code
 *  @return None.
 */
void PlcApp_DIEnc(BOOL *Ex, BYTE *DIn, DWORD *RefA, BOOL *RefAEn, DWORD *RefB, BOOL *RefBEn, WORD *RefT, BOOL *RefTEn, DWORD *OutA, BOOL *OAref, DWORD *OutB, BOOL *OBref, WORD *OutT, BOOL *OTref, BYTE *Ok);


#endif /* APP_DI_H_ */
