/* @page rtos-task-do.h
 *       FreeRTOS Task
 *       Discrete outputs
 *       2020-2022
 */

#include "rtos-task-do.h"


/** @var DO channels
 */
static PlcDO_t PLC_DO[PLC_DO_SZ];


/** @var DO PWM
 */
static PlcDO_PWM_t PLC_DO_PWM[PLC_DO_SZ];


/** @var DO pins
 */
static PlcDO_Pin_t PLC_DO_PINS[PLC_DO_SZ] =
{
    {
        .Port    = PLC_DO_00__PORT,
        .Pin     = PLC_DO_00__PIN,
        .PinMode = PLC_DO_00__PIN_MODE
    },
    {
        .Port    = PLC_DO_01__PORT,
        .Pin     = PLC_DO_01__PIN,
        .PinMode = PLC_DO_01__PIN_MODE
    },
    {
        .Port    = PLC_DO_02__PORT,
        .Pin     = PLC_DO_02__PIN,
        .PinMode = PLC_DO_02__PIN_MODE
    },
    {
        .Port    = PLC_DO_03__PORT,
        .Pin     = PLC_DO_03__PIN,
        .PinMode = PLC_DO_03__PIN_MODE
    }
};


/** @brief  Calc PWM length of TRUE-value.
 *  @param  PeriodIn     - period (ms).
 *  @param  FillFactorIn - fill factor (%).
 *  @return Length of TRUE-value (us).
 *  @note
 *          Len1 = ((PeriodIn*1000)/100)*FillFactorIn
 */
uint64_t RTOS_TaskDO_CalcPwmLen1(const uint32_t PeriodIn, const float FillFactorIn)
{
    float PeriodUs = ((float)PeriodIn)*((float)1000.0);
    uint64_t Len   = (uint64_t)((PeriodUs/((float)100.0))*FillFactorIn);
    return ((Len >= PLC_DO_PWM_LEN__MIN) ? Len : 0);
}


/** @brief  Calc PWM length of FALSE-value.
 *  @param  PeriodIn - period (ms).
 *  @param  Len1In   - length of TRUE-value (us).
 *  @return Length of FALSE-value (us).
 *  @note
 *          Len0 = (PeriodIn*1000)-Len1In
 */
inline uint64_t RTOS_TaskDO_CalcPwmLen0(const uint32_t PeriodIn, const uint64_t Len1In)
{
    uint64_t PeriodUs = PeriodIn;
    uint64_t Len      = ((PeriodUs*1000)-Len1In);
    return ((Len >= PLC_DO_PWM_LEN__MIN) ? Len : 0);
}


