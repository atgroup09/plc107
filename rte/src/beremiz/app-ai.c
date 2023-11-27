/* @page app-ai.c
 *       Application functions / AI
 *       2020-2022
 */

#include "app-ai.h"


void PlcApp_AIMode(BOOL *Ex, BYTE *AIn, BYTE *M, BYTE *Om, BYTE *Os, BYTE *Ok)
{
    if(Ex && AIn && M && Om && Os && Ok)
    {
        if(*Ex)
        {
            if(*AIn < PLC_AI_SZ)
            {
                if(*M == PLC_AI_MODE_SURVEY || *M == PLC_AI_MODE_OFF)
                {
                    //LOCK
                    xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                    //set new values
                    REG_CopyRegByPos((REG_AI_MODE__POS+(*AIn)), REG_COPY_VAR_TO_MB, M);

                    //read current values
                    REG_CopyRegByPos((REG_AI_MODE_RES__POS+(*AIn)), REG_COPY_MB_TO_VAR, Om);
                    REG_CopyRegByPos((REG_AI_STATUS__POS+(*AIn)), REG_COPY_MB_TO_VAR, Os);

                    xSemaphoreGive(RTOS_MTX_MbTables);
                    //UNLOCK

                    *Ok  = PLC_APP_AI_OK;
                }
                else
                {
                    *Ok = PLC_APP_AI_ERR_M;
                }
            }
            else
            {
                *Ok = PLC_APP_AI_ERR_CHN;
            }
        }
    }
}


void PlcApp_AIVal(BOOL *Ex, BYTE *AIn, REAL *Ov, BYTE *Os, BYTE *Ok)
{
    if(Ex && AIn && Ov && Os && Ok)
    {
        if(*Ex)
        {
            if(*AIn < PLC_AI_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);

                //read current values
                REG_CopyRegByPos((REG_AI_VAL__POS+(*AIn)), REG_COPY_MB_TO_VAR, Ov);
                REG_CopyRegByPos((REG_AI_STATUS__POS+(*AIn)), REG_COPY_MB_TO_VAR, Os);

                xSemaphoreGive(RTOS_MTX_MbTables);
                //UNLOCK

                *Ok  = PLC_APP_AI_OK;
            }
            else
            {
                *Ok = PLC_APP_AI_ERR_CHN;
            }
        }
    }
}
