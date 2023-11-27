/* @page app-ao.c
 *       Application functions / AO
 *       2020-2022
 */

#include "app-ao.h"


void PlcApp_AOMode(BOOL *Ex, BYTE *AOn, BYTE *M, BYTE *Om, BYTE *Ok)
{
    if(Ex && AOn && M && Om && Ok)
    {
        if(*Ex)
        {
            if(*AOn < PLC_AO_SZ)
            {
                if(*M <= PLC_AO_MODE_FAST || *M == PLC_AO_MODE_OFF)
                {
                   //LOCK
                    xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                    REG_CopyRegByPos((REG_AO_MODE__POS+(*AOn)), REG_COPY_VAR_TO_MB, M);
                    REG_CopyRegByPos((REG_AO_MODE_RES__POS+(*AOn)), REG_COPY_MB_TO_VAR, Om);

                    xSemaphoreGive(RTOS_MTX_MbTables);
                    //UNLOCK

                    *Ok = PLC_APP_AO_OK;
                }
                else
                {
                    *Ok = PLC_APP_AO_ERR_M;
                }
            }
            else
            {
                *Ok = PLC_APP_AO_ERR_AON;
            }
        }
    }
}


void PlcApp_AOVal(BOOL *Ex, BYTE *AOn, REAL *V, REAL *Ov, BYTE *Ok)
{
    if(Ex && AOn && V && Ov && Ok)
    {
        if(*Ex)
        {
            if(*AOn < PLC_AO_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                uint8_t M;
                REG_CopyRegByPos((REG_AO_MODE__POS+(*AOn)), REG_COPY_MB_TO_VAR, &M);

                if(M == PLC_AO_MODE_NORM)
                {
                    //Postponed value
                    PlcAO_Set_t QueueData_Set;
                    QueueData_Set.ChNum  = (*AOn);
                    QueueData_Set.SetID  = PLC_AO_SET_POSTPONED_VAL;
                    QueueData_Set.SetVal = (*V);
                    //Write Queue (not-blocking)
                    xQueueSendToBack(RTOS_Q_AoSet, &QueueData_Set, 0);
                    PLC_AO_POSTPONED = BIT_TRUE;

                    REG_CopyRegByPos((REG_AO_NORM_VAL__POS+(*AOn)), REG_COPY_VAR_TO_MB__NO_MON, V);

                    *Ov = *V;
                    *Ok = PLC_APP_AO_OK;
                }
                else
                {
                    *Ok = PLC_APP_AO_ERR_NOT_NORM;
                }

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK
            }
            else
            {
                *Ok = PLC_APP_AO_ERR_AON;
            }
        }
    }
}


void PlcApp_AOFast(BOOL *Ex, BYTE *AOn, REAL *V, REAL *Ov, BYTE *Ok)
{
    if(Ex && AOn && V && Ov && Ok)
    {
        if(*Ex)
        {
            if(*AOn < PLC_AO_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                uint8_t M;
                REG_CopyRegByPos((REG_AO_MODE__POS+(*AOn)), REG_COPY_MB_TO_VAR, &M);

                if(M == PLC_AO_MODE_FAST)
                {
                    REG_CopyRegByPos((REG_AO_FAST_VAL__POS+(*AOn)), REG_COPY_VAR_TO_MB, V);

                    *Ov = *V;
                    *Ok = PLC_APP_AO_OK;
                }
                else
                {
                    *Ok = PLC_APP_AO_ERR_NOT_FAST;
                }

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK
            }
            else
            {
                *Ok = PLC_APP_AO_ERR_AON;
            }
        }
    }
}


void PlcApp_AOSafe(BOOL *Ex, BOOL *En, BYTE *AOn, REAL *V, REAL *Ov, BOOL *Ow, BYTE *Ok)
{
    if(Ex && En && AOn && V && Ov && Ow && Ok)
    {
        if(*Ex)
        {
            if(*AOn < PLC_AO_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                REG_CopyRegByPos((REG_AO_SAFE_ALLOW__POS+(*AOn)), REG_COPY_VAR_TO_MB, En);
                REG_CopyRegByPos((REG_AO_SAFE_VAL__POS+(*AOn)), REG_COPY_VAR_TO_MB, V);

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK

                *Ov = *V;
                *Ow = *En;
                *Ok = PLC_APP_AO_OK;
            }
            else
            {
                *Ok = PLC_APP_AO_ERR_AON;
            }
        }
    }
}
