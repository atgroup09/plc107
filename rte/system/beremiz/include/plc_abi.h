/* @page plc_abi.h
 *       PLC ABI
 *       from YAPLC
 *       2020-2022
 */

#ifndef PLC_ABI_H_
#define PLC_ABI_H_

#include <stdbool.h>
#include <stdint.h>
#include <iec_types_all.h>


/** @def Located variables
 *       zones
 */
#define PLC_LT_I                       (uint8_t)0   //Inputs
#define PLC_LT_M                       (uint8_t)1   //Memory
#define PLC_LT_Q                       (uint8_t)2   //Outputs


/** @def Located variables
 *       types
 */
#define PLC_LSZ_X                      (uint8_t)0   //BOOL
#define PLC_LSZ_B                      (uint8_t)1   //SINT, USINT, BYTE, STRING  (CHAR*)
#define PLC_LSZ_W                      (uint8_t)2   //INT,  UINT,  WORD, WSTRING (WCHAR*)
#define PLC_LSZ_D                      (uint8_t)3   //DINT, UDINT, REAL, DWORD
#define PLC_LSZ_L                      (uint8_t)4   //LINT, ULINT, LREAL, LWORD


/** @def Located variables
 *       number bytes for types
 */
#define PLC_BSZ_X                      (uint8_t)1
#define PLC_BSZ_B                      (uint8_t)1
#define PLC_BSZ_W                      (uint8_t)2
#define PLC_BSZ_D                      (uint8_t)4
#define PLC_BSZ_L                      (uint8_t)8


/** @typedef Functions
 */
typedef struct
{
    //DI
    void (*DIMode)(BOOL *, BYTE *, BYTE *, BYTE *, BYTE *);
    void (*DIVal)(BOOL *, BYTE *, BOOL *, BYTE *);
    void (*DICntT)(BOOL *, BYTE *, WORD *, BOOL *, WORD *, BOOL *, BYTE *);
    void (*DICnt)(BOOL *, BYTE *, DWORD *, BOOL *, DWORD *, BOOL *, BYTE *);
    void (*DICntRst)(BOOL *, BYTE *, BOOL *, BYTE *);
    void (*DIEnc)(BOOL *, BYTE *, DWORD *, BOOL *, DWORD *, BOOL *, WORD *, BOOL *, DWORD *, BOOL *, DWORD *, BOOL *, WORD *, BOOL *, BYTE *);

    //DO
    void (*DOMode)(BOOL *, BYTE *, BYTE *, BYTE *, BYTE *);
    void (*DOVal)(BOOL *, BYTE *, BOOL *, BOOL *, BYTE *);
    void (*DOFast)(BOOL *, BYTE *, BOOL *, BOOL *, BYTE *);
    void (*DOPwm)(BOOL *, BOOL *, BYTE *, DWORD *, REAL *, BOOL *, BYTE *);
    void (*DOSafe)(BOOL *, BOOL *, BYTE *, BOOL *, BOOL *, BOOL *, BYTE *);

    //AI
    void (*AIMode)(BOOL *, BYTE *, BYTE *, BYTE *, BYTE *, BYTE *);
    void (*AIVal)(BOOL *, BYTE *, REAL *, BYTE *, BYTE *);

    //AO
    void (*AOMode)(BOOL *, BYTE *, BYTE *, BYTE *, BYTE *);
    void (*AOVal)(BOOL *, BYTE *, REAL *, REAL *, BYTE *);
    void (*AOFast)(BOOL *, BYTE *, REAL *, REAL *, BYTE *);
    void (*AOSafe)(BOOL *, BOOL *, BYTE *, REAL *, REAL *, BOOL *, BYTE *);

    //SYSTEM
    void (*SoftReset)(BOOL);

    //SYS
    void (*GetTime)(IEC_TIME *);

} plc_app_funcs_t;


/** @typedef Located variables
 *           description of variable
 */
typedef struct _plc_loc_dsc_t
{
    void *v_buf;                       //@var Pointer to variable value buffer
    uint8_t v_type;                    //@var Zone ID
    uint8_t v_size;                    //@var Data Type Size ID
    uint16_t a_size;                   //@var Size of arguments
    const uint32_t *a_data;            //@var Pointer to buffer of arguments
    uint16_t proto;                    //@var Group ID

} plc_loc_dsc_t;


