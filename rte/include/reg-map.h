/* @page reg-map.h
 *       Registers map
 *       2020-2022
 */

#ifndef REG_MAP_H
#define REG_MAP_H

#include <stdint.h>
#include "config.h"


/** @def    Calc. Register position (offset) from previous group of registers.
 *  @param  PrePosIn - start position (offset) of previous group.
 *  @param  PreSzIn  - quantity of registers in previous group.
 *  @return Start position (offset) of the register.
 */
#define REG_CALC_POS(PrePosIn, PreSzIn)                        (PrePosIn+PreSzIn)

/** @def    Calc. Register position in a group (iGroup) by ModBus address.
 *  @param  MbAddrIn - ModBus address.
 *  @param  SMbPosIn - start ModBus address of the register group.
 *  @param  NwIn     - quantity of words for the register.
 *  @return Register position in a group (iGroup) or -1. [int32_t]
 */
#define REG_CALC_POS_BY_MBADDR(MbAddrIn, SMbPosIn, NwIn)       ((NwIn > 0) ? (int32_t)((MbAddrIn-SMbPosIn)/NwIn) : (int32_t)-1)


/** @def    Calc. ModBus position (offset) from previous group of registers.
 *  @param  PrePosIn - ModBus position (offset) of previous group.
 *  @param  PreSzIn  - quantity of registers in previous group.
 *  @param  PreNwIn  - quantity of words for one register of previous group.
 *  @param  ResSzIn  - quantity of reserve registers.
 *  @return ModBus position (offset).
 */
#define REG_CALC_MBPOS(PrePosIn, PreSzIn, PreNwIn, ResSzIn)    (((PreSzIn*PreNwIn)+PrePosIn)+(ResSzIn*PreNwIn))

/** @def    Calc. ModBus address.
 *  @param  SaddrIn  - start address of register (0...N) in the group.
 *  @param  NwIn     - quantity of words for the register.
 *  @param  PosIn    - start ModBus position (offset) of the group.
 *  @return ModBus address.
 */
#define REG_CALC_MBADDR(SaddrIn, NwIn, MbPosIn)                ((SaddrIn*NwIn)+MbPosIn)


/** @note
 *       *__ZONE   - ID of memory     (plc_app.v_type)
 *       *__TYPESZ - ID of data type  (plc_app.v_size)
 *       *__GROUP  - ID of group      (plc_app.proto)
 *       *__A00    - ID of subgroup 0 (plc_app.a_data[0])
 *       *__A01    - ID of subgroup 1 (plc_app.a_data[1])
 *       *__A02    - ID of subgroup 2 (plc_app.a_data[2])
 */

/** @def Subgroup A00..02 is not used
 */
#define REG_AXX_NONE                   (int32_t)-1

/** @def Subgroup A00..02 is register address
 */
#define REG_AXX_ADDR                   (int32_t)-10

//=============================================================================

/** @def Data Table ID
 */
#define REG_DATA_BOOL_TABLE_ID         (uint8_t)1  //Boolean
#define REG_DATA_NUMB_TABLE_ID         (uint8_t)2  //Numeric

//=============================================================================

/** @def ModBus Table ID
 */
#define MBRTU_COIL_TABLE_ID            (uint8_t)1
#define MBRTU_DISC_TABLE_ID            (uint8_t)2
#define MBRTU_HOLD_TABLE_ID            (uint8_t)3
#define MBRTU_INPT_TABLE_ID            (uint8_t)4

//=============================================================================

/** @def EEPROM Area ID
 */
#define EEPROM_AREA_NONE                (uint8_t)0
#define EEPROM_AREA_FACTORY             (uint8_t)1
#define EEPROM_AREA_SYSTEM              (uint8_t)2
#define EEPROM_AREA_USER                (uint8_t)3

/** @def EEPROM Address
 */
#define EEPROM_ADDR_NONE                (int32_t)-1

//=============================================================================

/** @def Reserve space (the quantity of registers)
 */
#define REG_RESERVE                    (uint8_t)10

//=============================================================================
//=============================================================================
//=============================================================================


// DI =================================

#include "di.h"

#define REG_DI__GROUP                           (uint16_t)1

/** @def DI Normal: value
 *  @note
 *       IX1.0.1.1 ... IX1.3.1.1
 *       T_DI   > ModBus
 *       ModBus > App
 */
#define REG_DI_NORM_VAL__GID                     (uint16_t)1           //Unique ID
// located variable
#define REG_DI_NORM_VAL__ZONE                    PLC_LT_I              //ID of memory
#define REG_DI_NORM_VAL__TYPESZ                  PLC_LSZ_X             //ID of data type
#define REG_DI_NORM_VAL__GROUP                   REG_DI__GROUP         //ID of group
#define REG_DI_NORM_VAL__A00                     REG_AXX_ADDR
#define REG_DI_NORM_VAL__A01                     (int32_t)1            //ID of subgroup by mode
#define REG_DI_NORM_VAL__A02                     (int32_t)1            //ID of register
#define REG_DI_NORM_VAL__TYPE                    TYPE_BOOL             //Data type
#define REG_DI_NORM_VAL__TYPE_SZ                 TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_NORM_VAL__TYPE_WSZ                TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_NORM_VAL__POS                     (uint16_t)0
#define REG_DI_NORM_VAL__SZ                      (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_NORM_VAL__SADDR                   (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_NORM_VAL__DPOS                    (uint16_t)0
#define REG_DI_NORM_VAL__DPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DI_NORM_VAL__DPOS, REG_DI_NORM_VAL__SZ, REG_DI_NORM_VAL__TYPE_WSZ, 0)-1
#define REG_DI_NORM_VAL__DTABLE                  REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_NORM_VAL__MBPOS                   (uint16_t)0
#define REG_DI_NORM_VAL__MBPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DI_NORM_VAL__MBPOS, REG_DI_NORM_VAL__SZ, REG_DI_NORM_VAL__TYPE_WSZ, 0)-1
#define REG_DI_NORM_VAL__MBTABLE                 MBRTU_DISC_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_NORM_VAL__EAREA                   EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_DI_NORM_VAL__EPOS                    EEPROM_ADDR_NONE
//STRING
#define REG_DI_NORM_VAL__STR                     "DI%d Norm: Value"


/** @def DI Tachometer: value
 *  @note
 *       IW1.0.2.1 ... IW1.3.2.1
 *       T_DI   > ModBus
 *       ModBus > App
 */
#define REG_DI_TACH_VAL__GID                     (uint16_t)2           //Unique ID
// located variable
#define REG_DI_TACH_VAL__ZONE                    PLC_LT_I              //ID of memory
#define REG_DI_TACH_VAL__TYPESZ                  PLC_LSZ_W             //ID of data type
#define REG_DI_TACH_VAL__GROUP                   REG_DI__GROUP         //ID of group
#define REG_DI_TACH_VAL__A00                     REG_AXX_ADDR
#define REG_DI_TACH_VAL__A01                     (int32_t)2            //ID of subgroup by mode
#define REG_DI_TACH_VAL__A02                     (int32_t)1            //ID of register
#define REG_DI_TACH_VAL__TYPE                    TYPE_WORD             //Data type
#define REG_DI_TACH_VAL__TYPE_SZ                 TYPE_WORD_SZ          //Size of data type in bytes
#define REG_DI_TACH_VAL__TYPE_WSZ                TYPE_WORD_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_TACH_VAL__POS                     (uint16_t)REG_CALC_POS(REG_DI_NORM_VAL__POS, REG_DI_NORM_VAL__SZ)
#define REG_DI_TACH_VAL__SZ                      (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_TACH_VAL__SADDR                   (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_TACH_VAL__DPOS                    (uint16_t)0
#define REG_DI_TACH_VAL__DPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_VAL__DPOS, REG_DI_TACH_VAL__SZ, REG_DI_TACH_VAL__TYPE_WSZ, 0)-1
#define REG_DI_TACH_VAL__DTABLE                  REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_TACH_VAL__MBPOS                   (uint16_t)0
#define REG_DI_TACH_VAL__MBPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_VAL__MBPOS, REG_DI_TACH_VAL__SZ, REG_DI_TACH_VAL__TYPE_WSZ, 0)-1
#define REG_DI_TACH_VAL__MBTABLE                 MBRTU_INPT_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_TACH_VAL__EAREA                   EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_DI_TACH_VAL__EPOS                    EEPROM_ADDR_NONE
//STRING
#define REG_DI_TACH_VAL__STR                     "DI%d Tach: Value"


/** @def DI Tachometer: setpoint
 *  @note
 *       MW1.0.2.2 ... MW1.3.2.2
 *       App    > ModBus (> App)
 *       ModBus > T_DI
 */
