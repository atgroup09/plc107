#include "beremiz.h"
#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

__DECLARE_ENUMERATED_TYPE(LOGLEVEL,
  LOGLEVEL__CRITICAL,
  LOGLEVEL__WARNING,
  LOGLEVEL__INFO,
  LOGLEVEL__DEBUG
)
// FUNCTION_BLOCK LOGGER
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,MSG)
  __DECLARE_VAR(LOGLEVEL,LEVEL)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TRIG0)

} LOGGER;

void LOGGER_init__(LOGGER *data__, BOOL retain);
// Code part
void LOGGER_body__(LOGGER *data__);
// FUNCTION
REAL SCALEA(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX, 
  REAL V, 
  REAL KA, 
  REAL KB, 
  REAL Y);
// FUNCTION
REAL SCALEA_KB(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX, 
  REAL V1, 
  REAL V2, 
  REAL Y1, 
  REAL Y2, 
  REAL KB);
// FUNCTION_BLOCK TONTEST
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,IN)
  __DECLARE_VAR(DWORD,MS)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(TIME,ET)
  __DECLARE_VAR(DWORD,EDW)
  __DECLARE_VAR(REAL,EREA)

  // FB private variables - TEMP, private and located variables
  TON TON1;
  __DECLARE_VAR(BOOL,TON1_IN)
  __DECLARE_VAR(TIME,TON1_TM)

} TONTEST;

void TONTEST_init__(TONTEST *data__, BOOL retain);
// Code part
void TONTEST_body__(TONTEST *data__);
// FUNCTION
REAL SCALEA_KA(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX, 
  REAL V1, 
  REAL V2, 
  REAL Y1, 
  REAL Y2, 
  REAL KA);
// FUNCTION_BLOCK TONCONT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,IN)
  __DECLARE_VAR(BOOL,Q)
  __DECLARE_VAR(TIME,ET)

  // FB private variables - TEMP, private and located variables
  TON TON1;
  __DECLARE_VAR(BOOL,TON1_IN)
  __DECLARE_VAR(TIME,TON1_TM)
  TON TON1INC;
  __DECLARE_VAR(BOOL,TON1INC_IN)
  __DECLARE_VAR(TIME,TON1INC_TM)

} TONCONT;

void TONCONT_init__(TONCONT *data__, BOOL retain);
// Code part
void TONCONT_body__(TONCONT *data__);
// FUNCTION_BLOCK FLRTUN
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(REAL,V)
  __DECLARE_VAR(REAL,DIFF)
  __DECLARE_VAR(BYTE,PRO)
  __DECLARE_VAR(BYTE,OK)
  __DECLARE_VAR(REAL,OY)
  __DECLARE_VAR(DWORD,OTM)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TUNDONE)
  __DECLARE_VAR(REAL,TM1)
  __DECLARE_VAR(BOOL,V1SET)
  __DECLARE_VAR(REAL,V01)
  TONCONT TONCONT1;
  __DECLARE_VAR(BOOL,TONCONT1_IN)

} FLRTUN;

void FLRTUN_init__(FLRTUN *data__, BOOL retain);
// Code part
void FLRTUN_body__(FLRTUN *data__);
// FUNCTION
BOOL GETBITWO(
  BOOL EN, 
  BOOL *__ENO, 
  WORD WO, 
  BYTE POS);
// FUNCTION_BLOCK FILTRD
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BOOL,V)
  __DECLARE_VAR(TIME,TM)
  __DECLARE_VAR(BOOL,OV)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,VAL)
  TON TON0;
  TON TON1;

} FILTRD;