/** @brief  Refresh PWM.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_RefreshPwm(const uint8_t ChNumIn)
{
    if(ChNumIn < PLC_DO_SZ)
    {
        if(PLC_DO[ChNumIn].Pack.Mode == PLC_DO_MODE_PWM)
        {
            if(PLC_DO[ChNumIn].Pack.PwmAllow && PLC_DO[ChNumIn].PwmLen1)
            {
                PlcTim2_Start();
            }

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set output value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - value:
 *  @arg      = 0
 *  @arg      = 1
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetVal(const uint8_t ChNumIn, const uint8_t ValIn)
{
    if(ChNumIn < PLC_DO_SZ)
    {
#ifdef DEBUG_LOG_DO
        DebugLog("DoSetVal: ch=%d norm_val=%d(%d)\n", ChNumIn, PLC_DO[ChNumIn].Pack.Val, ValIn);
#endif // DEBUG_LOG_DO
        PlcDO_Set(PLC_DO[ChNumIn].Pin->Port, PLC_DO[ChNumIn].Pin->Pin, PLC_DO[ChNumIn].Pin->PinMode, ValIn);
        return (BIT_TRUE);
    }

    return (BIT_FALSE);
}


/** @brief  Set normal value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - value:
 *  @arg      = 0
 *  @arg      = 1
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetNormVal(const uint8_t ChNumIn, const uint8_t ValIn)
{
    if(ChNumIn < PLC_DO_SZ)
    {
        PLC_DO[ChNumIn].Pack.Val = ((ValIn) ? BIT_TRUE : BIT_FALSE);

        if(PLC_DO[ChNumIn].Pack.Mode == PLC_DO_MODE_NORM)
        {
#ifdef DEBUG_LOG_DO
            DebugLog("DoSet: ch=%d norm_val=%d(%d)\n", ChNumIn, PLC_DO[ChNumIn].Pack.Val, ValIn);
#endif // DEBUG_LOG_DO
            return (RTOS_TaskDO_SetVal(PLC_DO[ChNumIn].Pack.ChNum, PLC_DO[ChNumIn].Pack.Val));
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set postponed value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - value:
 *  @arg      = 0
 *  @arg      = 1
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetPostponedVal(const uint8_t ChNumIn, const uint8_t ValIn)
{
    if(ChNumIn < PLC_DO_SZ)
    {
        PLC_DO[ChNumIn].Pack.PostponedVal = ((ValIn) ? BIT_TRUE : BIT_FALSE);
        PLC_DO[ChNumIn].Pack.Postponed    = BIT_TRUE;

#ifdef DEBUG_LOG_DO
        DebugLog("DoSet: ch=%d post_val=%d(%d)\n", ChNumIn, PLC_DO[ChNumIn].Pack.PostponedVal, ValIn);
#endif // DEBUG_LOG_DO

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
uint8_t RTOS_TaskDO_SetPostponedApply(const uint8_t ValIn)
{
    if(ValIn)
    {
        for(uint16_t i=0; i<PLC_DO_SZ; i++)
        {
            if(PLC_DO[i].Pack.Mode == PLC_DO_MODE_NORM && PLC_DO[i].Pack.Postponed)
            {
                if(PLC_DO[i].Pack.PostponedVal != PLC_DO[i].Pack.Val)
                {
#ifdef DEBUG_LOG_DO
                    DebugLog("DoSet: ch=%d POST-APPLY\n", i);
#endif // DEBUG_LOG_DO

                    RTOS_TaskDO_SetNormVal(i, PLC_DO[i].Pack.PostponedVal);
                    PLC_DO[i].Pack.Postponed = BIT_FALSE;
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
 *  @arg      = 0
 *  @arg      = 1
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetFastVal(const uint8_t ChNumIn, const uint8_t ValIn)
{
    if(ChNumIn < PLC_DO_SZ)
    {
        PLC_DO[ChNumIn].Pack.FastVal = ((ValIn) ? BIT_TRUE : BIT_FALSE);

#ifdef DEBUG_LOG_DO
        DebugLog("DoSet: ch=%d fast_val=%d(%d)\n", ChNumIn, PLC_DO[ChNumIn].Pack.FastVal, ValIn);
#endif // DEBUG_LOG_DO

        if(PLC_DO[ChNumIn].Pack.Mode == PLC_DO_MODE_FAST)
        {
            return (RTOS_TaskDO_SetVal(PLC_DO[ChNumIn].Pack.ChNum, PLC_DO[ChNumIn].Pack.FastVal));
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set PWM fill factor.
 *  @param  ChNumIn - channel number.
 *  @param  FillFactorIn - fill factor (%).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetPwmFillFactor(const uint8_t ChNumIn, const float FillFactorIn)
{
    if(ChNumIn < PLC_DO_SZ)
    {
        PLC_DO[ChNumIn].PwmFillFactor = FillFactorIn;

        //limitating by MIN and MAX
        if(PLC_DO[ChNumIn].PwmFillFactor < PLC_DO_PWM_FILL_FACTOR__MIN) PLC_DO[ChNumIn].PwmFillFactor = PLC_DO_PWM_FILL_FACTOR__MIN;
        if(PLC_DO[ChNumIn].PwmFillFactor > PLC_DO_PWM_FILL_FACTOR__MAX) PLC_DO[ChNumIn].PwmFillFactor = PLC_DO_PWM_FILL_FACTOR__MAX;

        PLC_DO[ChNumIn].PwmLen1 = RTOS_TaskDO_CalcPwmLen1(PLC_DO[ChNumIn].PwmPeriod, PLC_DO[ChNumIn].PwmFillFactor);
        PLC_DO[ChNumIn].PwmLen0 = RTOS_TaskDO_CalcPwmLen0(PLC_DO[ChNumIn].PwmPeriod, PLC_DO[ChNumIn].PwmLen1);

#ifdef DEBUG_LOG_DO
        DebugLog("DoSet: ch=%d D=%d(%d) len1=%d len0=%d\n", ChNumIn, (uint8_t)PLC_DO[ChNumIn].PwmFillFactor, (uint8_t)FillFactorIn, (uint32_t)PLC_DO[ChNumIn].PwmLen1, (uint32_t)PLC_DO[ChNumIn].PwmLen0);
#endif // DEBUG_LOG_DO

        RTOS_TaskDO_RefreshPwm(ChNumIn);
        return (BIT_TRUE);
    }

    return (BIT_FALSE);
}


/** @brief  Set PWM period.
 *  @param  ChNumIn - channel number.
 *  @param  PeriodIn - period (ms).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetPwmPeriod(const uint8_t ChNumIn, const uint32_t PeriodIn)
{
    if(ChNumIn < PLC_DO_SZ)
    {
        PLC_DO[ChNumIn].PwmPeriod = PeriodIn;

        //limitating by MIN and MAX
        if(PLC_DO[ChNumIn].PwmPeriod < PLC_DO_PWM_PERIOD__MIN) PLC_DO[ChNumIn].PwmPeriod = PLC_DO_PWM_PERIOD__MIN;

        PLC_DO[ChNumIn].PwmLen1 = RTOS_TaskDO_CalcPwmLen1(PLC_DO[ChNumIn].PwmPeriod, PLC_DO[ChNumIn].PwmFillFactor);
        PLC_DO[ChNumIn].PwmLen0 = RTOS_TaskDO_CalcPwmLen0(PLC_DO[ChNumIn].PwmPeriod, PLC_DO[ChNumIn].PwmLen1);

#ifdef DEBUG_LOG_DO
        DebugLog("DoSet: ch=%d T=%d(%d) len1=%d len0=%d\n", ChNumIn, PLC_DO[ChNumIn].PwmPeriod, PeriodIn, (uint32_t)PLC_DO[ChNumIn].PwmLen1, (uint32_t)PLC_DO[ChNumIn].PwmLen0);
#endif // DEBUG_LOG_DO

        RTOS_TaskDO_RefreshPwm(ChNumIn);
        return (BIT_TRUE);
    }

    return (BIT_FALSE);
}


/** @brief  Set PWM allow.
 *  @param  ChNumIn - channel number.
 *  @param  AllowIn - allow:
 *  @arg      = 0 - not allowed
 *  @arg      = 1 - allowed
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetPwmAllow(const uint8_t ChNumIn, const uint8_t AllowIn)
{
    if(ChNumIn < PLC_DO_SZ)
    {
        PLC_DO[ChNumIn].Pack.PwmAllow = ((AllowIn) ? BIT_TRUE : BIT_FALSE);

#ifdef DEBUG_LOG_DO
        DebugLog("DoSet: ch=%d pwm_allow=%d(%d)\n", ChNumIn, PLC_DO[ChNumIn].Pack.PwmAllow, AllowIn);
#endif // DEBUG_LOG_DO

        RTOS_TaskDO_RefreshPwm(ChNumIn);
        return (BIT_TRUE);
    }

    return (BIT_FALSE);
}


/** @brief  Set Mode.
 *  @param  ChNumIn - channel number.
 *  @param  ModeIn - Mode:
 *  @arg      = PLC_DO_MODE_NORM
 *  @arg      = PLC_DO_MODE_FAST
 *  @arg      = PLC_DO_MODE_PWM
 *  @arg      = PLC_DO_MODE_OFF
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetMode(const uint8_t ChNumIn, const uint8_t ModeIn)
{
    if(ChNumIn < PLC_DO_SZ)
    {
        if(PLC_DO[ChNumIn].Pack.Mode != ModeIn && ModeIn <= PLC_DO_MODE_OFF)
        {
            PLC_DO[ChNumIn].Pack.Mode = ModeIn;

#ifdef DEBUG_LOG_DO
            DebugLog("DoSet: ch=%d mode=%d(%d)\n", ChNumIn, PLC_DO[ChNumIn].Pack.Mode, ModeIn);
#endif // DEBUG_LOG_DO

            switch(PLC_DO[ChNumIn].Pack.Mode)
            {
                case PLC_DO_MODE_NORM:
                    RTOS_TaskDO_SetNormVal(PLC_DO[ChNumIn].Pack.ChNum, PLC_DO[ChNumIn].Pack.Val);
                    break;

                case PLC_DO_MODE_FAST:
                    RTOS_TaskDO_SetFastVal(PLC_DO[ChNumIn].Pack.ChNum, PLC_DO[ChNumIn].Pack.FastVal);
                    break;

                case PLC_DO_MODE_PWM:
                    RTOS_TaskDO_SetVal(PLC_DO[ChNumIn].Pack.ChNum, BIT_FALSE);
                    RTOS_TaskDO_RefreshPwm(ChNumIn);
                    break;

                case PLC_DO_MODE_OFF:
                    RTOS_TaskDO_SetVal(PLC_DO[ChNumIn].Pack.ChNum, BIT_FALSE);
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
uint8_t RTOS_TaskDO_SetSafeAllow(const uint8_t ChNumIn, const uint8_t AllowIn)
{
    if(ChNumIn < PLC_DO_SZ)
    {
        uint8_t Allow = ((AllowIn) ? BIT_TRUE : BIT_FALSE);

        if(PLC_DO[ChNumIn].Pack.SafeAllow != Allow)
        {
            PLC_DO[ChNumIn].Pack.SafeAllow = Allow;

#ifdef DEBUG_LOG_DO
            DebugLog("DoSet: ch=%d safe_allow=%d(%d)\n", ChNumIn, PLC_DO[ChNumIn].Pack.SafeAllow, AllowIn);
#endif // DEBUG_LOG_DO

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set Safe-mode value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn - value:
 *  @arg      = 0
 *  @arg      = 1
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDO_SetSafeVal(const uint8_t ChNumIn, const uint8_t ValIn)
{
    if(ChNumIn < PLC_DO_SZ)
    {
        uint8_t Val = ((ValIn) ? BIT_TRUE : BIT_FALSE);

        if(PLC_DO[ChNumIn].Pack.SafeVal != Val)
        {
            PLC_DO[ChNumIn].Pack.SafeVal = Val;

#ifdef DEBUG_LOG_DO
            DebugLog("DoSet: ch=%d safe_val=%d(%d)\n", ChNumIn, PLC_DO[ChNumIn].Pack.SafeVal, ValIn);
#endif // DEBUG_LOG_DO

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
uint8_t RTOS_TaskDO_Set(const PlcDO_Set_t *DataIn)
{
    uint8_t Res = BIT_FALSE;

    if(DataIn)
    {
        switch(DataIn->SetID)
        {
            //DO.Postponed
            case PLC_DO_SET_POSTPONED_VAL:
                Res = RTOS_TaskDO_SetPostponedVal(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                break;

            //DO.PostponedAllow
            case PLC_DO_SET_POSTPONED_APPLY:
                Res = RTOS_TaskDO_SetPostponedApply((uint8_t)DataIn->SetVal);
                break;

            //DO.NormVal
            case PLC_DO_SET_NORM_VAL:
                Res = RTOS_TaskDO_SetNormVal(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                break;

            //DO.FastVal
            case PLC_DO_SET_FAST_VAL:
                Res = RTOS_TaskDO_SetFastVal(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                break;

            //DO.PwmFillFactor
            case PLC_DO_SET_PWM_FILL_FACTOR:
                Res = RTOS_TaskDO_SetPwmFillFactor(DataIn->ChNum, DataIn->SetVal);
                break;

            //DO.PwmPeriod
            case PLC_DO_SET_PWM_PERIOD:
                Res = RTOS_TaskDO_SetPwmPeriod(DataIn->ChNum, (uint32_t)DataIn->SetVal);
                break;

            //DO.PwmAllow
            case PLC_DO_SET_PWM_ALLOW:
                Res = RTOS_TaskDO_SetPwmAllow(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                break;

            //DO.Mode
            case PLC_DO_SET_MODE:
                Res = RTOS_TaskDO_SetMode(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                break;

            //DO.SafeAllow
            case PLC_DO_SET_SAFE_ALLOW:
                Res = RTOS_TaskDO_SetSafeAllow(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                break;

            //DO.SafeVal
            case PLC_DO_SET_SAFE_VAL:
                Res = RTOS_TaskDO_SetSafeVal(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                break;
        }

        /*
        if(Res)
        {
            if(DataIn->SetID == PLC_DO_SET_PWM_ALLOW || DataIn->SetID == PLC_DO_SET_MODE)
            {
                SetRes.ChNum = DataIn->ChNum;

                //Write Queue (not-blocking)
                //send updated channel data
                xQueueSendToBack(RTOS_Q_DataDo, &SetRes, 0);
            }
        }
        */
    }

    return (Res);
}