#define REG_DI_TACH_SETPOINT__GID                (uint16_t)3           //Unique ID
// located variable
#define REG_DI_TACH_SETPOINT__ZONE               PLC_LT_M              //ID of memory
#define REG_DI_TACH_SETPOINT__TYPESZ             PLC_LSZ_W             //ID of data type
#define REG_DI_TACH_SETPOINT__GROUP              REG_DI__GROUP         //ID of group
#define REG_DI_TACH_SETPOINT__A00                REG_AXX_ADDR
#define REG_DI_TACH_SETPOINT__A01                (int32_t)2            //ID of subgroup by mode
#define REG_DI_TACH_SETPOINT__A02                (int32_t)2            //ID of register
#define REG_DI_TACH_SETPOINT__TYPE               TYPE_WORD             //Data type
#define REG_DI_TACH_SETPOINT__TYPE_SZ            TYPE_WORD_SZ          //Size of data type in bytes
#define REG_DI_TACH_SETPOINT__TYPE_WSZ           TYPE_WORD_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_TACH_SETPOINT__POS                (uint16_t)REG_CALC_POS(REG_DI_TACH_VAL__POS, REG_DI_TACH_VAL__SZ)
#define REG_DI_TACH_SETPOINT__SZ                 (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_TACH_SETPOINT__SADDR              (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_TACH_SETPOINT__DPOS               (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_VAL__DPOS, REG_DI_TACH_VAL__SZ, REG_DI_TACH_VAL__TYPE_WSZ, 0)
#define REG_DI_TACH_SETPOINT__DPOS_END           (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT__DPOS, REG_DI_TACH_SETPOINT__SZ, REG_DI_TACH_SETPOINT__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT__DTABLE             REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_TACH_SETPOINT__MBPOS              (uint16_t)0
#define REG_DI_TACH_SETPOINT__MBPOS_END          (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT__MBPOS, REG_DI_TACH_SETPOINT__SZ, REG_DI_TACH_SETPOINT__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT__MBTABLE            MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_TACH_SETPOINT__EAREA              EEPROM_AREA_SYSTEM     //EEPROM Area ID
#define REG_DI_TACH_SETPOINT__EPOS               (int32_t)0
//STRING
#define REG_DI_TACH_SETPOINT__STR                "DI%d Tach: Setpoint"


/** @def DI Tachometer: setpoint reached
 *  @note
 *       MX1.0.2.3 ... MX1.3.2.3
 *       T_DI   > ModBus
 *       ModBus > App
 */
#define REG_DI_TACH_SETPOINT_RES__GID            (uint16_t)4           //Unique ID
// located variable
#define REG_DI_TACH_SETPOINT_RES__ZONE           PLC_LT_M              //ID of memory
#define REG_DI_TACH_SETPOINT_RES__TYPESZ         PLC_LSZ_X             //ID of data type
#define REG_DI_TACH_SETPOINT_RES__GROUP          REG_DI__GROUP         //ID of group
#define REG_DI_TACH_SETPOINT_RES__A00            REG_AXX_ADDR
#define REG_DI_TACH_SETPOINT_RES__A01            (int32_t)2            //ID of subgroup by mode
#define REG_DI_TACH_SETPOINT_RES__A02            (int32_t)3            //ID of register
#define REG_DI_TACH_SETPOINT_RES__TYPE           TYPE_BOOL             //Data type
#define REG_DI_TACH_SETPOINT_RES__TYPE_SZ        TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_TACH_SETPOINT_RES__TYPE_WSZ       TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_TACH_SETPOINT_RES__POS            (uint16_t)REG_CALC_POS(REG_DI_TACH_SETPOINT__POS, REG_DI_TACH_SETPOINT__SZ)
#define REG_DI_TACH_SETPOINT_RES__SZ             (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_TACH_SETPOINT_RES__SADDR          (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_TACH_SETPOINT_RES__DPOS           (uint16_t)REG_CALC_MBPOS(REG_DI_NORM_VAL__DPOS, REG_DI_NORM_VAL__SZ, REG_DI_NORM_VAL__TYPE_WSZ, 0)
#define REG_DI_TACH_SETPOINT_RES__DPOS_END       (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_RES__DPOS, REG_DI_TACH_SETPOINT_RES__SZ, REG_DI_TACH_SETPOINT_RES__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT_RES__DTABLE         REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_TACH_SETPOINT_RES__MBPOS          (uint16_t)REG_CALC_MBPOS(REG_DI_NORM_VAL__MBPOS, REG_DI_NORM_VAL__SZ, REG_DI_NORM_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_DI_TACH_SETPOINT_RES__MBPOS_END      (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_RES__MBPOS, REG_DI_TACH_SETPOINT_RES__SZ, REG_DI_TACH_SETPOINT_RES__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT_RES__MBTABLE        MBRTU_DISC_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_TACH_SETPOINT_RES__EAREA          EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_DI_TACH_SETPOINT_RES__EPOS           EEPROM_ADDR_NONE
//STRING
#define REG_DI_TACH_SETPOINT_RES__STR            "DI%d Tach: Setpoint is reached, flag"


/** @def DI Tachometer: setpoint allow
 *  @note
 *       MX1.0.2.4 ... MX1.3.2.4
 *       App    > ModBus (> App)
 *       ModBus > T_DI
 */
#define REG_DI_TACH_SETPOINT_ALLOW__GID          (uint16_t)5           //Unique ID
// located variable
#define REG_DI_TACH_SETPOINT_ALLOW__ZONE         PLC_LT_M              //ID of memory
#define REG_DI_TACH_SETPOINT_ALLOW__TYPESZ       PLC_LSZ_X             //ID of data type
#define REG_DI_TACH_SETPOINT_ALLOW__GROUP        REG_DI__GROUP         //ID of group
#define REG_DI_TACH_SETPOINT_ALLOW__A00          REG_AXX_ADDR
#define REG_DI_TACH_SETPOINT_ALLOW__A01          (int32_t)2            //ID of subgroup by mode
#define REG_DI_TACH_SETPOINT_ALLOW__A02          (int32_t)4            //ID of register
#define REG_DI_TACH_SETPOINT_ALLOW__TYPE         TYPE_BOOL             //Data type
#define REG_DI_TACH_SETPOINT_ALLOW__TYPE_SZ      TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_TACH_SETPOINT_ALLOW__TYPE_WSZ     TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_TACH_SETPOINT_ALLOW__POS          (uint16_t)REG_CALC_POS(REG_DI_TACH_SETPOINT_RES__POS, REG_DI_TACH_SETPOINT_RES__SZ)
#define REG_DI_TACH_SETPOINT_ALLOW__SZ           (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_TACH_SETPOINT_ALLOW__SADDR        (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_TACH_SETPOINT_ALLOW__DPOS         (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_RES__DPOS, REG_DI_TACH_SETPOINT_RES__SZ, REG_DI_TACH_SETPOINT_RES__TYPE_WSZ, 0)
#define REG_DI_TACH_SETPOINT_ALLOW__DPOS_END     (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_ALLOW__DPOS, REG_DI_TACH_SETPOINT_ALLOW__SZ, REG_DI_TACH_SETPOINT_ALLOW__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT_ALLOW__DTABLE       REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_TACH_SETPOINT_ALLOW__MBPOS        (uint16_t)0
#define REG_DI_TACH_SETPOINT_ALLOW__MBPOS_END    (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_ALLOW__MBPOS, REG_DI_TACH_SETPOINT_ALLOW__SZ, REG_DI_TACH_SETPOINT_ALLOW__TYPE_WSZ, 0)-1
#define REG_DI_TACH_SETPOINT_ALLOW__MBTABLE      MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_TACH_SETPOINT_ALLOW__EAREA        EEPROM_AREA_SYSTEM     //EEPROM Area ID
#define REG_DI_TACH_SETPOINT_ALLOW__EPOS         (int32_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT__EPOS, REG_DI_TACH_SETPOINT__SZ, REG_DI_TACH_SETPOINT__TYPE_SZ, 0)
//STRING
#define REG_DI_TACH_SETPOINT_ALLOW__STR          "DI%d Tach: Allow to work by setpoint"


/** @def DI Counter: value
 *  @note
 *       ID1.0.3.1 ... ID1.3.3.1
 *       T_DI   > ModBus
 *       ModBus > App
 */