void FILTRD_init__(FILTRD *data__, BOOL retain);
// Code part
void FILTRD_body__(FILTRD *data__);
// FUNCTION_BLOCK FLR1
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(REAL,V)
  __DECLARE_VAR(REAL,SP)
  __DECLARE_VAR(BYTE,PRO)
  __DECLARE_VAR(BOOL,SCK)
  __DECLARE_VAR(DWORD,TM)
  __DECLARE_VAR(REAL,DV)
  __DECLARE_VAR(REAL,DZ)
  __DECLARE_VAR(REAL,DE)
  __DECLARE_VAR(DWORD,DETM)
  __DECLARE_VAR(BYTE,YM)
  __DECLARE_VAR(BYTE,OK)
  __DECLARE_VAR(REAL,OY)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(REAL,VPREV)
  __DECLARE_VAR(REAL,TMDV)
  __DECLARE_VAR(SINT,UPDOWN)
  __DECLARE_VAR(BOOL,SCKSET)
  __DECLARE_VAR(BOOL,ERRORSET)
  __DECLARE_VAR(REAL,ER)
  TON TON_DE;
  __DECLARE_VAR(BOOL,TON_DE_IN)
  __DECLARE_VAR(TIME,TON_DE_TM)
  __DECLARE_VAR(REAL,DEV)
  __DECLARE_VAR(BOOL,DEV1SET)
  __DECLARE_VAR(BOOL,DEV2SET)
  TON TON_DV;
  __DECLARE_VAR(BOOL,TON_DV_IN)
  __DECLARE_VAR(TIME,TON_DV_TM)

} FLR1;

void FLR1_init__(FLR1 *data__, BOOL retain);
// Code part
void FLR1_body__(FLR1 *data__);
// FUNCTION_BLOCK FLR2
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(REAL,V)
  __DECLARE_VAR(REAL,SP)
  __DECLARE_VAR(BYTE,PRO)
  __DECLARE_VAR(DWORD,TM)
  __DECLARE_VAR(REAL,DV)
  __DECLARE_VAR(REAL,DZ)
  __DECLARE_VAR(REAL,DE)
  __DECLARE_VAR(DWORD,DETM)
  __DECLARE_VAR(BYTE,YM)
  __DECLARE_VAR(BYTE,OK)
  __DECLARE_VAR(REAL,OY)

  // FB private variables - TEMP, private and located variables
  TON TON_WORK;
  __DECLARE_VAR(BOOL,TON_WORK_IN)
  __DECLARE_VAR(TIME,TON_WORK_TM)
  FLR1 FLR1_1;

} FLR2;

void FLR2_init__(FLR2 *data__, BOOL retain);
// Code part
void FLR2_body__(FLR2 *data__);
// FUNCTION_BLOCK PIDTUN
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(REAL,V)
  __DECLARE_VAR(REAL,DIFF)
  __DECLARE_VAR(BYTE,TY)
  __DECLARE_VAR(BYTE,PRO)
  __DECLARE_VAR(BYTE,OK)
  __DECLARE_VAR(REAL,OY)
  __DECLARE_VAR(REAL,OKP)
  __DECLARE_VAR(REAL,OKI)
  __DECLARE_VAR(REAL,OKD)
  __DECLARE_VAR(DWORD,OTM)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TUNDONE)
  __DECLARE_VAR(REAL,TM1)
  __DECLARE_VAR(REAL,TM2)
  __DECLARE_VAR(REAL,TMSUM)
  __DECLARE_VAR(BOOL,V1SET)
  __DECLARE_VAR(REAL,V01)
  __DECLARE_VAR(REAL,V063)
  __DECLARE_VAR(REAL,RR)
  __DECLARE_VAR(REAL,TM1SEC)
  TONCONT TONCONT1;
  __DECLARE_VAR(BOOL,TONCONT1_IN)

} PIDTUN;

void PIDTUN_init__(PIDTUN *data__, BOOL retain);
// Code part
void PIDTUN_body__(PIDTUN *data__);
// FUNCTION
WORD SETBITWO(
  BOOL EN, 
  BOOL *__ENO, 
  WORD WO, 
  BYTE POS, 
  BOOL VAL);
// FUNCTION_BLOCK FILTRA
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(REAL,V)
  __DECLARE_VAR(REAL,K)
  __DECLARE_VAR(REAL,OV)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(REAL,VAL)
  __DECLARE_VAR(REAL,KLIM)

} FILTRA;

