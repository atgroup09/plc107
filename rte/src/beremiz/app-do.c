/* @page app-do.c
 *       Application functions / DO
 *       2020-2022
 */

#include "app-do.h"


void PlcApp_DOMode(BOOL *Ex, BYTE *DOn, BYTE *M, BYTE *Om, BYTE *Ok)
{
    if(Ex && DOn && M && Om && Ok)
    {
        if(*Ex)
        {
            if(*DOn < PLC_DO_SZ)
            {
                if(*M <= PLC_DO_MODE_OFF)
                {
                    //LOCK
                    xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                    if(REG_CopyRegByPos((REG_DO_MODE__POS+(*DOn)), REG_COPY_VAR_TO_MB, M))
                    {
                        *Om = *M;
                    }

                    xSemaphoreGive(RTOS_MTX_MbTables);
                    //UNLOCK

                    *Om = *M;
                    *Ok = PLC_APP_DO_OK;
                }
                else
                {
                    *Ok = PLC_APP_DO_ERR_M;
                }
            }
            else
            {
                *Ok = PLC_APP_DO_ERR_DON;
            }
        }
    }
}


void PlcApp_DOVal(BOOL *Ex, BYTE *DOn, BOOL *V, BOOL *Ov, BYTE *Ok)
{
    if(Ex && DOn && V && Ov && Ok)
    {
        if(*Ex)
        {
            if(*DOn < PLC_DO_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                uint8_t M;
                REG_CopyRegByPos((REG_DO_MODE__POS+(*DOn)), REG_COPY_MB_TO_VAR, &M);

                if(M == PLC_DO_MODE_NORM)
                {
                    //Postponed value
                    PlcDO_Set_t QueueData_Set;
                    QueueData_Set.ChNum  = (*DOn);
                    QueueData_Set.SetID  = PLC_DO_SET_POSTPONED_VAL;
                    QueueData_Set.SetVal = (float)(*V);
                    //Write Queue (not-blocking)
                    xQueueSendToBack(RTOS_Q_DoSet, &QueueData_Set, 0);
                    PLC_DO_POSTPONED = BIT_TRUE;

                    REG_CopyRegByPos((REG_DO_NORM_VAL__POS+(*DOn)), REG_COPY_VAR_TO_MB__NO_MON, V);

                    *Ov = *V;
                    *Ok = PLC_APP_DO_OK;
                }
                else
                {
                    *Ok = PLC_APP_DO_ERR_NOT_NORM;
                }

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK
            }
            else
            {
                *Ok = PLC_APP_DO_ERR_DON;
            }
        }
    }
}


void PlcApp_DOFast(BOOL *Ex, BYTE *DOn, BOOL *V, BOOL *Ov, BYTE *Ok)
{
    if(Ex && DOn && V && Ov && Ok)
    {
        if(*Ex)
        {
            if(*DOn < PLC_DO_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                uint8_t M;
                REG_CopyRegByPos((REG_DO_MODE__POS+(*DOn)), REG_COPY_MB_TO_VAR, &M);

                if(M == PLC_DO_MODE_FAST)
                {
                    REG_CopyRegByPos((REG_DO_FAST_VAL__POS+(*DOn)), REG_COPY_VAR_TO_MB, V);

                    *Ov = *V;
                    *Ok = PLC_APP_DO_OK;
                }
                else
                {
                    *Ok = PLC_APP_DO_ERR_NOT_FAST;
                }

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK
            }
            else
            {
                *Ok = PLC_APP_DO_ERR_DON;
            }
        }
    }
}


void PlcApp_DOPwm(BOOL *Ex, BOOL *En, BYTE *DOn, DWORD *Tm, REAL *D, BOOL *Ow, BYTE *Ok)
{
    if(Ex && En && DOn && Tm && D && Ow && Ok)
    {
        if(*Ex)
        {
            if(*DOn < PLC_DO_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                uint8_t M;
                REG_CopyRegByPos((REG_DO_MODE__POS+(*DOn)), REG_COPY_MB_TO_VAR, &M);

                if(M == PLC_DO_MODE_PWM)
                {
                    if(REG_CopyRegByPos((REG_DO_PWM_ALLOW__POS+(*DOn)), REG_COPY_VAR_TO_MB, En))
                    {
                        *Ow = *En;
                    }

                    REG_CopyRegByPos((REG_DO_PWM_PERIOD__POS+(*DOn)), REG_COPY_VAR_TO_MB, Tm);
                    REG_CopyRegByPos((REG_DO_PWM_VAL__POS+(*DOn)), REG_COPY_VAR_TO_MB, D);

                    *Ok = PLC_APP_DO_OK;
                }
                else
                {
                    *Ok = PLC_APP_DO_ERR_NOT_PWM;
                }

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK
            }
            else
            {
                *Ok = PLC_APP_DO_ERR_DON;
            }
        }
    }
}


void PlcApp_DOSafe(BOOL *Ex, BOOL *En, BYTE *DOn, BOOL *V, BOOL *Ov, BOOL *Ow, BYTE *Ok)
{
    if(Ex && En && DOn && V && Ov && Ow && Ok)
    {
        if(*Ex)
        {
            if(*DOn < PLC_DO_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                REG_CopyRegByPos((REG_DO_SAFE_ALLOW__POS+(*DOn)), REG_COPY_VAR_TO_MB, En);
                REG_CopyRegByPos((REG_DO_SAFE_VAL__POS+(*DOn)), REG_COPY_VAR_TO_MB, V);

                *Ov = *V;
                *Ow = *En;
                *Ok = PLC_APP_DO_OK;

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK
            }
            else
            {
                *Ok = PLC_APP_DO_ERR_DON;
            }
        }
    }
}