#define REG_DI_CNTR_VAL__GID                     (uint16_t)6           //Unique ID
// located variable
#define REG_DI_CNTR_VAL__ZONE                    PLC_LT_I              //ID of memory
#define REG_DI_CNTR_VAL__TYPESZ                  PLC_LSZ_D             //ID of data type
#define REG_DI_CNTR_VAL__GROUP                   REG_DI__GROUP         //ID of group
#define REG_DI_CNTR_VAL__A00                     REG_AXX_ADDR
#define REG_DI_CNTR_VAL__A01                     (int32_t)3            //ID of subgroup by mode
#define REG_DI_CNTR_VAL__A02                     (int32_t)1            //ID of register
#define REG_DI_CNTR_VAL__TYPE                    TYPE_DWORD            //Data type
#define REG_DI_CNTR_VAL__TYPE_SZ                 TYPE_DWORD_SZ         //Size of data type in bytes
#define REG_DI_CNTR_VAL__TYPE_WSZ                TYPE_DWORD_WSZ        //Size of data type in words
// position (offset) in REGS
#define REG_DI_CNTR_VAL__POS                     (uint16_t)REG_CALC_POS(REG_DI_TACH_SETPOINT_ALLOW__POS, REG_DI_TACH_SETPOINT_ALLOW__SZ)
#define REG_DI_CNTR_VAL__SZ                      (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_CNTR_VAL__SADDR                   (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_CNTR_VAL__DPOS                    (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT__DPOS, REG_DI_TACH_SETPOINT__SZ, REG_DI_TACH_SETPOINT__TYPE_WSZ, 0)
#define REG_DI_CNTR_VAL__DPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_VAL__DPOS, REG_DI_CNTR_VAL__SZ, REG_DI_CNTR_VAL__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_VAL__DTABLE                  REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_CNTR_VAL__MBPOS                   (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_VAL__MBPOS, REG_DI_TACH_VAL__SZ, REG_DI_TACH_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_DI_CNTR_VAL__MBPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_VAL__MBPOS, REG_DI_CNTR_VAL__SZ, REG_DI_CNTR_VAL__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_VAL__MBTABLE                 MBRTU_INPT_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_CNTR_VAL__EAREA                   EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_DI_CNTR_VAL__EPOS                    EEPROM_ADDR_NONE
//STRING
#define REG_DI_CNTR_VAL__STR                     "DI%d Cntr: Value"


/** @def DI Counter: setpoint
 *  @note
 *       MD1.0.3.2 ... MD1.3.3.2
 *       App    > ModBus (> App)
 *       ModBus > T_DI
 */
#define REG_DI_CNTR_SETPOINT__GID                (uint16_t)7           //Unique ID
// located variable
#define REG_DI_CNTR_SETPOINT__ZONE               PLC_LT_M              //ID of memory
#define REG_DI_CNTR_SETPOINT__TYPESZ             PLC_LSZ_D             //ID of data type
#define REG_DI_CNTR_SETPOINT__GROUP              REG_DI__GROUP         //ID of group
#define REG_DI_CNTR_SETPOINT__A00                REG_AXX_ADDR
#define REG_DI_CNTR_SETPOINT__A01                (int32_t)3            //ID of subgroup by mode
#define REG_DI_CNTR_SETPOINT__A02                (int32_t)2            //ID of register
#define REG_DI_CNTR_SETPOINT__TYPE               TYPE_DWORD            //Data type
#define REG_DI_CNTR_SETPOINT__TYPE_SZ            TYPE_DWORD_SZ         //Size of data type in bytes
#define REG_DI_CNTR_SETPOINT__TYPE_WSZ           TYPE_DWORD_WSZ        //Size of data type in words
// position (offset) in REGS
#define REG_DI_CNTR_SETPOINT__POS                (uint16_t)REG_CALC_POS(REG_DI_CNTR_VAL__POS, REG_DI_CNTR_VAL__SZ)
#define REG_DI_CNTR_SETPOINT__SZ                 (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_CNTR_SETPOINT__SADDR              (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_CNTR_SETPOINT__DPOS               (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_VAL__DPOS, REG_DI_CNTR_VAL__SZ, REG_DI_CNTR_VAL__TYPE_WSZ, 0)
#define REG_DI_CNTR_SETPOINT__DPOS_END           (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT__DPOS, REG_DI_CNTR_SETPOINT__SZ, REG_DI_CNTR_SETPOINT__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT__DTABLE             REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_CNTR_SETPOINT__MBPOS              (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT__MBPOS, REG_DI_TACH_SETPOINT__SZ, REG_DI_TACH_SETPOINT__TYPE_WSZ, REG_RESERVE)
#define REG_DI_CNTR_SETPOINT__MBPOS_END          (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT__MBPOS, REG_DI_CNTR_SETPOINT__SZ, REG_DI_CNTR_SETPOINT__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT__MBTABLE            MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_CNTR_SETPOINT__EAREA              EEPROM_AREA_SYSTEM     //EEPROM Area ID
#define REG_DI_CNTR_SETPOINT__EPOS               (int32_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_ALLOW__EPOS, REG_DI_TACH_SETPOINT_ALLOW__SZ, REG_DI_TACH_SETPOINT_ALLOW__TYPE_SZ, 0)
//STRING
#define REG_DI_CNTR_SETPOINT__STR                "DI%d Cntr: Setpoint"


/** @def DI Counter: setpoint reached
 *  @note
 *       MX1.0.3.3 ... MX1.3.3.3
 *       T_DI   > ModBus
 *       ModBus > App
 */
#define REG_DI_CNTR_SETPOINT_RES__GID            (uint16_t)8           //Unique ID
// located variable
#define REG_DI_CNTR_SETPOINT_RES__ZONE           PLC_LT_M              //ID of memory
#define REG_DI_CNTR_SETPOINT_RES__TYPESZ         PLC_LSZ_X             //ID of data type
#define REG_DI_CNTR_SETPOINT_RES__GROUP          REG_DI__GROUP         //ID of group
#define REG_DI_CNTR_SETPOINT_RES__A00            REG_AXX_ADDR
#define REG_DI_CNTR_SETPOINT_RES__A01            (int32_t)3            //ID of subgroup by mode
#define REG_DI_CNTR_SETPOINT_RES__A02            (int32_t)3            //ID of register
#define REG_DI_CNTR_SETPOINT_RES__TYPE           TYPE_BOOL             //Data type
#define REG_DI_CNTR_SETPOINT_RES__TYPE_SZ        TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_CNTR_SETPOINT_RES__TYPE_WSZ       TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_CNTR_SETPOINT_RES__POS            (uint16_t)REG_CALC_POS(REG_DI_CNTR_SETPOINT__POS, REG_DI_CNTR_SETPOINT__SZ)
#define REG_DI_CNTR_SETPOINT_RES__SZ             (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_CNTR_SETPOINT_RES__SADDR          (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_CNTR_SETPOINT_RES__DPOS           (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_ALLOW__DPOS, REG_DI_TACH_SETPOINT_ALLOW__SZ, REG_DI_TACH_SETPOINT_ALLOW__TYPE_WSZ, 0)
#define REG_DI_CNTR_SETPOINT_RES__DPOS_END       (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_RES__DPOS, REG_DI_CNTR_SETPOINT_RES__SZ, REG_DI_CNTR_SETPOINT_RES__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT_RES__DTABLE         REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_CNTR_SETPOINT_RES__MBPOS          (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_RES__MBPOS, REG_DI_TACH_SETPOINT_RES__SZ, REG_DI_TACH_SETPOINT_RES__TYPE_WSZ, REG_RESERVE)
#define REG_DI_CNTR_SETPOINT_RES__MBPOS_END      (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_RES__MBPOS, REG_DI_CNTR_SETPOINT_RES__SZ, REG_DI_CNTR_SETPOINT_RES__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT_RES__MBTABLE        MBRTU_DISC_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_CNTR_SETPOINT_RES__EAREA          EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_DI_CNTR_SETPOINT_RES__EPOS           EEPROM_ADDR_NONE
//STRING
#define REG_DI_CNTR_SETPOINT_RES__STR            "DI%d Cntr: Setpoint is reached, flag"


/** @def DI Counter: setpoint allow
 *  @note
 *       MX1.0.3.4 ... MX1.3.3.4
 *       App    > ModBus (> App)
 *       ModBus > T_DI
 */
#define REG_DI_CNTR_SETPOINT_ALLOW__GID          (uint16_t)9           //Unique ID
// located variable
#define REG_DI_CNTR_SETPOINT_ALLOW__ZONE         PLC_LT_M              //ID of memory
#define REG_DI_CNTR_SETPOINT_ALLOW__TYPESZ       PLC_LSZ_X             //ID of data type
#define REG_DI_CNTR_SETPOINT_ALLOW__GROUP        REG_DI__GROUP         //ID of group
#define REG_DI_CNTR_SETPOINT_ALLOW__A00          REG_AXX_ADDR
#define REG_DI_CNTR_SETPOINT_ALLOW__A01          (int32_t)3            //ID of subgroup by mode
#define REG_DI_CNTR_SETPOINT_ALLOW__A02          (int32_t)4            //ID of register
#define REG_DI_CNTR_SETPOINT_ALLOW__TYPE         TYPE_BOOL             //Data type
#define REG_DI_CNTR_SETPOINT_ALLOW__TYPE_SZ      TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_CNTR_SETPOINT_ALLOW__TYPE_WSZ     TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_CNTR_SETPOINT_ALLOW__POS          (uint16_t)REG_CALC_POS(REG_DI_CNTR_SETPOINT_RES__POS, REG_DI_CNTR_SETPOINT_RES__SZ)
#define REG_DI_CNTR_SETPOINT_ALLOW__SZ           (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_CNTR_SETPOINT_ALLOW__SADDR        (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_CNTR_SETPOINT_ALLOW__DPOS         (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_RES__DPOS, REG_DI_CNTR_SETPOINT_RES__SZ, REG_DI_CNTR_SETPOINT_RES__TYPE_WSZ, 0)
#define REG_DI_CNTR_SETPOINT_ALLOW__DPOS_END     (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_ALLOW__DPOS, REG_DI_CNTR_SETPOINT_ALLOW__SZ, REG_DI_CNTR_SETPOINT_ALLOW__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT_ALLOW__DTABLE       REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_CNTR_SETPOINT_ALLOW__MBPOS        (uint16_t)REG_CALC_MBPOS(REG_DI_TACH_SETPOINT_ALLOW__MBPOS, REG_DI_TACH_SETPOINT_ALLOW__SZ, REG_DI_TACH_SETPOINT_ALLOW__TYPE_WSZ, REG_RESERVE)
#define REG_DI_CNTR_SETPOINT_ALLOW__MBPOS_END    (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_ALLOW__MBPOS, REG_DI_CNTR_SETPOINT_ALLOW__SZ, REG_DI_CNTR_SETPOINT_ALLOW__TYPE_WSZ, 0)-1
#define REG_DI_CNTR_SETPOINT_ALLOW__MBTABLE      MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_CNTR_SETPOINT_ALLOW__EAREA        EEPROM_AREA_SYSTEM     //EEPROM Area ID
#define REG_DI_CNTR_SETPOINT_ALLOW__EPOS         (int32_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT__EPOS, REG_DI_CNTR_SETPOINT__SZ, REG_DI_CNTR_SETPOINT__TYPE_SZ, 0)
//STRING
#define REG_DI_CNTR_SETPOINT_ALLOW__STR          "DI%d Cntr: AAllow to work by setpoint"