void FILTRA_init__(FILTRA *data__, BOOL retain);
// Code part
void FILTRA_body__(FILTRA *data__);
// FUNCTION_BLOCK PID1
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(REAL,V)
  __DECLARE_VAR(REAL,SP)
  __DECLARE_VAR(BYTE,TY)
  __DECLARE_VAR(BYTE,PRO)
  __DECLARE_VAR(REAL,KP)
  __DECLARE_VAR(REAL,KI)
  __DECLARE_VAR(REAL,KD)
  __DECLARE_VAR(BOOL,SCK)
  __DECLARE_VAR(REAL,DI)
  __DECLARE_VAR(REAL,DZ)
  __DECLARE_VAR(REAL,DE)
  __DECLARE_VAR(DWORD,DETM)
  __DECLARE_VAR(BYTE,YM)
  __DECLARE_VAR(BYTE,OK)
  __DECLARE_VAR(REAL,OY)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(REAL,ER)
  __DECLARE_VAR(REAL,ERABS)
  __DECLARE_VAR(REAL,ERPREV)
  __DECLARE_VAR(REAL,ERDIFF)
  __DECLARE_VAR(REAL,PPART)
  __DECLARE_VAR(REAL,IPART)
  __DECLARE_VAR(REAL,DPART)
  __DECLARE_VAR(REAL,DEV)
  __DECLARE_VAR(BOOL,DEV1SET)
  __DECLARE_VAR(BOOL,DEV2SET)
  __DECLARE_VAR(BOOL,SCKSET)
  __DECLARE_VAR(BOOL,ERRORSET)
  TON TON_DE;
  __DECLARE_VAR(BOOL,TON_DE_IN)
  __DECLARE_VAR(TIME,TON_DE_TM)

} PID1;

void PID1_init__(PID1 *data__, BOOL retain);
// Code part
void PID1_body__(PID1 *data__);
// FUNCTION_BLOCK PID2
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(REAL,V)
  __DECLARE_VAR(REAL,SP)
  __DECLARE_VAR(BYTE,TY)
  __DECLARE_VAR(BYTE,PRO)
  __DECLARE_VAR(REAL,KP)
  __DECLARE_VAR(REAL,KI)
  __DECLARE_VAR(REAL,KD)
  __DECLARE_VAR(DWORD,TM)
  __DECLARE_VAR(REAL,DI)
  __DECLARE_VAR(REAL,DZ)
  __DECLARE_VAR(REAL,DE)
  __DECLARE_VAR(DWORD,DETM)
  __DECLARE_VAR(BYTE,YM)
  __DECLARE_VAR(BYTE,OK)
  __DECLARE_VAR(REAL,OY)

  // FB private variables - TEMP, private and located variables
  TON TON_WORK;
  __DECLARE_VAR(BOOL,TON_WORK_IN)
  __DECLARE_VAR(TIME,TON_WORK_TM)
  PID1 PID1_1;

} PID2;

void PID2_init__(PID2 *data__, BOOL retain);
// Code part
void PID2_body__(PID2 *data__);
// FUNCTION
INT DEC(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX, 
  INT V);
// FUNCTION
INT INC(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX, 
  INT V);
// FUNCTION
BOOL SOFTRESET(
  BOOL EN, 
  BOOL *__ENO, 
  BOOL EX);
// FUNCTION_BLOCK DICNTT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,DIN)
  __DECLARE_VAR(WORD,REF)
  __DECLARE_VAR(BOOL,REFEN)
  __DECLARE_VAR(WORD,OV)
  __DECLARE_VAR(BOOL,OREF)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} DICNTT;

void DICNTT_init__(DICNTT *data__, BOOL retain);
// Code part
void DICNTT_body__(DICNTT *data__);
// FUNCTION_BLOCK DICNT
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,DIN)
  __DECLARE_VAR(DWORD,REF)
  __DECLARE_VAR(BOOL,REFEN)
  __DECLARE_VAR(DWORD,OV)
  __DECLARE_VAR(BOOL,OREF)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} DICNT;