typedef const plc_loc_dsc_t *plc_loc_tbl_t;
typedef void (*app_fp_t) (void);


/** @typedef APP-ABI
 */
typedef struct
{
    uint32_t *sstart;
    app_fp_t entry;

    //App startup interface
    //* pointers are set in target C-file (yaplctargets)
    //* values   are set in target-app.ld
    uint32_t *data_loadaddr;
    uint32_t *data_start;
    uint32_t *data_end;
    uint32_t *bss_end;
    app_fp_t *pa_start;
    app_fp_t *pa_end;
    app_fp_t *ia_start;
    app_fp_t *ia_end;
    app_fp_t *fia_start;
    app_fp_t *fia_end;

    //RTE Version control
    //Semantic versioning is used
    //* values are set in target C-file (yaplctargets)
    //* equivalent values in plc_app.h
    uint32_t rte_ver_major;
    uint32_t rte_ver_minor;
    uint32_t rte_ver_patch;

    //Hardware ID
    //* value is set in target C-file (yaplctargets)
    //* equivalent value in plc_app.h
    uint32_t hw_id;

    //IO manager data
    //* values are set in target C-file (yaplctargets)
    plc_loc_tbl_t *l_tab;      //Location table
    uint32_t *w_tab;           //Weigth table
    uint16_t  l_sz;            //Location table size

    //EEPROM registers
    //plc_app_eereg_t *ee_regs;  //pointer to array of registers
    //uint16_t  ee_sz;           //length of array

    //Functions
    plc_app_funcs_t *funcs;

    //Common ticktime
    unsigned long long *common_ticktime;

    //Control instance of PLC_ID (md5)
    //* value is set in target C-file (yaplctargets)
    const char *check_id;   //Must be placed to the end of .text

    //App interface (md5)
    //* value is set in target C-file (yaplctargets)
    const char *id;      //Must be placed near the start of .text

    //Functions
    //* functions are declared in target C-file (yaplctargets)
    //* pointers are set in target C-file (yaplctargets)

    int (*start)(int , char **);
    int (*stop)(void);
    void (*run)(void);

    void (*dbg_resume)(void);
    void (*dbg_suspend)(int);

    int  (*dbg_data_get)(unsigned long *, unsigned long *, void **);
    void (*dbg_data_free)(void);

    void (*dbg_vars_reset)(void);
    void (*dbg_var_register)(int, void *);

    uint32_t (*log_cnt_get)(uint8_t);
    uint32_t (*log_msg_get)(uint8_t, uint32_t, char*, uint32_t, uint32_t*, uint32_t*, uint32_t*);
    void     (*log_cnt_reset)(void);
    int      (*log_msg_post)(uint8_t, char*, uint32_t);

} plc_app_abi_t;


/** @typedef RTE-ABI
 */
typedef struct
{
    void (*get_time)(IEC_TIME *);
    void (*set_timer)(unsigned long long, unsigned long long);

    int  (*check_retain_buf)(void);
    void (*invalidate_retain_buf)(void); //Call before saving
    void (*validate_retain_buf)(void);   //Call after saving

    void (*retain)(unsigned int, unsigned int, void *);
    void (*remind)(unsigned int, unsigned int, void *);

} plc_rte_abi_t;


/** @var Pointer to ABI (application)
 *       real define in plc_app.c
 */
extern plc_app_abi_t *PLC_APP_CURR;


/** @def Macroses
 */
#define PLC_LOC_CONCAT(a, b)           a##b
#define PLC_LOC_TYPE(a)                PLC_LOC_CONCAT(PLC_LT_, a)
#define PLC_LOC_SIZE(a)                PLC_LOC_CONCAT(PLC_LSZ_, a)


/** @def Logging
 */
#define LOG_LEVELS                    4
#define LOG_CRITICAL                  0
#define LOG_WARNING                   1
#define LOG_INFO                      2
#define LOG_DEBUG                     3

#endif // PLC_ABI_H_