/** @def DI: mode (set)
 *  @note
 *       MB1.0.4 ... MB1.3.4
 *       App    > ModBus (> App)
 *       ModBus > T_DI
 */
#define REG_DI_MODE__GID                        (uint16_t)10           //Unique ID
// located variable
#define REG_DI_MODE__ZONE                        PLC_LT_M              //ID of memory
#define REG_DI_MODE__TYPESZ                      PLC_LSZ_B             //ID of data type
#define REG_DI_MODE__GROUP                       REG_DI__GROUP         //ID of group
#define REG_DI_MODE__A00                         REG_AXX_ADDR
#define REG_DI_MODE__A01                         (int32_t)4            //ID of register
#define REG_DI_MODE__A02                         REG_AXX_NONE
#define REG_DI_MODE__TYPE                        TYPE_BYTE             //Data type
#define REG_DI_MODE__TYPE_SZ                     TYPE_BYTE_SZ          //Size of data type in bytes
#define REG_DI_MODE__TYPE_WSZ                    TYPE_BYTE_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_MODE__POS                         (uint16_t)REG_CALC_POS(REG_DI_CNTR_SETPOINT_ALLOW__POS, REG_DI_CNTR_SETPOINT_ALLOW__SZ)
#define REG_DI_MODE__SZ                          (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_MODE__SADDR                       (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_MODE__DPOS                        (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT__DPOS, REG_DI_CNTR_SETPOINT__SZ, REG_DI_CNTR_SETPOINT__TYPE_WSZ, 0)
#define REG_DI_MODE__DPOS_END                    (uint16_t)REG_CALC_MBPOS(REG_DI_MODE__DPOS, REG_DI_MODE__SZ, REG_DI_MODE__TYPE_WSZ, 0)-1
#define REG_DI_MODE__DTABLE                      REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_MODE__MBPOS                       (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT__MBPOS, REG_DI_CNTR_SETPOINT__SZ, REG_DI_CNTR_SETPOINT__TYPE_WSZ, REG_RESERVE)
#define REG_DI_MODE__MBPOS_END                   (uint16_t)REG_CALC_MBPOS(REG_DI_MODE__MBPOS, REG_DI_MODE__SZ, REG_DI_MODE__TYPE_WSZ, 0)-1
#define REG_DI_MODE__MBTABLE                     MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_MODE__EAREA                       EEPROM_AREA_SYSTEM     //EEPROM Area ID
#define REG_DI_MODE__EPOS                        (int32_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_ALLOW__EPOS, REG_DI_CNTR_SETPOINT_ALLOW__SZ, REG_DI_CNTR_SETPOINT_ALLOW__TYPE_SZ, 0)
//STRING
#define REG_DI_MODE__STR                        "DI%d: Mode"


/** @def DI: reset counter and tachometer values (command)
 *  @note
 *       MX1.0.6 ... MX1.3.6
 *       App    > ModBus (> App)
 *       ModBus > T_DI
 */
#define REG_DI_RESET__GID                        (uint16_t)12          //Unique ID
// located variable
#define REG_DI_RESET__ZONE                       PLC_LT_M              //ID of memory
#define REG_DI_RESET__TYPESZ                     PLC_LSZ_X             //ID of data type
#define REG_DI_RESET__GROUP                      REG_DI__GROUP         //ID of group
#define REG_DI_RESET__A00                        REG_AXX_ADDR
#define REG_DI_RESET__A01                        (int32_t)6            //ID of register
#define REG_DI_RESET__A02                        REG_AXX_NONE
#define REG_DI_RESET__TYPE                       TYPE_BOOL             //Data type
#define REG_DI_RESET__TYPE_SZ                    TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DI_RESET__TYPE_WSZ                   TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DI_RESET__POS                        (uint16_t)REG_CALC_POS(REG_DI_MODE__POS, REG_DI_MODE__SZ)
#define REG_DI_RESET__SZ                         (uint16_t)PLC_DI_SZ   //Number of registers
#define REG_DI_RESET__SADDR                      (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DI_RESET__DPOS                       (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_ALLOW__DPOS, REG_DI_CNTR_SETPOINT_ALLOW__SZ, REG_DI_CNTR_SETPOINT_ALLOW__TYPE_WSZ, 0)
#define REG_DI_RESET__DPOS_END                   (uint16_t)REG_CALC_MBPOS(REG_DI_RESET__DPOS, REG_DI_RESET__SZ, REG_DI_RESET__TYPE_WSZ, 0)-1
#define REG_DI_RESET__DTABLE                     REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DI_RESET__MBPOS                      (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_SETPOINT_ALLOW__MBPOS, REG_DI_CNTR_SETPOINT_ALLOW__SZ, REG_DI_CNTR_SETPOINT_ALLOW__TYPE_WSZ, REG_RESERVE)
#define REG_DI_RESET__MBPOS_END                  (uint16_t)REG_CALC_MBPOS(REG_DI_RESET__MBPOS, REG_DI_RESET__SZ, REG_DI_RESET__TYPE_WSZ, 0)-1
#define REG_DI_RESET__MBTABLE                    MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DI_RESET__EAREA                      EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_DI_RESET__EPOS                       EEPROM_ADDR_NONE
//STRING
#define REG_DI_RESET__STR                        "DI%d: Reset counter"


// DO =================================

#include "do.h"

#define REG_DO__GROUP                           (uint16_t)5

/** @def DO Normal: value
 *  @note
 *       QX5.0.1.1 ... QX5.3.1.1
 *       App    > ModBus (> App)
 *       ModBus > T_DO
 */
#define REG_DO_NORM_VAL__GID                     (uint16_t)14          //Unique ID
// located variable
#define REG_DO_NORM_VAL__ZONE                    PLC_LT_Q              //ID of memory
#define REG_DO_NORM_VAL__TYPESZ                  PLC_LSZ_X             //ID of data type
#define REG_DO_NORM_VAL__GROUP                   REG_DO__GROUP         //ID of group
#define REG_DO_NORM_VAL__A00                     REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_NORM_VAL__A01                     (int32_t)1            //arg1: ID of subgroup by mode
#define REG_DO_NORM_VAL__A02                     (int32_t)1            //arg2: ID of register
#define REG_DO_NORM_VAL__TYPE                    TYPE_BOOL             //Data type
#define REG_DO_NORM_VAL__TYPE_SZ                 TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DO_NORM_VAL__TYPE_WSZ                TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_NORM_VAL__POS                     (uint16_t)REG_CALC_POS(REG_DI_RESET__POS, REG_DI_RESET__SZ)
#define REG_DO_NORM_VAL__SZ                      (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_NORM_VAL__SADDR                   (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_NORM_VAL__DPOS                    (uint16_t)REG_CALC_MBPOS(REG_DI_RESET__DPOS, REG_DI_RESET__SZ, REG_DI_RESET__TYPE_WSZ, 0)
#define REG_DO_NORM_VAL__DPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DO_NORM_VAL__DPOS, REG_DO_NORM_VAL__SZ, REG_DO_NORM_VAL__TYPE_WSZ, 0)-1
#define REG_DO_NORM_VAL__DTABLE                  REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_NORM_VAL__MBPOS                   (uint16_t)REG_CALC_MBPOS(REG_DI_RESET__MBPOS, REG_DI_RESET__SZ, REG_DI_RESET__TYPE_WSZ, REG_RESERVE)
#define REG_DO_NORM_VAL__MBPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DO_NORM_VAL__MBPOS, REG_DO_NORM_VAL__SZ, REG_DO_NORM_VAL__TYPE_WSZ, 0)-1
#define REG_DO_NORM_VAL__MBTABLE                 MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_NORM_VAL__EAREA                   EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_DO_NORM_VAL__EPOS                    EEPROM_ADDR_NONE
//STRING
#define REG_DO_NORM_VAL__STR                     "DO%d Norm: Value"


