/* @page app-di.c
 *       Application functions / DI
 *       2020-2022
 */

#include "app-di.h"


void PlcApp_DIMode(BOOL *Ex, BYTE *DIn, BYTE *M, BYTE *Om, BYTE *Ok)
{
    if(Ex && DIn && M && Om && Ok)
    {
        if(*Ex)
        {
            if(*DIn < PLC_DI_SZ && !(PLC_DI_IS_PHASE_B(*DIn) && *M > PLC_DI_MODE_TACH))
            {
                if(!(PLC_DI_IS_PHASE_B(*DIn) && *M > PLC_DI_MODE_TACH))
                {
                    if(*M <= PLC_DI_MODE_INC2)
                    {
                        //LOCK
                        xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                        if(REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_VAR_TO_MB, M))
                        {
                            *Om = *M;
                        }

                        xSemaphoreGive(RTOS_MTX_MbTables);
                        //UNLOCK

                        *Ok = PLC_APP_DI_OK;
                    }
                    else
                    {
                        *Ok = PLC_APP_DI_ERR_M;
                    }
                }
                else
                {
                    *Ok = PLC_APP_DI_ERR_INC;
                }
            }
            else
            {
                *Ok = PLC_APP_DI_ERR_DIN;
            }
        }
    }
}


void PlcApp_DIVal(BOOL *Ex, BYTE *DIn, BOOL *Ov, BYTE *Ok)
{
    if(Ex && DIn && Ov && Ok)
    {
        if(*Ex)
        {
            if(*DIn < PLC_DI_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                uint8_t M;
                REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_MB_TO_VAR, &M);

                if(M == PLC_DI_MODE_NORM)
                {
                    REG_CopyRegByPos((REG_DI_NORM_VAL__POS+(*DIn)), REG_COPY_MB_TO_VAR, Ov);
                    *Ok = PLC_APP_DI_OK;
                }
                else
                {
                    *Ok = PLC_APP_DI_ERR_NOT_NORM;
                }

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK
            }
            else
            {
                *Ok = PLC_APP_DI_ERR_DIN;
            }
        }
    }
}


void PlcApp_DICntT(BOOL *Ex, BYTE *DIn, WORD *Ref, BOOL *RefEn, WORD *Ov, BOOL *Oref, BYTE *Ok)
{
    if(Ex && DIn && Ref && RefEn && Ov && Oref && Ok)
    {
        if(*Ex)
        {
            if(*DIn < PLC_DI_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                uint8_t M;
                REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_MB_TO_VAR, &M);

                if(M == PLC_DI_MODE_TACH)
                {
                    REG_CopyRegByPos((REG_DI_TACH_SETPOINT__POS+(*DIn)), REG_COPY_VAR_TO_MB, Ref);
                    REG_CopyRegByPos((REG_DI_TACH_SETPOINT_ALLOW__POS+(*DIn)), REG_COPY_VAR_TO_MB, RefEn);
                    REG_CopyRegByPos((REG_DI_TACH_VAL__POS+(*DIn)), REG_COPY_MB_TO_VAR, Ov);
                    REG_CopyRegByPos((REG_DI_TACH_SETPOINT_RES__POS+(*DIn)), REG_COPY_MB_TO_VAR, Oref);
                    *Ok = PLC_APP_DI_OK;
                }
                else
                {
                    *Ok = PLC_APP_DI_ERR_NOT_TACH;
                }

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK
            }
            else
            {
                *Ok = PLC_APP_DI_ERR_DIN;
            }
        }
    }
}


void PlcApp_DICnt(BOOL *Ex, BYTE *DIn, DWORD *Ref, BOOL *RefEn, DWORD *Ov, BOOL *Oref, BYTE *Ok)
{
    if(Ex && DIn && Ref && RefEn && Ov && Oref && Ok)
    {
        if(*Ex)
        {
            if(*DIn < PLC_DI_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                uint8_t M;
                REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_MB_TO_VAR, &M);

                if(M == PLC_DI_MODE_CNTR)
                {
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT__POS+(*DIn)), REG_COPY_VAR_TO_MB, Ref);
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_ALLOW__POS+(*DIn)), REG_COPY_VAR_TO_MB, RefEn);
                    REG_CopyRegByPos((REG_DI_CNTR_VAL__POS+(*DIn)), REG_COPY_MB_TO_VAR, Ov);
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_RES__POS+(*DIn)), REG_COPY_MB_TO_VAR, Oref);
                    *Ok = PLC_APP_DI_OK;
                }
                else
                {
                    *Ok = PLC_APP_DI_ERR_NOT_CNTR;
                }

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK
            }
            else
            {
                *Ok = PLC_APP_DI_ERR_DIN;
            }
        }
    }
}


