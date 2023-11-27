/* @page reg-base.h
 *       Registers: base
 *       2022
 */

#ifndef REG_BASE_H
#define REG_BASE_H

#include <stdint.h>
#include "config.h"
#include "bit.h"
#include "type.h"
#include "reg-map.h"
#include "plc_abi.h"

#ifdef RTE_MOD_REG_MONITOR
#include "rtos.h"
#endif // RTE_MOD_REG_MONITOR

#ifdef RTE_MOD_APP
#include "plc_app.h"
#endif // RTE_MOD_APP

#ifdef DEBUG_REG
#include "rtos-task-log.h"
#endif // DEBUG_REG


/** @typedef Register
 */
typedef struct REG_t_
{
    //@var Unique ID of group/subgroup
    uint8_t GID;

    //@var Position in group/subgroup
    uint8_t iGroup;

    //@var Position in REGS
    uint16_t iReg;

    //@var Data type ID (type.h)
    uint8_t Type;

    //@var Get size (words) of data type (type.h)
    uint8_t Wsz;

    //@var Data Table ID (reg-map.h)
    uint8_t  DataTable;

    //@var Pointer to ModBus (Data) table
    void *pMbVar;

#ifdef RTE_MOD_APP
    //@var Pointer to Application located variable
    plc_loc_dsc_t *pAppVar;
#endif // RTE_MOD_APP

    //@var ModBus Table ID (mbrtu.h)
    uint8_t  MbTable;

    //@var ModBus Address
    uint16_t MbAddr;

#ifdef RTE_MOD_EEPROM
    //@var EEPROM Address (-1 - unused, >=0 - used) (eeprom.h)
    int32_t EeAddr;

    //@var EEPROM Area ID (0 - unused, 1 - system, 2 - user)  (eeprom.h)
    uint8_t EeAreaID;
#endif // RTE_MOD_EEPROM

    //@var Use Change-monitoring (0 - off, 1 - on)
    uint8_t Monitor;

} REG_t;


/** @typedef System states (1)
 *           bit-fields
 */
typedef struct REG_SysStat1_Pack_t_ {

    //Application load-status
    //  = 0 - not loaded
    //  = 1 - loaded
    uint16_t AppInited:1;

    //Application run-status
    //  = 0 - not run
    //  = 1 - run
    uint16_t AppRun:1;

    //Application run-first-cycle-status
    //  = 0 - first cycle is not completed
    //  = 1 - completed
    uint16_t AppRun1:1;

} REG_SysStat1_Pack_t;

typedef union {

    REG_SysStat1_Pack_t Pack;
    uint16_t Data;

}  REG_SysStat1_Pack_ut;

/** @var System statuses (1)
 */
extern REG_SysStat1_Pack_ut PLC_SYS_STAT1;


/** @def Destination of copy
 *       *_TO_MB, *_TO_ALL with change-monitoring
 */
#ifdef RTE_MOD_APP
#define REG_COPY_APP_TO_MB              0  //copy Located variable into Data Table
#define REG_COPY_MB_TO_APP              1  //copy Data Table into Located variable
#define REG_COPY_VAR_TO_APP             3  //copy Variable into Located variable
#endif // RTE_MOD_APP
#define REG_COPY_MB_TO_VAR              2  //copy Data Table into Variable
#define REG_COPY_VAR_TO_MB              4  //copy Variable into Data Table
#define REG_COPY_VAR_TO_ALL             5  //copy Variable into Located variable, Data Table

/** @def Destination of copy
 *       *_TO_MB, *_TO_ALL without change-monitoring
 */
#ifdef RTE_MOD_APP
#define REG_COPY_APP_TO_MB__NO_MON      10
#endif // RTE_MOD_APP
#define REG_COPY_VAR_TO_MB__NO_MON      14
#define REG_COPY_VAR_TO_ALL__NO_MON     15


/** @brief  Get pointer to register by position in REGS.
 *  @param  IDxIn - position in REGS.
 *  @return Pointer to register or 0 if error.
 */
REG_t *REG_GetByIDx(const uint16_t IDxIn);

/** @brief  Get pointer to register by start position.
 *  @param  SPosIn   - start position of register group in REGS (ex.: REG_DI_NORM_VAL__POS).
 *  @param  iGroupIn - position of register in the group (>= 0) (iGroup).
 *  @return Pointer to register or 0 if error.
 */