/** @def DO Fast: value
 *  @note
 *       QX5.0.2.1 ... QX5.3.2.1
 *       App    > ModBus (> App)
 *       ModBus > T_DO
 */
#define REG_DO_FAST_VAL__GID                     (uint16_t)15          //Unique ID
// located variable
#define REG_DO_FAST_VAL__ZONE                    PLC_LT_Q              //ID of memory
#define REG_DO_FAST_VAL__TYPESZ                  PLC_LSZ_X             //ID of data type
#define REG_DO_FAST_VAL__GROUP                   REG_DO__GROUP         //ID of group
#define REG_DO_FAST_VAL__A00                     REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_FAST_VAL__A01                     (int32_t)2            //arg1: ID of subgroup by mode
#define REG_DO_FAST_VAL__A02                     (int32_t)1            //arg2: ID of register
#define REG_DO_FAST_VAL__TYPE                    TYPE_BOOL             //Data type
#define REG_DO_FAST_VAL__TYPE_SZ                 TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DO_FAST_VAL__TYPE_WSZ                TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_FAST_VAL__POS                     (uint16_t)REG_CALC_POS(REG_DO_NORM_VAL__POS, REG_DO_NORM_VAL__SZ)
#define REG_DO_FAST_VAL__SZ                      (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_FAST_VAL__SADDR                   (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_FAST_VAL__DPOS                    (uint16_t)REG_CALC_MBPOS(REG_DO_NORM_VAL__DPOS, REG_DO_NORM_VAL__SZ, REG_DO_NORM_VAL__TYPE_WSZ, 0)
#define REG_DO_FAST_VAL__DPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DO_FAST_VAL__DPOS, REG_DO_FAST_VAL__SZ, REG_DO_FAST_VAL__TYPE_WSZ, 0)-1
#define REG_DO_FAST_VAL__DTABLE                  REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_FAST_VAL__MBPOS                   (uint16_t)REG_CALC_MBPOS(REG_DO_NORM_VAL__MBPOS, REG_DO_NORM_VAL__SZ, REG_DO_NORM_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_DO_FAST_VAL__MBPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DO_FAST_VAL__MBPOS, REG_DO_FAST_VAL__SZ, REG_DO_FAST_VAL__TYPE_WSZ, 0)-1
#define REG_DO_FAST_VAL__MBTABLE                 MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_FAST_VAL__EAREA                   EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_DO_FAST_VAL__EPOS                    EEPROM_ADDR_NONE
//STRING
#define REG_DO_FAST_VAL__STR                     "DO%d Fast: Value"


/** @def DO PWM: value (fill factor)
 *  @note
 *       QD5.0.3.1 ... QD5.3.3.1
 *       App    > ModBus (> App)
 *       ModBus > T_DO
 */
#define REG_DO_PWM_VAL__GID                      (uint16_t)18          //Unique ID
// located variable
#define REG_DO_PWM_VAL__ZONE                     PLC_LT_Q              //ID of memory
#define REG_DO_PWM_VAL__TYPESZ                   PLC_LSZ_D             //ID of data type
#define REG_DO_PWM_VAL__GROUP                    REG_DO__GROUP         //ID of group
#define REG_DO_PWM_VAL__A00                      REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_PWM_VAL__A01                      (int32_t)3            //arg1: ID of subgroup by mode
#define REG_DO_PWM_VAL__A02                      (int32_t)1            //arg2: ID of register
#define REG_DO_PWM_VAL__TYPE                     TYPE_REAL             //Data type
#define REG_DO_PWM_VAL__TYPE_SZ                  TYPE_REAL_SZ          //Size of data type in bytes
#define REG_DO_PWM_VAL__TYPE_WSZ                 TYPE_REAL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_PWM_VAL__POS                      (uint16_t)REG_CALC_POS(REG_DO_FAST_VAL__POS, REG_DO_FAST_VAL__SZ)
#define REG_DO_PWM_VAL__SZ                       (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_PWM_VAL__SADDR                    (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_PWM_VAL__DPOS                     (uint16_t)REG_CALC_MBPOS(REG_DI_MODE__DPOS, REG_DI_MODE__SZ, REG_DI_MODE__TYPE_WSZ, 0)
#define REG_DO_PWM_VAL__DPOS_END                 (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_VAL__DPOS, REG_DO_PWM_VAL__SZ, REG_DO_PWM_VAL__TYPE_WSZ, 0)-1
#define REG_DO_PWM_VAL__DTABLE                   REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_PWM_VAL__MBPOS                    (uint16_t)REG_CALC_MBPOS(REG_DI_MODE__MBPOS, REG_DI_MODE__SZ, REG_DI_MODE__TYPE_WSZ, REG_RESERVE)
#define REG_DO_PWM_VAL__MBPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_VAL__MBPOS, REG_DO_PWM_VAL__SZ, REG_DO_PWM_VAL__TYPE_WSZ, 0)-1
#define REG_DO_PWM_VAL__MBTABLE                  MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_PWM_VAL__EAREA                    EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_DO_PWM_VAL__EPOS                     EEPROM_ADDR_NONE
//STRING
#define REG_DO_PWM_VAL__STR                     "DO%d PWM: Fill Dactor, %"


/** @def DO PWM: command 'Allow'
 *  @note
 *       MX5.0.3.2 ... MX5.3.3.2
 *       App    > ModBus (> App)
 *       ModBus > T_DO
 */
#define REG_DO_PWM_ALLOW__GID                    (uint16_t)19          //Unique ID
// located variable
#define REG_DO_PWM_ALLOW__ZONE                   PLC_LT_M              //ID of memory
#define REG_DO_PWM_ALLOW__TYPESZ                 PLC_LSZ_X             //ID of data type
#define REG_DO_PWM_ALLOW__GROUP                  REG_DO__GROUP         //ID of group
#define REG_DO_PWM_ALLOW__A00                    REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_PWM_ALLOW__A01                    (int32_t)3            //arg1: ID of subgroup by mode
#define REG_DO_PWM_ALLOW__A02                    (int32_t)2            //arg2: ID of register
#define REG_DO_PWM_ALLOW__TYPE                   TYPE_BOOL             //Data type
#define REG_DO_PWM_ALLOW__TYPE_SZ                TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DO_PWM_ALLOW__TYPE_WSZ               TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_PWM_ALLOW__POS                    (uint16_t)REG_CALC_POS(REG_DO_PWM_VAL__POS, REG_DO_PWM_VAL__SZ)
#define REG_DO_PWM_ALLOW__SZ                     (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_PWM_ALLOW__SADDR                  (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_PWM_ALLOW__DPOS                   (uint16_t)REG_CALC_MBPOS(REG_DO_FAST_VAL__DPOS, REG_DO_FAST_VAL__SZ, REG_DO_FAST_VAL__TYPE_WSZ, 0)
#define REG_DO_PWM_ALLOW__DPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_ALLOW__DPOS, REG_DO_PWM_ALLOW__SZ, REG_DO_PWM_ALLOW__TYPE_WSZ, 0)-1
#define REG_DO_PWM_ALLOW__DTABLE                 REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_PWM_ALLOW__MBPOS                  (uint16_t)REG_CALC_MBPOS(REG_DO_FAST_VAL__MBPOS, REG_DO_FAST_VAL__SZ, REG_DO_FAST_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_DO_PWM_ALLOW__MBPOS_END              (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_ALLOW__MBPOS, REG_DO_PWM_ALLOW__SZ, REG_DO_PWM_ALLOW__TYPE_WSZ, 0)-1
#define REG_DO_PWM_ALLOW__MBTABLE                MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_PWM_ALLOW__EAREA                  EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_DO_PWM_ALLOW__EPOS                   EEPROM_ADDR_NONE
//STRING
#define REG_DO_PWM_ALLOW__STR                    "DO%d PWM: Allow to work"


/** @def DO PWM: period (ms)
 *  @note
 *       MD5.0.3.4 ... MXD.3.3.4
 *       App    > ModBus (> App)
 *       ModBus > T_DO
 */
