/* @page rtos-task-ao.h
 *       FreeRTOS Task
 *       Analog outputs
 *       2020-2022
 */

#include "rtos-task-ao.h"


/** @var AO channels
 */
static PlcAO_t PLC_AO[PLC_AO_SZ];


/** @brief  Set normal value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - normal value:
 *  @arg      = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetNormVal(const uint8_t ChNumIn, const float ValIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        PLC_AO[ChNumIn].Val = ValIn;

        if(PLC_AO[ChNumIn].Pack.Mode == PLC_AO_MODE_NORM)
        {
#ifdef DEBUG_LOG_AO
            DebugLog("AoSet: ch=%d norm_val*100=%d(%d) Ka*100=%d Kb*100=%d\n", ChNumIn, (uint32_t)PLC_AO[ChNumIn].Val*100.0, (uint32_t)PLC_AO[ChNumIn].Ka*100.0, (uint32_t)PLC_AO[ChNumIn].Kb*100.0);
#endif // DEBUG_LOG_AO

            return (PlcAO_SetAnaLv(PLC_AO[ChNumIn].Pack.ChNum, PLC_AO[ChNumIn].Val, PLC_AO[ChNumIn].Ka, PLC_AO[ChNumIn].Kb));
        }
        else if(PLC_AO[ChNumIn].Pack.Mode == PLC_AO_MODE_CALB)
        {
#ifdef DEBUG_LOG_AO
            DebugLog("AoSet: ch=%d norm_val*100=%d(%d) Ka*100=%d Kb*100=%d\n", ChNumIn, (uint32_t)PLC_AO[ChNumIn].Val*100.0, (uint32_t)PLC_AO_KA_DEF*100.0, (uint32_t)PLC_AO_KB_DEF*100.0);
#endif // DEBUG_LOG_AO

            return (PlcAO_SetAnaLv(PLC_AO[ChNumIn].Pack.ChNum, PLC_AO[ChNumIn].Val, PLC_AO_KA_DEF, PLC_AO_KB_DEF));
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set postponed value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - value:
 *  @arg      = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetPostponedVal(const uint8_t ChNumIn, const float ValIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        PLC_AO[ChNumIn].PostponedVal   = ValIn;
        PLC_AO[ChNumIn].Pack.Postponed = BIT_TRUE;

#ifdef DEBUG_LOG_AO
        if(PLC_AO[ChNumIn].PostponedVal != ValIn)
        {
            DebugLog("AoSet: ch=%d post_val=%d(%d)\n", ChNumIn, (uint32_t)PLC_AO[ChNumIn].PostponedVal, (uint32_t)ValIn);
        }
#endif // DEBUG_LOG_AO

        return (BIT_TRUE);
    }

    return (BIT_FALSE);
}


/** @brief  Set postponed value (apply all postponed valued).
 *  @param  ValIn - value:
 *  @arg      = 0 - not apply
 *  @arg      = 1 - apply
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetPostponedApply(const uint8_t ValIn)
{
    if(ValIn)
    {
        for(uint16_t i=0; i<PLC_AO_SZ; i++)
        {
            if(PLC_AO[i].Pack.Mode == PLC_AO_MODE_NORM && PLC_AO[i].Pack.Postponed)
            {
                if(PLC_AO[i].PostponedVal != PLC_AO[i].Val)
                {
#ifdef DEBUG_LOG_AO
                    DebugLog("AoSet: ch=%d POST-APPLY\n", i);
#endif // DEBUG_LOG_AO

                    RTOS_TaskAO_SetNormVal(i, PLC_AO[i].PostponedVal);
                    PLC_AO[i].Pack.Postponed = BIT_FALSE;
                }
            }
        }

        return (BIT_TRUE);
    }

    return (BIT_FALSE);
}


/** @brief  Set fast value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - fast value:
 *  @arg      = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetFastVal(const uint8_t ChNumIn, const float ValIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        PLC_AO[ChNumIn].FastVal = ValIn;

#ifdef DEBUG_LOG_AO
        DebugLog("AoSet: ch=%d fast_val=%d(%d)\n", ChNumIn, (uint32_t)PLC_AO[ChNumIn].FastVal, (uint32_t)ValIn);
#endif // DEBUG_LOG_AO

        if(PLC_AO[ChNumIn].Pack.Mode == PLC_AO_MODE_FAST)
        {
            return (PlcAO_SetAnaLv(PLC_AO[ChNumIn].Pack.ChNum, PLC_AO[ChNumIn].FastVal, PLC_AO[ChNumIn].Ka, PLC_AO[ChNumIn].Kb));
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set Mode.
 *  @param  ChNumIn - channel number.
 *  @param  ModeIn - Mode:
 *  @arg      = PLC_AO_MODE_NORM
 *  @arg      = PLC_AO_MODE_FAST
 *  @arg      = PLC_AO_MODE_CALB
 *  @arg      = PLC_AO_MODE_OFF
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetMode(const uint8_t ChNumIn, const uint8_t ModeIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        if(PLC_AO[ChNumIn].Pack.Mode != ModeIn && ModeIn <= PLC_AO_MODE_OFF)
        {
            PLC_AO[ChNumIn].Pack.Mode    = ModeIn;
            PLC_AO[ChNumIn].Pack.ModeRes = PLC_AO[ChNumIn].Pack.Mode;

#ifdef DEBUG_LOG_AO
            DebugLog("AoSet: ch=%d mode=%d(%d){%d}\n", ChNumIn, PLC_AO[ChNumIn].Pack.Mode, ModeIn, PLC_AO[ChNumIn].Pack.ModeRes);
#endif // DEBUG_LOG_AO

            switch(PLC_AO[ChNumIn].Pack.Mode)
            {
                case PLC_AO_MODE_NORM:
                    RTOS_TaskAO_SetNormVal(PLC_AO[ChNumIn].Pack.ChNum, PLC_AO[ChNumIn].Val);
                    break;

                case PLC_AO_MODE_FAST:
                    RTOS_TaskAO_SetFastVal(PLC_AO[ChNumIn].Pack.ChNum, PLC_AO[ChNumIn].FastVal);
                    break;

                /*
                case PLC_AO_MODE_CALB:
                    break;
                */

                case PLC_AO_MODE_OFF:
                    PlcAO_SetAnaLv(PLC_AO[ChNumIn].Pack.ChNum, PLC_AO_ANA_MIN, PLC_AO[ChNumIn].Ka, PLC_AO[ChNumIn].Kb);
                    break;
            }

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set Safe-mode allow.
 *  @param  ChNumIn - channel number.
 *  @param  AllowIn - allow:
 *  @arg      = 0 - not allowed
 *  @arg      = 1 - allowed
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetSafeAllow(const uint8_t ChNumIn, const uint8_t AllowIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        uint8_t Allow = ((AllowIn) ? BIT_TRUE : BIT_FALSE);

        if(PLC_AO[ChNumIn].Pack.SafeAllow != Allow)
        {
            PLC_AO[ChNumIn].Pack.SafeAllow = Allow;

#ifdef DEBUG_LOG_AO
            DebugLog("AoSet: ch=%d safe_allow=%d(%d)\n", ChNumIn, PLC_AO[ChNumIn].Pack.SafeAllow, AllowIn);
#endif // DEBUG_LOG_AO

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set Safe-mode value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - value:
 *  @arg      = PLC_AO_ANA_MIN .. PLC_AO_ANA_MAX
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetSafeVal(const uint8_t ChNumIn, const float ValIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        PLC_AO[ChNumIn].SafeVal = ValIn;

#ifdef DEBUG_LOG_AO
        DebugLog("AoSet: ch=%d safe_val=%d(%d)\n", ChNumIn, (uint32_t)PLC_AO[ChNumIn].SafeVal, (uint32_t)ValIn);
#endif // DEBUG_LOG_AO

        return (BIT_TRUE);
    }

    return (BIT_FALSE);
}


/** @brief  Set calibrated Lo- or Hi-level (V).
 *  @param  ChNumIn - channel number.
 *  @param  CalbValIn - calibrated level.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetCalbVal(const uint8_t ChNumIn, const float CalbValIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        PLC_AO[ChNumIn].I = CalbValIn;

#ifdef DEBUG_LOG_AO
        DebugLog("AoSetCalbVal: ChNum=%d CalbVal*100=%d [SET]\n", ChNumIn, (uint32_t)CalbValIn*100.0);
#endif // DEBUG_LOG_AO

        return (BIT_TRUE);
    }

    return (BIT_FALSE);
}


/** @brief  Set calibrated Lo-level (V) and current ADC-code.
 *  @param  ChNumIn - channel number.
 *  @param  CmdIn   - command (0, 1).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetCalbLoCmd(const uint8_t ChNumIn, const uint8_t CmdIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        if(CmdIn && PLC_AO[ChNumIn].Pack.Mode == PLC_AO_MODE_CALB)
        {
            PLC_AO[ChNumIn].I1 = PLC_AO[ChNumIn].I;

#ifdef DEBUG_LOG_AO
            DebugLog("AoSetCalbLoCmd: ChNum=%d Cmd=%d Y1=%d I1=%d [SET]\n", ChNumIn, CmdIn, PLC_AO_DIG_MIN, (uint32_t)PLC_AO[ChNumIn].I1);
#endif // DEBUG_LOG_AO

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set calibrated Hi-level (V) and current ADC-code.
 *  @param  ChNumIn - channel number.
 *  @param  CmdIn   - command (0, 1).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetCalbHiCmd(const uint8_t ChNumIn, const uint8_t CmdIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        if(CmdIn && PLC_AO[ChNumIn].Pack.Mode == PLC_AO_MODE_CALB)
        {
            PLC_AO[ChNumIn].I2 = PLC_AO[ChNumIn].I;

#ifdef DEBUG_LOG_AO
            DebugLog("AoSetCalbHiCmd: ChNum=%d Cmd=%d Y2=%d I2=%d [SET]\n", ChNumIn, CmdIn, PLC_AO_DIG_MAX, (uint32_t)PLC_AO[ChNumIn].I2);
#endif // DEBUG_LOG_AO

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set calibrated factors.
 *  @param  ChNumIn - channel number.
 *  @param  CmdIn   - command (0, 1).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_SetCalbCmd(const uint8_t ChNumIn, const uint8_t CmdIn)
{
    if(ChNumIn < PLC_AO_SZ)
    {
        if(CmdIn && PLC_AO[ChNumIn].Pack.Mode == PLC_AO_MODE_CALB)
        {
            PLC_AO[ChNumIn].Ka = ScaleA_Ka((float)PLC_AO_DIG_MIN, (float)PLC_AO_DIG_MAX, PLC_AO[ChNumIn].I1, PLC_AO[ChNumIn].I2);
            PLC_AO[ChNumIn].Kb = ScaleA_Kb((float)PLC_AO_DIG_MIN, (float)PLC_AO_DIG_MAX, PLC_AO[ChNumIn].I1, PLC_AO[ChNumIn].I2);

#ifdef DEBUG_LOG_AO
            DebugLog("AoSetCalbCmd: ChNum=%d Cmd=%d Ka*100=%d Kb*100=%d [SET]\n", ChNumIn, CmdIn, (uint32_t)PLC_AO[ChNumIn].Ka*100.0, (uint32_t)PLC_AO[ChNumIn].Kb*100.0);
#endif // DEBUG_LOG_AO

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}


/** @brief  Unpack settings.
 *  @param  DataIn - pointer to settings.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAO_Set(const PlcAO_Set_t *DataIn)
{
    uint8_t Res = BIT_FALSE;
    PlcAO_Set_t SetRes;

    if(DataIn)
    {
        switch(DataIn->SetID)
        {
            //AO.Postponed
            case PLC_AO_SET_POSTPONED_VAL:
                Res = RTOS_TaskAO_SetPostponedVal(DataIn->ChNum, DataIn->SetVal);
                (void)SetRes;
                break;

            //AO.PostponedAllow
            case PLC_AO_SET_POSTPONED_APPLY:
                Res = RTOS_TaskAO_SetPostponedApply((uint8_t)DataIn->SetVal);
                (void)SetRes;
                break;

            //AO.NormVal
            case PLC_AO_SET_NORM_VAL:
                Res = RTOS_TaskAO_SetNormVal(DataIn->ChNum, DataIn->SetVal);
                (void)SetRes;
                break;

            //AO.FastVal
            case PLC_AO_SET_FAST_VAL:
                Res = RTOS_TaskAO_SetFastVal(DataIn->ChNum, DataIn->SetVal);
                (void)SetRes;
                break;

            //AO.Mode
            case PLC_AO_SET_MODE:
                Res = RTOS_TaskAO_SetMode(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                if(Res)
                {
                    SetRes.SetID  = PLC_AO_SET_MODE_RES;
                    SetRes.SetVal = DataIn->SetVal;
                }
                break;

            //AO.SafeAllow
            case PLC_AO_SET_SAFE_ALLOW:
                Res = RTOS_TaskAO_SetSafeAllow(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                break;

            //AO.SafeVal
            case PLC_AO_SET_SAFE_VAL:
                Res = RTOS_TaskAO_SetSafeVal(DataIn->ChNum, DataIn->SetVal);
                break;

            //AO.CalbVal (Lo- or Hi-level)
            case PLC_AO_SET_CALB_VAL:
                Res = RTOS_TaskAO_SetCalbVal(DataIn->ChNum, DataIn->SetVal);
                (void)SetRes;
                break;

            //AO.CalbLoCmd (command to fix. Lo-level and ADC-code)
            case PLC_AO_SET_CALB_LO_CMD:
                Res = RTOS_TaskAO_SetCalbLoCmd(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                (void)SetRes;
                break;

            //AO.CalbHiCmd (command to fix. Hi-level and ADC-code)
            case PLC_AO_SET_CALB_HI_CMD:
                Res = RTOS_TaskAO_SetCalbHiCmd(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                (void)SetRes;
                break;

            //CalbCmd (command to calculate calibration factors)
            case PLC_AO_SET_CALB_CMD:
                Res = RTOS_TaskAO_SetCalbCmd(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                (void)SetRes;
                break;
        }

        if(Res)
        {
            if(DataIn->SetID == PLC_AO_SET_MODE)
            {
                SetRes.ChNum = DataIn->ChNum;

                //Write Queue (not-blocking)
                //send updated channel data
                xQueueSendToBack(RTOS_Q_DataAo, &SetRes, 0);
            }
        }
    }

    return (Res);
}


/** @brief  Init. AO-channels.
 *  @param  none.
 *  @return none.
 */
void RTOS_TaskAO_Init(void)
{
    uint8_t BuffBy;
    float   BuffFlo;

#ifdef DEBUG_LOG_AO
    DebugLog("AoInit\n");
#endif // DEBUG_LOG_AO

    for(uint16_t i=0; i<PLC_AO_SZ; i++)
    {
        PLC_AO[i].Pack.ChNum = i;

        //read from REG_t (retain)
        BuffBy = PLC_AO_MODE_DEF;
        REG_CopyRegByPos(REG_AO_MODE__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
        PLC_AO[i].Pack.Mode = BuffBy;

        PLC_AO[i].Pack.ModeRes = PLC_AO[i].Pack.Mode;
        PLC_AO[i].Pack.Postponed = BIT_FALSE;

        //read from REG_t (retain)
        BuffBy = PLC_AO_SAFE_ALLOW_DEF;
        REG_CopyRegByPos(REG_AO_SAFE_ALLOW__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
        PLC_AO[i].Pack.SafeAllow = BuffBy;

        //read from REG_t (retain)
        BuffFlo = PLC_AO_SAFE_VAL_DEF;
        REG_CopyRegByPos(REG_AO_SAFE_VAL__POS+i, REG_COPY_MB_TO_VAR, &BuffFlo);
        PLC_AO[i].SafeVal = BuffFlo;

        PLC_AO[i].Val          = PLC_AO_ANA_DEF;
        PLC_AO[i].FastVal      = PLC_AO_ANA_MIN;
        PLC_AO[i].PostponedVal = PLC_AO_ANA_MIN;
        PLC_AO[i].I            = PLC_AO_ANA_MIN;
        PLC_AO[i].I1           = PLC_AO_ANA_MIN;
        PLC_AO[i].I2           = PLC_AO_ANA_MAX;
        PLC_AO[i].Ka           = PLC_AO_KA_DEF;
        PLC_AO[i].Kb           = PLC_AO_KB_DEF;

        //set value by default
        PlcAO_SetAnaLv(PLC_AO[i].Pack.ChNum, PLC_AO[i].Val, PLC_AO[i].Ka, PLC_AO[i].Kb);

#ifdef DEBUG_LOG_AO
        DebugLog("Ao[%d]: Mode=%d SafeAllow=%d SafeVal=%d Ka=%d Kb=%d\n", i, PLC_AO[i].Pack.Mode, PLC_AO[i].Pack.SafeAllow, (uint32_t)PLC_AO[i].SafeVal, (uint32_t)(PLC_AO[i].Ka*1000000.0), (uint32_t)(PLC_AO[i].Kb*1000000.0));
#endif // DEBUG_LOG_AO
    }
}


/** @brief  Task `AO`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskAO(void *ParamsIn)
{
    //VARIABLES
    PlcAO_Set_t QueueData_Set;
    BaseType_t  QueueStatus;

    //INIT
    (void)ParamsIn; //fix unused

    //START
    for(;;)
    {
        //Read Queue (blocking)
        //get updated settings
        QueueStatus = xQueueReceive(RTOS_Q_AoSet, &QueueData_Set, portMAX_DELAY);
        if(QueueStatus == pdPASS)
        {
            //unpack settings
            RTOS_TaskAO_Set(&QueueData_Set);
        }

        //fast switch to other task
        taskYIELD();
    }
}