void DICNT_init__(DICNT *data__, BOOL retain);
// Code part
void DICNT_body__(DICNT *data__);
// FUNCTION_BLOCK DIENC
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,DIN)
  __DECLARE_VAR(DWORD,REFA)
  __DECLARE_VAR(BOOL,REFAEN)
  __DECLARE_VAR(DWORD,REFB)
  __DECLARE_VAR(BOOL,REFBEN)
  __DECLARE_VAR(WORD,REFT)
  __DECLARE_VAR(BOOL,REFTEN)
  __DECLARE_VAR(DWORD,OA)
  __DECLARE_VAR(BOOL,OAREF)
  __DECLARE_VAR(DWORD,OB)
  __DECLARE_VAR(BOOL,OBREF)
  __DECLARE_VAR(WORD,OT)
  __DECLARE_VAR(BOOL,OTREF)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} DIENC;

void DIENC_init__(DIENC *data__, BOOL retain);
// Code part
void DIENC_body__(DIENC *data__);
// FUNCTION_BLOCK DIVAL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,DIN)
  __DECLARE_VAR(BOOL,OV)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} DIVAL;

void DIVAL_init__(DIVAL *data__, BOOL retain);
// Code part
void DIVAL_body__(DIVAL *data__);
// FUNCTION_BLOCK DICNTRST
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,DIN)
  __DECLARE_VAR(BOOL,RST)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} DICNTRST;

void DICNTRST_init__(DICNTRST *data__, BOOL retain);
// Code part
void DICNTRST_body__(DICNTRST *data__);
// FUNCTION_BLOCK DIMODE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,DIN)
  __DECLARE_VAR(BYTE,M)
  __DECLARE_VAR(BYTE,OM)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} DIMODE;

void DIMODE_init__(DIMODE *data__, BOOL retain);
// Code part
void DIMODE_body__(DIMODE *data__);
// FUNCTION_BLOCK DOPWM
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BOOL,ENX)
  __DECLARE_VAR(BYTE,DON)
  __DECLARE_VAR(DWORD,TM)
  __DECLARE_VAR(REAL,DU)
  __DECLARE_VAR(BOOL,OW)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} DOPWM;

void DOPWM_init__(DOPWM *data__, BOOL retain);
// Code part
void DOPWM_body__(DOPWM *data__);
// FUNCTION_BLOCK DOSAFE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BOOL,ENX)
  __DECLARE_VAR(BYTE,DON)
  __DECLARE_VAR(BOOL,V)
  __DECLARE_VAR(BOOL,OV)
  __DECLARE_VAR(BOOL,OW)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} DOSAFE;

void DOSAFE_init__(DOSAFE *data__, BOOL retain);
// Code part
void DOSAFE_body__(DOSAFE *data__);
// FUNCTION_BLOCK DOMODE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,DON)
  __DECLARE_VAR(BYTE,M)
  __DECLARE_VAR(BYTE,OM)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} DOMODE;

void DOMODE_init__(DOMODE *data__, BOOL retain);
// Code part
void DOMODE_body__(DOMODE *data__);
// FUNCTION_BLOCK DOVAL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,DON)
  __DECLARE_VAR(BOOL,V)
  __DECLARE_VAR(BOOL,OV)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} DOVAL;

void DOVAL_init__(DOVAL *data__, BOOL retain);
// Code part
void DOVAL_body__(DOVAL *data__);
// FUNCTION_BLOCK DOFAST
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,DON)
  __DECLARE_VAR(BOOL,V)
  __DECLARE_VAR(BOOL,OV)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} DOFAST;

void DOFAST_init__(DOFAST *data__, BOOL retain);
// Code part
void DOFAST_body__(DOFAST *data__);
// FUNCTION_BLOCK AIMODE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,AIN)
  __DECLARE_VAR(BYTE,M)
  __DECLARE_VAR(BYTE,OM)
  __DECLARE_VAR(BYTE,OS)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} AIMODE;