#define REG_DO_PWM_PERIOD__GID                   (uint16_t)21          //Unique ID
// located variable
#define REG_DO_PWM_PERIOD__ZONE                  PLC_LT_M              //ID of memory
#define REG_DO_PWM_PERIOD__TYPESZ                PLC_LSZ_D             //ID of data type
#define REG_DO_PWM_PERIOD__GROUP                 REG_DO__GROUP         //ID of group
#define REG_DO_PWM_PERIOD__A00                   REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_PWM_PERIOD__A01                   (int32_t)3            //arg1: ID of subgroup by mode
#define REG_DO_PWM_PERIOD__A02                   (int32_t)4            //arg2: ID of register
#define REG_DO_PWM_PERIOD__TYPE                  TYPE_DWORD            //Data type
#define REG_DO_PWM_PERIOD__TYPE_SZ               TYPE_DWORD_SZ         //Size of data type in bytes
#define REG_DO_PWM_PERIOD__TYPE_WSZ              TYPE_DWORD_WSZ        //Size of data type in words
// position (offset) in REGS
#define REG_DO_PWM_PERIOD__POS                   (uint16_t)REG_CALC_POS(REG_DO_PWM_ALLOW__POS, REG_DO_PWM_ALLOW__SZ)
#define REG_DO_PWM_PERIOD__SZ                    (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_PWM_PERIOD__SADDR                 (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_PWM_PERIOD__DPOS                  (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_VAL__DPOS, REG_DO_PWM_VAL__SZ, REG_DO_PWM_VAL__TYPE_WSZ, 0)
#define REG_DO_PWM_PERIOD__DPOS_END              (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_PERIOD__DPOS, REG_DO_PWM_PERIOD__SZ, REG_DO_PWM_PERIOD__TYPE_WSZ, 0)-1
#define REG_DO_PWM_PERIOD__DTABLE                REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_PWM_PERIOD__MBPOS                 (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_VAL__MBPOS, REG_DO_PWM_VAL__SZ, REG_DO_PWM_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_DO_PWM_PERIOD__MBPOS_END             (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_PERIOD__MBPOS, REG_DO_PWM_PERIOD__SZ, REG_DO_PWM_PERIOD__TYPE_WSZ, 0)-1
#define REG_DO_PWM_PERIOD__MBTABLE               MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_PWM_PERIOD__EAREA                 EEPROM_AREA_SYSTEM     //EEPROM Area ID
#define REG_DO_PWM_PERIOD__EPOS                  (int32_t)REG_CALC_MBPOS(REG_DI_MODE__EPOS, REG_DI_MODE__SZ, REG_DI_MODE__TYPE_SZ, 0)
//STRING
#define REG_DO_PWM_PERIOD__STR                   "DO%d PWM: Period, ms"


/** @def DO: mode
 *  @note
 *       MB5.0.4 ... MB5.3.4
 *       App    > ModBus (> App)
 *       ModBus > T_DO
 */
#define REG_DO_MODE__GID                         (uint16_t)22          //Unique ID
// located variable
#define REG_DO_MODE__ZONE                        PLC_LT_M              //ID of memory
#define REG_DO_MODE__TYPESZ                      PLC_LSZ_B             //ID of data type
#define REG_DO_MODE__GROUP                       REG_DO__GROUP         //ID of group
#define REG_DO_MODE__A00                         REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_MODE__A01                         (int32_t)4            //arg1: ID of subgroup by mode
#define REG_DO_MODE__A02                         REG_AXX_NONE          //arg2: none
#define REG_DO_MODE__TYPE                        TYPE_BYTE             //Data type
#define REG_DO_MODE__TYPE_SZ                     TYPE_BYTE_SZ          //Size of data type in bytes
#define REG_DO_MODE__TYPE_WSZ                    TYPE_BYTE_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_MODE__POS                         (uint16_t)REG_CALC_POS(REG_DO_PWM_PERIOD__POS, REG_DO_PWM_PERIOD__SZ)
#define REG_DO_MODE__SZ                          (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_MODE__SADDR                       (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_MODE__DPOS                        (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_PERIOD__DPOS, REG_DO_PWM_PERIOD__SZ, REG_DO_PWM_PERIOD__TYPE_WSZ, 0)
#define REG_DO_MODE__DPOS_END                    (uint16_t)REG_CALC_MBPOS(REG_DO_MODE__DPOS, REG_DO_MODE__SZ, REG_DO_MODE__TYPE_WSZ, 0)-1
#define REG_DO_MODE__DTABLE                      REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_MODE__MBPOS                       (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_PERIOD__MBPOS, REG_DO_PWM_PERIOD__SZ, REG_DO_PWM_PERIOD__TYPE_WSZ, REG_RESERVE)
#define REG_DO_MODE__MBPOS_END                   (uint16_t)REG_CALC_MBPOS(REG_DO_MODE__MBPOS, REG_DO_MODE__SZ, REG_DO_MODE__TYPE_WSZ, 0)-1
#define REG_DO_MODE__MBTABLE                     MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_MODE__EAREA                       EEPROM_AREA_SYSTEM     //EEPROM Area ID
#define REG_DO_MODE__EPOS                        (int32_t)REG_CALC_MBPOS(REG_DO_PWM_PERIOD__EPOS, REG_DO_PWM_PERIOD__SZ, REG_DO_PWM_PERIOD__TYPE_SZ, 0)
//STRING
#define REG_DO_MODE__STR                         "DO%d: Mode"


/** @def DO: command 'Allow safe-mode'
 *  @note
 *       MX5.0.6 ... MX5.3.6
 *       App    > ModBus (> App)
 *       ModBus > T_DO
 */
#define REG_DO_SAFE_ALLOW__GID                   (uint16_t)24          //Unique ID
// located variable
#define REG_DO_SAFE_ALLOW__ZONE                  PLC_LT_M              //ID of memory
#define REG_DO_SAFE_ALLOW__TYPESZ                PLC_LSZ_X             //ID of data type
#define REG_DO_SAFE_ALLOW__GROUP                 REG_DO__GROUP         //ID of group
#define REG_DO_SAFE_ALLOW__A00                   REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_SAFE_ALLOW__A01                   (int32_t)6            //arg1: ID of subgroup by mode
#define REG_DO_SAFE_ALLOW__A02                   REG_AXX_NONE          //arg2: none
#define REG_DO_SAFE_ALLOW__TYPE                  TYPE_BOOL             //Data type
#define REG_DO_SAFE_ALLOW__TYPE_SZ               TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DO_SAFE_ALLOW__TYPE_WSZ              TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_SAFE_ALLOW__POS                   (uint16_t)REG_CALC_POS(REG_DO_MODE__POS, REG_DO_MODE__SZ)
#define REG_DO_SAFE_ALLOW__SZ                    (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_SAFE_ALLOW__SADDR                 (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_SAFE_ALLOW__DPOS                  (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_ALLOW__DPOS, REG_DO_PWM_ALLOW__SZ, REG_DO_PWM_ALLOW__TYPE_WSZ, 0)
#define REG_DO_SAFE_ALLOW__DPOS_END              (uint16_t)REG_CALC_MBPOS(REG_DO_SAFE_ALLOW__DPOS, REG_DO_SAFE_ALLOW__SZ, REG_DO_SAFE_ALLOW__TYPE_WSZ, 0)-1
#define REG_DO_SAFE_ALLOW__DTABLE                REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_SAFE_ALLOW__MBPOS                 (uint16_t)REG_CALC_MBPOS(REG_DO_PWM_ALLOW__MBPOS, REG_DO_PWM_ALLOW__SZ, REG_DO_PWM_ALLOW__TYPE_WSZ, REG_RESERVE)
#define REG_DO_SAFE_ALLOW__MBPOS_END             (uint16_t)REG_CALC_MBPOS(REG_DO_SAFE_ALLOW__MBPOS, REG_DO_SAFE_ALLOW__SZ, REG_DO_SAFE_ALLOW__TYPE_WSZ, 0)-1
#define REG_DO_SAFE_ALLOW__MBTABLE               MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_SAFE_ALLOW__EAREA                 EEPROM_AREA_SYSTEM     //EEPROM Area ID
#define REG_DO_SAFE_ALLOW__EPOS                  (int32_t)REG_CALC_MBPOS(REG_DO_MODE__EPOS, REG_DO_MODE__SZ, REG_DO_MODE__TYPE_SZ, 0)
//STRING
#define REG_DO_SAFE_ALLOW__STR                   "DO%d: Allow to work in safety mode"


/** @def DO: safe-mode value
 *  @note
 *       MX5.0.7 ... MX5.3.7
 *       App    > ModBus (> App)
 *       ModBus > T_DO
 */