REG_t *REG_GetByPos(const uint16_t SPosIn, const int32_t iGroupIn);

/** @brief  Get pointer to register by ModBus address.
 *  @param  MbTableIn - ModBus Table ID (mbrtu.h).
 *  @param  MbAddrIn  - ModBus Register address.
 *  @return Pointer to register or 0 if error.
 */
REG_t *REG_GetByMbAddr(const uint8_t MbTableIn, const uint16_t MbAddrIn);


#ifdef RTE_MOD_REG_MONITOR

/** @brief  Send change-monitoring status to Queue (by REG_t).
 *  @param  QueueIn - target queue.
 *  @param  RegIn   - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 */
uint8_t REG_MonitorSendToQueue(REG_t *RegIn, QueueHandle_t QueueIn);

/** @brief  Send change-monitoring status to Queue (RTOS_Q_DataRegMonitor queue) (by REG_t).
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 */
uint8_t REG_MonitorSendToQueueData(REG_t *RegIn);

/** @brief  Change-monitoring (by REG_t).
 *  @param  RegIn     - pointer to register.
 *  @param  QueueIn   - target queue.
 *  @param  ValIn     - current register value.
 *  @param  ValPrevIn - previous register value.
 *  @return Result:
 *  @arg      = 0 - not changed
 *  @arg      = 1 - changed
 */
uint8_t REG_Monitor(REG_t *RegIn, QueueHandle_t QueueIn, const uint16_t ValIn, const uint16_t ValPrevIn);

/** @brief  Change-monitoring (by position in REGS).
 *  @param  IDxIn     - position in REGS.
 *  @param  QueueIn   - target queue.
 *  @param  ValIn     - current register value.
 *  @param  ValPrevIn - previous register value.
 *  @return Result:
 *  @arg      = 0 - not changed
 *  @arg      = 1 - changed
 */
uint8_t REG_MonitorByIDx(const uint16_t IDxIn, QueueHandle_t QueueIn, const uint16_t ValIn, const uint16_t ValPrevIn);

/** @brief  Change-monitoring (by ModBus Address).
 *  @param  MbTableIn - ModBus table ID.
 *  @param  MbAddrIn  - ModBus address of register.
 *  @param  QueueIn   - target queue.
 *  @param  ValIn     - current register value.
 *  @param  ValPrevIn - previous register value.
 *  @param  IDxIn     - pointer to store register position in REGS or 0.
 *  @return Result:
 *  @arg      = 0 - not changed
 *  @arg      = 1 - changed
 */
uint8_t REG_MonitorByMbAddr(const uint8_t MbTableIn, const uint16_t MbAddrIn, QueueHandle_t QueueIn, const uint16_t ValIn, const uint16_t ValPrevIn, uint16_t *IDxIn);

/** @brief  Change-monitoring (RTOS_Q_DataRegMonitor queue) (by REG_t).
 *  @param  RegIn     - pointer to register.
 *  @param  ValIn     - current register value.
 *  @param  ValPrevIn - previous register value.
 *  @return Result:
 *  @arg      = 0 - not changed
 *  @arg      = 1 - changed
 */
uint8_t REG_MonitorForQueueData(REG_t *RegIn, const uint16_t ValIn, const uint16_t ValPrevIn);

/** @brief  Change-monitoring (RTOS_Q_DataRegMonitor queue) (by ModBus Address).
 *  @param  MbTableIn - ModBus table ID.
 *  @param  MbAddrIn  - ModBus address of register.
 *  @param  ValIn     - current register value.
 *  @param  ValPrevIn - previous register value.
 *  @param  IDxIn     - pointer to store register position in REGS or 0.
 *  @return Result:
 *  @arg      = 0 - not changed
 *  @arg      = 1 - changed
 */
uint8_t REG_MonitorForQueueDataByMbAddr(const uint8_t MbTableIn, const uint16_t MbAddrIn, const uint16_t ValIn, const uint16_t ValPrevIn, uint16_t *IDxIn);

#endif // RTE_MOD_REG_MONITOR


/** @brief  Copy words (+ change-monitoring multibyte values).
 *  @param  FromIn    - pointer to source buffer of words.
 *  @param  FromSzIn  - size of source buffer of words.
 *  @param  ToIn      - pointer to destination buffer of words.
 *  @param  MbTableIn - ModBus table ID (mbrtu.h).
 *  @param  MbAddrIn  - ModBus address.
 *  @return Size of copied words.
 *  @note
 *  MbTableIn and MbAddrIn are used to get REG_t from REGS for change-monitoring.
 */