void AIMODE_init__(AIMODE *data__, BOOL retain);
// Code part
void AIMODE_body__(AIMODE *data__);
// FUNCTION_BLOCK AIVAL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,AIN)
  __DECLARE_VAR(REAL,OV)
  __DECLARE_VAR(BYTE,OS)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} AIVAL;

void AIVAL_init__(AIVAL *data__, BOOL retain);
// Code part
void AIVAL_body__(AIVAL *data__);
// FUNCTION_BLOCK AOFAST
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,AON)
  __DECLARE_VAR(REAL,V)
  __DECLARE_VAR(REAL,OV)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} AOFAST;

void AOFAST_init__(AOFAST *data__, BOOL retain);
// Code part
void AOFAST_body__(AOFAST *data__);
// FUNCTION_BLOCK AOMODE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,AON)
  __DECLARE_VAR(BYTE,M)
  __DECLARE_VAR(BYTE,OM)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} AOMODE;

void AOMODE_init__(AOMODE *data__, BOOL retain);
// Code part
void AOMODE_body__(AOMODE *data__);
// FUNCTION_BLOCK AOVAL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BYTE,AON)
  __DECLARE_VAR(REAL,V)
  __DECLARE_VAR(REAL,OV)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} AOVAL;

void AOVAL_init__(AOVAL *data__, BOOL retain);
// Code part
void AOVAL_body__(AOVAL *data__);
// FUNCTION_BLOCK AOSAFE
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,EX)
  __DECLARE_VAR(BOOL,ENX)
  __DECLARE_VAR(BYTE,AON)
  __DECLARE_VAR(REAL,V)
  __DECLARE_VAR(REAL,OV)
  __DECLARE_VAR(BOOL,OW)
  __DECLARE_VAR(BYTE,OK)

  // FB private variables - TEMP, private and located variables

} AOSAFE;

void AOSAFE_init__(AOSAFE *data__, BOOL retain);
// Code part
void AOSAFE_body__(AOSAFE *data__);
// PROGRAM MAIN
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(BOOL,LT_LOW)
  __DECLARE_VAR(BOOL,LT_LOW_F)
  __DECLARE_EXTERNAL(BOOL,LT_MIDDLE)
  __DECLARE_VAR(BOOL,LT_MIDDLE_F)
  __DECLARE_EXTERNAL(BOOL,LT_HIGHT)
  __DECLARE_VAR(BOOL,LT_HIGHT_F)
  __DECLARE_EXTERNAL(BOOL,HS_AUTO)
  __DECLARE_VAR(BOOL,HS_AUTO_F)
  __DECLARE_EXTERNAL(BOOL,P_SPEED_50)
  __DECLARE_VAR(BOOL,P_SPEED_50L)
  __DECLARE_EXTERNAL(BOOL,P_SPEED_100)
  __DECLARE_VAR(BOOL,P_SPEED_100L)
  __DECLARE_EXTERNAL(BOOL,P_START)
  __DECLARE_VAR(BOOL,P_STARTL)
  __DECLARE_EXTERNAL(BOOL,LT_ERROR)
  __DECLARE_VAR(BOOL,LT_ERRORL)
  __DECLARE_EXTERNAL(BOOL,LT_SET)
  __DECLARE_EXTERNAL(WORD,PLC_STATE)
  TON TON0;
  __DECLARE_VAR(TIME,TM_5S)
  TON TON1;
  TON TON2;
  TON TON3;
  __DECLARE_VAR(BOOL,NOT95_OUT)
  __DECLARE_VAR(BOOL,OR68_OUT)
  __DECLARE_VAR(BOOL,OR58_OUT)
  __DECLARE_VAR(BOOL,OR80_OUT)
  __DECLARE_VAR(INT,WORD_TO_INT93_OUT)
  __DECLARE_VAR(INT,INC91_OUT)
  __DECLARE_VAR(WORD,INT_TO_WORD94_OUT)

} MAIN;

void MAIN_init__(MAIN *data__, BOOL retain);
// Code part
void MAIN_body__(MAIN *data__);
#endif //__POUS_H