#define REG_DO_SAFE_VAL__GID                     (uint16_t)25          //Unique ID
// located variable
#define REG_DO_SAFE_VAL__ZONE                    PLC_LT_M              //ID of memory
#define REG_DO_SAFE_VAL__TYPESZ                  PLC_LSZ_X             //ID of data type
#define REG_DO_SAFE_VAL__GROUP                   REG_DO__GROUP         //ID of group
#define REG_DO_SAFE_VAL__A00                     REG_AXX_ADDR          //arg0: channel number (auto)
#define REG_DO_SAFE_VAL__A01                     (int32_t)7            //arg1: ID of subgroup by mode
#define REG_DO_SAFE_VAL__A02                     REG_AXX_NONE          //arg2: none
#define REG_DO_SAFE_VAL__TYPE                    TYPE_BOOL             //Data type
#define REG_DO_SAFE_VAL__TYPE_SZ                 TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_DO_SAFE_VAL__TYPE_WSZ                TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_DO_SAFE_VAL__POS                     (uint16_t)REG_CALC_POS(REG_DO_SAFE_ALLOW__POS, REG_DO_SAFE_ALLOW__SZ)
#define REG_DO_SAFE_VAL__SZ                      (uint16_t)PLC_DO_SZ   //Number of registers
#define REG_DO_SAFE_VAL__SADDR                   (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_DO_SAFE_VAL__DPOS                    (uint16_t)REG_CALC_MBPOS(REG_DO_SAFE_ALLOW__DPOS, REG_DO_SAFE_ALLOW__SZ, REG_DO_SAFE_ALLOW__TYPE_WSZ, 0)
#define REG_DO_SAFE_VAL__DPOS_END                (uint16_t)REG_CALC_MBPOS(REG_DO_SAFE_VAL__DPOS, REG_DO_SAFE_VAL__SZ, REG_DO_SAFE_VAL__TYPE_WSZ, 0)-1
#define REG_DO_SAFE_VAL__DTABLE                  REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_DO_SAFE_VAL__MBPOS                   (uint16_t)REG_CALC_MBPOS(REG_DO_SAFE_ALLOW__MBPOS, REG_DO_SAFE_ALLOW__SZ, REG_DO_SAFE_ALLOW__TYPE_WSZ, REG_RESERVE)
#define REG_DO_SAFE_VAL__MBPOS_END               (uint16_t)REG_CALC_MBPOS(REG_DO_SAFE_VAL__MBPOS, REG_DO_SAFE_VAL__SZ, REG_DO_SAFE_VAL__TYPE_WSZ, 0)-1
#define REG_DO_SAFE_VAL__MBTABLE                 MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_DO_SAFE_VAL__EAREA                   EEPROM_AREA_SYSTEM     //EEPROM Area ID
#define REG_DO_SAFE_VAL__EPOS                    (int32_t)REG_CALC_MBPOS(REG_DO_SAFE_ALLOW__EPOS, REG_DO_SAFE_ALLOW__SZ, REG_DO_SAFE_ALLOW__TYPE_SZ, 0)
//STRING
#define REG_DO_SAFE_VAL__STR                     "DO%d: Safety value"


// System statuses ====================

#define REG_SYS__GROUP                           (uint16_t)7

#define REG_SYS_STAT_SZ                          (uint16_t)12          //quantity of registers

/** @def System states
 */
#define REG_SYS_STAT__GID                        (uint16_t)52          //Unique ID
// located variable
#define REG_SYS_STAT__ZONE                       PLC_LT_M              //ID of memory
#define REG_SYS_STAT__TYPESZ                     PLC_LSZ_W             //ID of data type
#define REG_SYS_STAT__GROUP                      REG_SYS__GROUP
#define REG_SYS_STAT__A00                        (int32_t)3            //arg0: ID of subgrouГ§
#define REG_SYS_STAT__A01                        REG_AXX_ADDR          //arg1: ID of subgroup
#define REG_SYS_STAT__A02                        REG_AXX_NONE          //arg2: ID of subgroup
#define REG_SYS_STAT__TYPE                       TYPE_WORD             //Data type
#define REG_SYS_STAT__TYPE_SZ                    TYPE_WORD_SZ          //Size of data type in bytes
#define REG_SYS_STAT__TYPE_WSZ                   TYPE_WORD_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_SYS_STAT__POS                        (uint16_t)REG_CALC_POS(REG_DO_SAFE_VAL__POS, REG_DO_SAFE_VAL__SZ)
#define REG_SYS_STAT__SZ                         (uint16_t)REG_SYS_STAT_SZ  //number of registers
#define REG_SYS_STAT__SADDR                      (uint16_t)0                //start register address
// position (offset) in Data Table
#define REG_SYS_STAT__DPOS                       (uint16_t)REG_CALC_MBPOS(REG_DO_MODE__DPOS, REG_DO_MODE__SZ, REG_DO_MODE__TYPE_WSZ, 0)
#define REG_SYS_STAT__DPOS_END                   (uint16_t)REG_CALC_MBPOS(REG_SYS_STAT__DPOS, REG_SYS_STAT__SZ, REG_SYS_STAT__TYPE_WSZ, 0)-1
#define REG_SYS_STAT__DTABLE                     REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_SYS_STAT__MBPOS                      (uint16_t)REG_CALC_MBPOS(REG_DI_CNTR_VAL__MBPOS, REG_DI_CNTR_VAL__SZ, REG_DI_CNTR_VAL__TYPE_WSZ, REG_RESERVE)
#define REG_SYS_STAT__MBPOS_END                  (uint16_t)REG_CALC_MBPOS(REG_SYS_STAT__MBPOS, REG_SYS_STAT__SZ, REG_SYS_STAT__TYPE_WSZ, 0)-1
#define REG_SYS_STAT__MBTABLE                    MBRTU_INPT_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_SYS_STAT__EAREA                      EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_SYS_STAT__EPOS                       EEPROM_ADDR_NONE

//REGS Positions
#define REG_SYS_STAT__POS_HW_CODE                (REG_SYS_STAT__POS+0)    //Hardware code
#define REG_SYS_STAT__POS_RTE_VER                (REG_SYS_STAT__POS+1)    //RTE version (minor major)
#define REG_SYS_STAT__POS_RTE_YYYY               (REG_SYS_STAT__POS+2)    //RTE YYYY (year)
#define REG_SYS_STAT__POS_RTE_DDMM               (REG_SYS_STAT__POS+3)    //RTE DDMM (day month)
#define REG_SYS_STAT__POS_HW_VAR                 (REG_SYS_STAT__POS+4)    //Hardware variant
#define REG_SYS_STAT__POS_DI_NORM                (REG_SYS_STAT__POS+5)    //DI Normal (values, packed)
#define REG_SYS_STAT__POS_DI_TACH_SP_RES         (REG_SYS_STAT__POS+6)    //DI Tachometer (setpoint reached, packed)
#define REG_SYS_STAT__POS_DI_CNT_SP_RES          (REG_SYS_STAT__POS+7)    //DI Counter (setpoint reached, packed)
#define REG_SYS_STAT__POS_DO_PWM_RES             (REG_SYS_STAT__POS+8)    //DO PWM (state, packed)
#define REG_SYS_STAT__POS_STAT1                  (REG_SYS_STAT__POS+9)    //System statuses (1), (packed)
#define REG_SYS_STAT__POS_STAT2                  (REG_SYS_STAT__POS+10)   //System statuses (2), (packed)
#define REG_SYS_STAT__POS_EE                     (REG_SYS_STAT__POS+11)   //EEPROM operation-status

//ModBus Addresses
#define REG_SYS_STAT__MBPOS_HW_CODE              (REG_SYS_STAT__MBPOS+0)  //Hardware code
#define REG_SYS_STAT__MBPOS_RTE_VER              (REG_SYS_STAT__MBPOS+1)  //RTE version (minor major)
#define REG_SYS_STAT__MBPOS_RTE_YYYY             (REG_SYS_STAT__MBPOS+2)  //RTE YYYY (year)
#define REG_SYS_STAT__MBPOS_RTE_DDMM             (REG_SYS_STAT__MBPOS+3)  //RTE DDMM (day month)
#define REG_SYS_STAT__MBPOS_HW_VAR               (REG_SYS_STAT__MBPOS+4)  //Hardware variant
#define REG_SYS_STAT__MBPOS_DI_NORM              (REG_SYS_STAT__MBPOS+5)  //DI Normal (values, packed)
#define REG_SYS_STAT__MBPOS_DI_TACH_SP_RES       (REG_SYS_STAT__MBPOS+6)  //DI Tachometer (setpoint reached, packed)
#define REG_SYS_STAT__MBPOS_DI_CNT_SP_RES        (REG_SYS_STAT__MBPOS+7)  //DI Counter (setpoint reached, packed)
#define REG_SYS_STAT__MBPOS_DO_PWM_RES           (REG_SYS_STAT__MBPOS+8)  //DO PWM (state, packed)
#define REG_SYS_STAT__MBPOS_STAT1                (REG_SYS_STAT__MBPOS+9)  //System statuses (1), (packed)
#define REG_SYS_STAT__MBPOS_STAT2                (REG_SYS_STAT__MBPOS+10) //System statuses (2), (packed)
#define REG_SYS_STAT__MBPOS_EE                   (REG_SYS_STAT__MBPOS+11) //EEPROM operation-status

//STRING
#define REG_SYS_STAT__STR_HW_CODE                "Hardware code"
#define REG_SYS_STAT__STR_RTE_VER                "RTE version"
#define REG_SYS_STAT__STR_RTE_YYYY               "RTE version (year)"
#define REG_SYS_STAT__STR_RTE_DDMM               "RTE version (day month)"
#define REG_SYS_STAT__STR_HW_VAR                 "Hardware variant"
#define REG_SYS_STAT__STR_DI_NORM                "DI Norm (packed values)"
#define REG_SYS_STAT__STR_DI_TACH_SP_RES         "DI Tach (packed values)"
#define REG_SYS_STAT__STR_DI_CNT_SP_RES          "DI Cntr (packed values)"
#define REG_SYS_STAT__STR_DO_PWM_RES             "DO PWM (packed values)"
#define REG_SYS_STAT__STR_STAT1                  "System statuses (1)"
#define REG_SYS_STAT__STR_STAT2                  "System statuses (2)"
#define REG_SYS_STAT__STR_EE                     "EEPROM tatus"