/** @brief  Init. DO-channels.
 *  @param  none.
 *  @return none.
 */
void RTOS_TaskDO_Init(void)
{
    uint8_t  BuffBy;
    uint32_t BuffDwo;

#ifdef DEBUG_LOG_DO
    DebugLog("DoInit\n");
#endif // DEBUG_LOG_DO

    for(uint16_t i=0; i<PLC_DO_SZ; i++)
    {
        PLC_DO[i].Pack.ChNum = i;

        //read from REG_t (retain)
        BuffBy = PLC_DO_MODE_DEF;
        REG_CopyRegByPos(REG_DO_MODE__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
        PLC_DO[i].Pack.Mode = BuffBy;

        //read from REG_t (retain)
        BuffBy = PLC_DO_SAFE_ALLOW_DEF;
        REG_CopyRegByPos(REG_DO_SAFE_ALLOW__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
        PLC_DO[i].Pack.SafeAllow = BuffBy;

        //read from REG_t (retain)
        BuffBy = PLC_DO_SAFE_VAL_DEF;
        REG_CopyRegByPos(REG_DO_SAFE_VAL__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
        PLC_DO[i].Pack.SafeVal = BuffBy;

        BuffDwo = PLC_DO_PWM_PERIOD_DEF;
        REG_CopyRegByPos(REG_DO_PWM_PERIOD__POS+i, REG_COPY_MB_TO_VAR, &BuffDwo);
        PLC_DO[i].PwmPeriod = BuffDwo;

        PLC_DO[i].Pack.Val          = BIT_FALSE;
        PLC_DO[i].Pack.Postponed    = BIT_FALSE;
        PLC_DO[i].Pack.PostponedVal = BIT_FALSE;
        PLC_DO[i].Pack.FastVal      = BIT_FALSE;
        PLC_DO[i].Pack.PwmAllow     = BIT_FALSE;
        PLC_DO[i].PwmFillFactor     = PLC_DO_PWM_FILL_FACTOR_DEF;
        PLC_DO[i].PwmLen0           = 0;
        PLC_DO[i].PwmLen1           = 0;
        PLC_DO[i].Pin               = &PLC_DO_PINS[i];

        PLC_DO_PWM[i].Stat          = BIT_TRUE;
        PLC_DO_PWM[i].Ticks         = 0;

#ifdef DEBUG_LOG_DO
        DebugLog("Do[%d]: Mode=%d SafeAllow=%d SafeVal=%d PwmPer=%d\n", i, PLC_DO[i].Pack.Mode, PLC_DO[i].Pack.SafeAllow, PLC_DO[i].Pack.SafeVal, PLC_DO[i].PwmPeriod);
#endif // DEBUG_LOG_DO
    }
}


/** @brief  Task `DO`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskDO(void *ParamsIn)
{
    //VARIABLES
    PlcDO_Set_t QueueData_Set;
    BaseType_t  QueueStatus;

    //INIT
    (void)ParamsIn; //fix unused

    //START
    for(;;)
    {
        //Read Queue (blocking)
        //get updated settings
        QueueStatus = xQueueReceive(RTOS_Q_DoSet, &QueueData_Set, portMAX_DELAY);
        if(QueueStatus == pdPASS)
        {
            //unpack settings
            RTOS_TaskDO_Set(&QueueData_Set);
        }

        //fast switch to other task
        taskYIELD();
    }
}


/** @brief  TIM2 interrupts handler.
 *  @param  none.
 *  @return none.
 */
void TIM2_IRQHandler(void)
{
    uint16_t cPwm   = 0;
    uint8_t  PinVal = BIT_FALSE;

    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        for(uint16_t i=0; i<PLC_DO_SZ; i++)
        {
            PinVal = BIT_FALSE;

            if(PLC_DO[i].Pack.Mode == PLC_DO_MODE_PWM)
            {
                if(PLC_DO[i].Pack.PwmAllow && PLC_DO[i].PwmLen1)
                {
                    //tick
                    PLC_DO_PWM[i].Ticks+= PLC_TIM2_PERIOD_US;

                    if(PLC_DO_PWM[i].Stat)
                    {
                        //PWM TRUE-value
                        if(PLC_DO_PWM[i].Ticks >= PLC_DO[i].PwmLen1 && PLC_DO[i].PwmLen0 > 0)
                        {
                            PLC_DO_PWM[i].Stat  = BIT_FALSE;
                            PLC_DO_PWM[i].Ticks = 0;
                        }
                        else
                        {
                            PinVal = BIT_TRUE;
                        }
                    }
                    else
                    {
                        //PWM FALSE-value
                        if(PLC_DO_PWM[i].Ticks >= PLC_DO[i].PwmLen0)
                        {
                            PLC_DO_PWM[i].Stat  = BIT_TRUE;
                            PLC_DO_PWM[i].Ticks = 0;
                        }
                    }

                    cPwm++;
                }

                //set output value
                RTOS_TaskDO_SetVal((uint8_t)i, PinVal);
            }
        }

        if(!cPwm)
        {
            //stop PWM-timer
            PlcTim2_Stop();
        }
    }
}