uint8_t REG_CopyWords(const uint16_t *FromIn, const uint16_t FromSzIn, uint16_t *ToIn, const uint8_t MbTableIn, const uint16_t MbAddrIn);


/** @brief  Copy a value into ModBus (Data) Table.
 *  @param  TypeIn      - data type of value (type.h).
 *  @param  ValueBitIn  - pointer to buffer of bit-value (for Boolean Data Table).
 *  @param  ValueWordIn - pointer to buffer of word-value (for Numeric Data Table).
 *  @param  MbTableIn   - ModBus (Data) Table ID (mbrtu.h).
 *  @param  MbVarIn     - pointer to ModBus (Data) Table register.
 *  @param  MonIn       - change-monitoring:
 *  @arg      = 0 - off
 *  @arg      = 1 - on
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note   Size of copied data by TypeIn.
 */
uint8_t REG_CopyValueToMb(const uint8_t TypeIn, const uint8_t *ValueBitIn, const uint16_t *ValueWordIn, const uint8_t MbTableIn, const uint16_t MbAddrIn, void *MbVarIn, uint8_t MonIn);


/** @brief  Copy a value from Word-buffer into ModBus (Data) Table.
 *  @param  RegIn     - pointer to register (REG_t).
 *  @param  FromIn    - pointer to Word-buffer.
 *  @param  FromSzIn  - size of Word-buffer (<= size of register value type in words: __WSZ; type.h).
 *  @param  FromOrdIn - byte ordering type of Word-buffer (type.h).
 *  @param  ZeroedIn  - zeroed Word-buffer:
 *  @arg      = 0 - no,
 *  @arg      = 1 - yes.
 *  @param  MonIn - change-monitoring:
 *  @arg      = 0 - off
 *  @arg      = 1 - on
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 */
uint8_t REG_CopyWordsToMb(REG_t *RegIn, uint16_t *FromIn, const uint8_t FromSzIn, const uint8_t FromOrdIn, const uint8_t ZeroedIn, const uint8_t MonIn);


/** @brief  Copy a value from ModBus (Data) Table.
 *  @param  TypeIn      - data type of value (type.h).
 *  @param  ValueBitIn  - pointer to buffer of bit-value (for Boolean Data Table).
 *  @param  ValueWordIn - pointer to buffer of word-value (for Numeric Data Table).
 *  @param  MbTableIn   - ModBus (Data) Table ID (mbrtu.h).
 *  @param  MbVarIn     - pointer to ModBus (Data) Table register.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note   Size of copied data by TypeIn.
 */
uint8_t REG_CopyValueFromMb(const uint8_t TypeIn, uint8_t *ValueBitIn, uint16_t *ValueWordIn, const uint8_t MbTableIn, void *MbVarIn);


/** @brief  Copy a value from Data Table into Word-buffer.
 *  @param  RegIn    - pointer to register (REG_t).
 *  @param  ToIn     - pointer to Word-buffer.
 *  @param  ToSzIn   - size of Word-buffer (<= size of register value type in words: __WSZ; type.h).
 *  @param  ToOrdIn  - byte ordering type of Word-buffer (type.h).
 *  @param  ZeroedIn - zeroed Word-buffer:
 *  @arg      = 0 - no,
 *  @arg      = 1 - yes.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 */
uint8_t REG_CopyWordsFromMb(REG_t *RegIn, uint16_t *ToIn, const uint8_t ToSzIn, const uint8_t ToOrdIn, const uint8_t ZeroedIn);

#ifdef RTE_MOD_APP
/** @brief  Copy unsigned numeric value from Located variable into ModBus (Data) Table.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsignedAppToMb(REG_t *RegIn);
#endif // RTE_MOD_APP

/** @brief  Copy unsigned numeric value from ModBus (Data) Table into Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsignedMbToVar(REG_t *RegIn, void *VarIn);

#ifdef RTE_MOD_APP
/** @brief  Copy unsigned numeric value from ModBus (Data) Table into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsignedMbToApp(REG_t *RegIn);
#endif // RTE_MOD_APP

/** @brief  Copy unsigned numeric value from Variable into ModBus (Data) Table.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsignedVarToMb(REG_t *RegIn, const void *VarIn);

#ifdef RTE_MOD_APP
/** @brief  Copy unsigned numeric value from Variable into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsignedVarToApp(REG_t *RegIn, const void *VarIn);
#endif // RTE_MOD_APP

/** @brief  Copy unsigned numeric value.
 *  @param  RegIn - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported BOOL, BYTE, WORD, DWORD, LWORD register types.
 */