// User data ==========================

#define REG_USER_DATA__GROUP                     (uint16_t)8

/** @def User data (bool)
 *  @note
 *       App > ModBus (> App)
 */
#define REG_USER_DATA1__GID                      (uint16_t)55          //Unique ID
// located variable
#define REG_USER_DATA1__ZONE                     PLC_LT_M              //ID of memory
#define REG_USER_DATA1__TYPESZ                   PLC_LSZ_X             //ID of data type
#define REG_USER_DATA1__GROUP                    REG_USER_DATA__GROUP  //ID of group
#define REG_USER_DATA1__A00                      (int32_t)1            //ID of subgroup
#define REG_USER_DATA1__A01                      REG_AXX_ADDR
#define REG_USER_DATA1__A02                      REG_AXX_NONE
#define REG_USER_DATA1__TYPE                     TYPE_BOOL             //Data type
#define REG_USER_DATA1__TYPE_SZ                  TYPE_BOOL_SZ          //Size of data type in bytes
#define REG_USER_DATA1__TYPE_WSZ                 TYPE_BOOL_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_USER_DATA1__POS                      (uint16_t)REG_CALC_POS(REG_SYS_STAT__POS, REG_SYS_STAT__SZ)
#define REG_USER_DATA1__SZ                       (uint16_t)16          //Number of registers
#define REG_USER_DATA1__SADDR                    (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_USER_DATA1__DPOS                     (uint16_t)REG_CALC_MBPOS(REG_DO_SAFE_VAL__DPOS, REG_DO_SAFE_VAL__SZ, REG_DO_SAFE_VAL__TYPE_WSZ, 0)
#define REG_USER_DATA1__DPOS_END                 (uint16_t)REG_CALC_MBPOS(REG_USER_DATA1__DPOS, REG_USER_DATA1__SZ, REG_USER_DATA1__TYPE_WSZ, 0)-1
#define REG_USER_DATA1__DTABLE                   REG_DATA_BOOL_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_USER_DATA1__MBPOS                    (uint16_t)REG_CALC_MBPOS(REG_DO_SAFE_VAL__MBPOS, REG_DO_SAFE_VAL__SZ, REG_DO_SAFE_VAL__TYPE_WSZ, 0)
#define REG_USER_DATA1__MBPOS_END                (uint16_t)REG_CALC_MBPOS(REG_USER_DATA1__MBPOS, REG_USER_DATA1__SZ, REG_USER_DATA1__TYPE_WSZ, 0)-1
#define REG_USER_DATA1__MBTABLE                  MBRTU_COIL_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_USER_DATA1__EAREA                    EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_USER_DATA1__EPOS                     EEPROM_ADDR_NONE
//STRING
#define REG_USER_DATA1__STR                      "User Data %d"


/** @def User data (word)
 *  @note
 *       App > ModBus (> App)
 */
#define REG_USER_DATA2__GID                      (uint16_t)56          //Unique ID
// located variable
#define REG_USER_DATA2__ZONE                     PLC_LT_M              //ID of memory
#define REG_USER_DATA2__TYPESZ                   PLC_LSZ_W             //ID of data type
#define REG_USER_DATA2__GROUP                    REG_USER_DATA__GROUP  //ID of group
#define REG_USER_DATA2__A00                      (int32_t)2            //ID of subgroup
#define REG_USER_DATA2__A01                      REG_AXX_ADDR
#define REG_USER_DATA2__A02                      REG_AXX_NONE
#define REG_USER_DATA2__TYPE                     TYPE_WORD             //Data type
#define REG_USER_DATA2__TYPE_SZ                  TYPE_WORD_SZ          //Size of data type in bytes
#define REG_USER_DATA2__TYPE_WSZ                 TYPE_WORD_WSZ         //Size of data type in words
// position (offset) in REGS
#define REG_USER_DATA2__POS                      (uint16_t)REG_CALC_POS(REG_USER_DATA1__POS, REG_USER_DATA1__SZ)
#define REG_USER_DATA2__SZ                       (uint16_t)16          //Number of registers
#define REG_USER_DATA2__SADDR                    (uint16_t)0           //Start register address
// position (offset) in Data Table
#define REG_USER_DATA2__DPOS                     (uint16_t)REG_CALC_MBPOS(REG_SYS_STAT__DPOS, REG_SYS_STAT__SZ, REG_SYS_STAT__TYPE_WSZ, 0)
#define REG_USER_DATA2__DPOS_END                 (uint16_t)REG_CALC_MBPOS(REG_USER_DATA2__DPOS, REG_USER_DATA2__SZ, REG_USER_DATA2__TYPE_WSZ, 0)-1
#define REG_USER_DATA2__DTABLE                   REG_DATA_NUMB_TABLE_ID  //Data Table ID
// position (offset) in ModBus Table
#define REG_USER_DATA2__MBPOS                    (uint16_t)REG_CALC_MBPOS(REG_DO_MODE__MBPOS, REG_DO_MODE__SZ, REG_DO_MODE__TYPE_WSZ, 0)
#define REG_USER_DATA2__MBPOS_END                (uint16_t)REG_CALC_MBPOS(REG_USER_DATA2__MBPOS, REG_USER_DATA2__SZ, REG_USER_DATA2__TYPE_WSZ, 0)-1
#define REG_USER_DATA2__MBTABLE                  MBRTU_HOLD_TABLE_ID   //ModBus Table ID
// EEPROM
#define REG_USER_DATA2__EAREA                    EEPROM_AREA_NONE  //EEPROM Area ID
#define REG_USER_DATA2__EPOS                     EEPROM_ADDR_NONE
//STRING
#define REG_USER_DATA2__STR                      "User Data %d"

//=============================================================================
//=============================================================================
//=============================================================================


/** @def Position of last register in REGS
 */
#define REG_LAST_POS                             (uint16_t)REG_CALC_POS(REG_USER_DATA2__POS, REG_USER_DATA2__SZ)

/** @def Position of last register in Data-table
 */
#define REG_DATA_BOOL_LAST_POS                   (uint16_t)(REG_USER_DATA1__DPOS_END+1)
#define REG_DATA_NUMB_LAST_POS                   (uint16_t)(REG_USER_DATA2__DPOS_END+1)

/** @def Position of last register in ModBus Table
 */
#define REG_LAST_COIL_POS                        (uint16_t)(REG_USER_DATA1__MBPOS_END+1)
#define REG_LAST_HOLD_POS                        (uint16_t)(REG_USER_DATA2__MBPOS_END+1)
#define REG_LAST_DISC_POS                        (uint16_t)(REG_DI_CNTR_SETPOINT_RES__MBPOS_END+1)
#define REG_LAST_INPT_POS                        (uint16_t)(REG_SYS_STAT__MBPOS_END+1)

/** @def Position of last register in EEPROM areas
 */
#define REG_LAST_EEPROM_SYS_POS                  (uint16_t)(0)
#define REG_LAST_EEPROM_USER_POS                 (uint16_t)(0)

//=============================================================================


/** @def Max. register address
 */
#define REG_ADDR_MAX                             (uint16_t)0xFFFF

/** @def Quantity of registers
 */
#define REG_SZ                                   REG_LAST_POS

/** @def Quantity of registers
 *       (Data Table)
 */
#define REG_DATA_BOOL_SZ                         REG_DATA_BOOL_LAST_POS
#define REG_DATA_NUMB_SZ                         REG_DATA_NUMB_LAST_POS

/** @def Quantity of registers
 *       (ModBus Table)
 */
#define MBRTU_COIL_SZ                            REG_LAST_COIL_POS
#define MBRTU_DISC_SZ                            REG_LAST_DISC_POS
#define MBRTU_HOLD_SZ                            REG_LAST_HOLD_POS
#define MBRTU_INPT_SZ                            REG_LAST_INPT_POS
//
/** @def Start-End address
 *       (ModBus Table)
 */
#define MBRTU_COIL_START                        (uint16_t)0
#define MBRTU_COIL_END                          (uint16_t)(MBRTU_COIL_START+MBRTU_COIL_SZ-1)
#define MBRTU_DISC_START                        (uint16_t)0
#define MBRTU_DISC_END                          (uint16_t)(MBRTU_DISC_START+MBRTU_DISC_SZ-1)
#define MBRTU_HOLD_START                        (uint16_t)0
#define MBRTU_HOLD_END                          (uint16_t)(MBRTU_HOLD_START+MBRTU_HOLD_SZ-1)
#define MBRTU_INPT_START                        (uint16_t)0
#define MBRTU_INPT_END                          (uint16_t)(MBRTU_INPT_START+MBRTU_INPT_SZ-1)

#endif //REG_MAP_H