void PlcApp_DICntRst(BOOL *Ex, BYTE *DIn, BOOL *Rst, BYTE *Ok)
{
    if(Ex && DIn && Rst && Ok)
    {
        if(*Ex)
        {
            if(*DIn < PLC_DI_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                uint8_t M;
                REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_MB_TO_VAR, &M);

                if(M == PLC_DI_MODE_CNTR || M == PLC_DI_MODE_TACH || M == PLC_DI_MODE_INC1 || M == PLC_DI_MODE_INC2)
                {
                    REG_CopyRegByPos((REG_DI_RESET__POS+(*DIn)), REG_COPY_VAR_TO_MB, Rst);
                    *Ok = PLC_APP_DI_OK;
                }
                else
                {
                    *Ok = PLC_APP_DI_ERR_NOT_CNTR;
                }

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK
            }
            else
            {
                *Ok = PLC_APP_DI_ERR_DIN;
            }
        }
    }
}


void PlcApp_DIEnc(BOOL *Ex, BYTE *DIn, DWORD *RefA, BOOL *RefAEn, DWORD *RefB, BOOL *RefBEn, WORD *RefT, BOOL *RefTEn, DWORD *OutA, BOOL *OAref, DWORD *OutB, BOOL *OBref, WORD *OutT, BOOL *OTref, BYTE *Ok)
{
    if(Ex && DIn && RefA && RefAEn && RefB && RefBEn && RefT && RefTEn && OutA && OAref && OutB && OBref && OutT && OTref && Ok)
    {
        if(*Ex)
        {
            if(PLC_DI_IS_PHASE_A(*DIn))
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                uint8_t M;
                REG_CopyRegByPos((REG_DI_MODE__POS+(*DIn)), REG_COPY_MB_TO_VAR, &M);

                if(M > PLC_DI_MODE_TACH)
                {
                    uint16_t ChB = ((*DIn)+1);
                    // phase A counter
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT__POS+(*DIn)), REG_COPY_VAR_TO_MB, RefA);
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_ALLOW__POS+(*DIn)), REG_COPY_VAR_TO_MB, RefAEn);
                    REG_CopyRegByPos((REG_DI_CNTR_VAL__POS+(*DIn)), REG_COPY_MB_TO_VAR, OutA);
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_RES__POS+(*DIn)), REG_COPY_MB_TO_VAR, OAref);
                    // phase B counter
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT__POS+ChB), REG_COPY_VAR_TO_MB, RefB);
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_ALLOW__POS+ChB), REG_COPY_VAR_TO_MB, RefBEn);
                    REG_CopyRegByPos((REG_DI_CNTR_VAL__POS+ChB), REG_COPY_MB_TO_VAR, OutB);
                    REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_RES__POS+ChB), REG_COPY_MB_TO_VAR, OBref);
                    // phase B tachometer
                    REG_CopyRegByPos((REG_DI_TACH_SETPOINT__POS+ChB), REG_COPY_VAR_TO_MB, RefT);
                    REG_CopyRegByPos((REG_DI_TACH_SETPOINT_ALLOW__POS+ChB), REG_COPY_VAR_TO_MB, RefTEn);
                    REG_CopyRegByPos((REG_DI_TACH_VAL__POS+ChB), REG_COPY_MB_TO_VAR, OutT);
                    REG_CopyRegByPos((REG_DI_TACH_SETPOINT_RES__POS+ChB), REG_COPY_MB_TO_VAR, OTref);
                    *Ok = PLC_APP_DI_OK;
                }
                else
                {
                    *Ok = PLC_APP_DI_ERR_NOT_CNTR;
                }

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK
            }
            else
            {
                *Ok = PLC_APP_DI_ERR_DIN;
            }
        }
    }
}