uint8_t REG_CopyUnsigned(REG_t *RegIn, const uint8_t DstIn, void *VarIn);

#ifdef RTE_MOD_APP
/** @brief  Copy signed numeric value from Located variable into ModBus (Data) Table.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySignedAppToMb(REG_t *RegIn);
#endif // RTE_MOD_APP

/** @brief  Copy signed numeric value from ModBus (Data) Table into Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySignedMbToVar(REG_t *RegIn, void *VarIn);

#ifdef RTE_MOD_APP
/** @brief  Copy signed numeric value from ModBus (Data) Table into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySignedMbToApp(REG_t *RegIn);
#endif // RTE_MOD_APP

/** @brief  Copy signed numeric value from Variable into ModBus (Data) Table.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySignedVarToMb(REG_t *RegIn, const void *VarIn);

#ifdef RTE_MOD_APP
/** @brief  Copy signed numeric value from Variable into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySignedVarToApp(REG_t *RegIn, const void *VarIn);
#endif // RTE_MOD_APP

/** @brief  Copy signed numeric value.
 *  @param  RegIn - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported SINT, INT, DINT, LINT register types.
 */
uint8_t REG_CopySigned(REG_t *RegIn, const uint8_t DstIn, void *VarIn);

#ifdef RTE_MOD_APP
/** @brief  Copy float numeric value from Located variable into ModBus (Data) Table.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloatAppToMb(REG_t *RegIn);
#endif // RTE_MOD_APP

/** @brief  Copy float numeric value from ModBus (Data) Table into Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloatMbToVar(REG_t *RegIn, void *VarIn);

#ifdef RTE_MOD_APP
/** @brief  Copy float numeric value from ModBus (Data) Table into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloatMbToApp(REG_t *RegIn);
#endif // RTE_MOD_APP

/** @brief  Copy float numeric value from Variable into ModBus (Data) Table.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloatVarToMb(REG_t *RegIn, const void *VarIn);

#ifdef RTE_MOD_APP
/** @brief  Copy float numeric value from Variable into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloatVarToApp(REG_t *RegIn, const void *VarIn);
#endif // RTE_MOD_APP

/** @brief  Copy float numeric value.
 *  @param  RegIn - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported FLOAT, REAL register types.
 */
uint8_t REG_CopyFloat(REG_t *RegIn, const uint8_t DstIn, void *VarIn);

#ifdef RTE_MOD_APP
/** @brief  Copy double numeric value from Located variable into ModBus (Data) Table.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDoubleAppToMb(REG_t *RegIn);
#endif // RTE_MOD_APP

/** @brief  Copy double numeric value from ModBus (Data) Table into Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDoubleMbToVar(REG_t *RegIn, void *VarIn);

#ifdef RTE_MOD_APP
/** @brief  Copy double numeric value from ModBus (Data) Table into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDoubleMbToApp(REG_t *RegIn);
#endif // RTE_MOD_APP

/** @brief  Copy double numeric value from Variable into ModBus (Data) Table.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not float numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDoubleVarToMb(REG_t *RegIn, const void *VarIn);

#ifdef RTE_MOD_APP
/** @brief  Copy double numeric value from Variable into Located Variable.
 *  @param  RegIn - pointer to register.
 *  @param  VarIn - pointer to Variable.
 *  @return Result:
 *  @arg      = 0 - error (if register type is not double numeric)
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDoubleVarToApp(REG_t *RegIn, const void *VarIn);
#endif // RTE_MOD_APP

/** @brief  Copy double numeric value.
 *  @param  RegIn - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 *   Supported DOUBLE, LREAL register types.
 */
uint8_t REG_CopyDouble(REG_t *RegIn, const uint8_t DstIn, void *VarIn);


/** @brief  Copy single register.
 *  @param  RegIn - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 */
uint8_t REG_CopyReg(REG_t *RegIn, const uint8_t DstIn, void *VarIn);


/** @brief  Copy any numeric value to single register.
 *  @param  RegIn     - pointer to register.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn     - pointer to Variable.
 *  @param  VarTypeIn - type of Variable:
 *  @arg      = TYPE_BYTE
 *            = TYPE_WORD
 *            = TYPE_DWORD
 *            = TYPE_LWORD
 *            = TYPE_SINT
 *            = TYPE_INT
 *            = TYPE_DINT
 *            = TYPE_LINT
 *            = TYPE_FLOAT
 *            = TYPE_DOUBLE
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 */
uint8_t REG_CopyVar(REG_t *RegIn, const uint8_t DstIn, const void *VarIn, const uint8_t VarTypeIn);


/** @brief  Copy single register (by register position in REGS).
 *  @param  RegPosIn - position of register in REGS.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return Result:
 *  @arg      = 0 - error
 *  @arg      = 1 - OK
 *  @note
 *   Type of Reg must be eq. type of Var!
 */
uint8_t REG_CopyRegByPos(const uint16_t RegPosIn, const uint8_t DstIn, void *VarIn);


/** @brief  Copy group of registers.
 *  @param  PosIn - register position in REGS.
 *  @param  SzIn  - number of registers to copy.
 *  @param  DstIn - destination of copy (reg.h):
 *  @arg      = REG_COPY_APP_TO_MB
 *  @arg      = REG_COPY_APP_TO_MB__NO_MON
 *  @arg      = REG_COPY_MB_TO_APP
 *  @arg      = REG_COPY_MB_TO_VAR
 *  @arg      = REG_COPY_VAR_TO_APP
 *  @arg      = REG_COPY_VAR_TO_MB
 *  @arg      = REG_COPY_VAR_TO_MB__NO_MON
 *  @arg      = REG_COPY_VAR_TO_ALL
 *  @arg      = REG_COPY_VAR_TO_ALL__NO_MON
 *  @param  VarIn - pointer to Variable or 0.
 *  @return The number of copied registers.
 */
uint16_t REG_CopyRegs(const uint16_t PosIn, const uint16_t SzIn, const uint8_t DstIn, void *VarIn);


/** @brief  Test Position of ModBus (Data) Table.
 *  @param  TableIn - table ID (reg-map.h)
 *  @param  PosIn   - position.
 *  @param  WSzIn   - size of words for value:
 *  @arg       =1 - for Bool-table
 *  @arg      >=1 - for Numeric-table (ex.: 2 words for FLOAT)
 *  @return Pointer to register or 0 (if table or position is not supported)
 */
void *REG_TestDataTablePos(const uint8_t TableIn, const uint16_t PosIn, const uint8_t WSzIn);


/** @brief  Init. group of registers in REGS.
 *  @param  GIDIn     - Unique ID of group/subgroup.
 *  @param  ZoneIn    - Zone ID.
 *  @param  TypeSzIn  - Data Type Size ID.
 *  @param  GroupIn   - Group ID.
 *  @param  TypeIn    - Data Type ID.
 *  @param  PosIn     - Start position in REGS (offset).
 *  @param  SzIn      - Number of registers.
 *  @param  SaddrIn   - Start register address.
 *  @param  MbTableIn - ModBus Table ID.
 *  @param  MbPosIn   - Start position in ModBus table (offset).
 *  @param  A00In     - Value of a_data[0] (<0 - not used; ex. -10 - use calculated register address).
 *  @param  A01In     - Value of a_data[1] (<0 - not used; ex. -10 - use calculated register address).
 *  @param  A02In     - Value of a_data[2] (<0 - not used; ex. -10 - use calculated register address).
 *  @param  DataTableIn - Data Table ID.
 *  @param  DataPosIn   - Start position in Data table (offset).
 *  @param  EeAreaIn    - EEPROM Area ID.
 *  @param  EePosIn     - Start position in EEPROM (offset).
 *  @return The number of inited registers.
 */
uint16_t REG_InitRegs(const uint16_t GIDIn, const uint8_t ZoneIn, const uint8_t TypeSzIn, const uint16_t GroupIn, const uint8_t TypeIn, const uint16_t PosIn, const uint16_t SzIn, const uint16_t SaddrIn, const uint8_t MbTableIn, const uint16_t MbPosIn, const int32_t A00In, const int32_t A01In, const int32_t A02In, const uint8_t DataTableIn, const uint16_t DataPosIn, const uint8_t EeAreaIn, const int32_t EePosIn);


/** @brief  Clear Data Tables.
 *  @param  None.
 *  @return None.
 */
void REG_Clear(void);

#endif //REG_BASE_H
