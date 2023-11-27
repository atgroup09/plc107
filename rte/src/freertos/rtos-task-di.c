/* @page rtos-task-di.h
 *       FreeRTOS Task
 *       Discrete inputs
 *       2020-2022
 */

#include "rtos-task-di.h"


/** @var DI channels
 */
static PlcDI_t PLC_DI[PLC_DI_SZ];

/** @var DI pins
 */
static PlcDI_Pin_t PLC_DI_PINS[PLC_DI_SZ] =
{
    {
        .Port    = PLC_DI_00__PORT,
        .Pin     = PLC_DI_00__PIN
    },
    {
        .Port    = PLC_DI_01__PORT,
        .Pin     = PLC_DI_01__PIN
    },
    {
        .Port    = PLC_DI_02__PORT,
        .Pin     = PLC_DI_02__PIN
    },
    {
        .Port    = PLC_DI_03__PORT,
        .Pin     = PLC_DI_03__PIN
    }
};

/** @var  Status of Tachometer reloading timer.
 *  @arg    = 0 - off
 *  @arg    = 1 - on
 */
static uint8_t PLC_DI_TIM_TACH_STATUS = BIT_FALSE;


/** @brief  Start Tachometer reloading timer.
 *  @param  None.
 *  @return None.
 */
void RTOS_TimDiTach_Start(void)
{
    if(!PLC_DI_TIM_TACH_STATUS)
    {
        xTimerStart(RTOS_TIM_DiTach, 0);
        PLC_DI_TIM_TACH_STATUS = BIT_TRUE;
    }
}


/** @brief  Stop Tachometer reloading timer.
 *  @param  None.
 *  @return None.
 */
void RTOS_TimDiTach_Stop(void)
{
    if(PLC_DI_TIM_TACH_STATUS)
    {
        xTimerStop(RTOS_TIM_DiTach, 0);
        PLC_DI_TIM_TACH_STATUS = BIT_FALSE;
    }
}


/** @brief  Refresh Tachometer channel.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_RefreshTach(const uint8_t ChNumIn)
{
    if(ChNumIn < PLC_DI_SZ)
    {
        if(PLC_DI[ChNumIn].Pack.Mode == PLC_DI_MODE_TACH || PLC_DI[ChNumIn].Pack.Mode == PLC_DI_MODE_INC2)
        {
            RTOS_TimDiTach_Start();
            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}


/** @brief  Tachometer setpoint.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_TachSetpoint(const uint8_t ChNumIn)
{
    if(ChNumIn < PLC_DI_SZ)
    {
        PLC_DI[ChNumIn].Pack.TachSetpointRes = BIT_FALSE;

        //test allow to work the counter by setpoint
        if(PLC_DI[ChNumIn].Pack.TachSetpointAllow)
        {
            //test setpoint
            if(PLC_DI[ChNumIn].TachVal >= PLC_DI[ChNumIn].TachSetpoint)
            {
                PLC_DI[ChNumIn].Pack.TachSetpointRes = BIT_TRUE;
            }
        }
        return (BIT_TRUE);
    }
    return (BIT_FALSE);
}


/** @brief  Tachometer reset.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_TachReset(const uint8_t ChNumIn)
{
    if(ChNumIn < PLC_DI_SZ)
    {
        PLC_DI[ChNumIn].TachVal = 0;
        return (RTOS_TaskDI_TachSetpoint(ChNumIn));
    }
    return (BIT_FALSE);
}


/** @brief  Tachometer counter.
 *  @param  ChNumIn   - channel number.
 *  @param  ValIn     - channel value.
 *  @param  ValPrevIn - channel previous value.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_TachCntr(const uint8_t ChNumIn, const uint8_t ValIn, const uint8_t ValPrevIn)
{
    if(ChNumIn < PLC_DI_SZ)
    {
        //by Front
        if(ValIn && ValIn != ValPrevIn)
        {
            PLC_DI[ChNumIn].TachCntrVal++;
            return (BIT_TRUE);
        }
    }
    return (BIT_FALSE);
}


/** @brief  Counter setpoint.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_CntrSetpoint(const uint8_t ChNumIn)
{
    if(ChNumIn < PLC_DI_SZ)
    {
        PLC_DI[ChNumIn].Pack.CntrSetpointRes = BIT_FALSE;

        //test allow to work the counter by setpoint
        if(PLC_DI[ChNumIn].Pack.CntrSetpointAllow)
        {
            //test setpoint
            if(PLC_DI[ChNumIn].CntrVal >= PLC_DI[ChNumIn].CntrSetpoint)
            {
                PLC_DI[ChNumIn].Pack.CntrSetpointRes = BIT_TRUE;
            }
        }
        return (BIT_TRUE);
    }
    return (BIT_FALSE);
}


/** @brief  Counter reset.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_CntrReset(const uint8_t ChNumIn)
{
    if(ChNumIn < PLC_DI_SZ)
    {
        PLC_DI[ChNumIn].CntrVal = 0;
        return (RTOS_TaskDI_CntrSetpoint(ChNumIn));
    }
    return (BIT_FALSE);
}


/** @brief  Counter.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn   - channel value.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_Cntr(const uint8_t ChNumIn, const uint8_t ValIn)
{
    if(ChNumIn < PLC_DI_SZ)
    {
        //by Front
        if(ValIn && ValIn != PLC_DI[ChNumIn].Pack.Val)
        {
            PLC_DI[ChNumIn].CntrVal++;
            return (RTOS_TaskDI_CntrSetpoint(ChNumIn));
        }
    }
    return (BIT_FALSE);
}


/** @brief  Incremental encoder (counter).
 *  @param  ChNumIn - channel number.
 *  @param  ValIn   - channel value.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_Inc1(const uint8_t ChNumIn, const uint8_t ValIn)
{
    if(ChNumIn < PLC_DI_SZ)
    {
        uint8_t ChNumPair = PLC_DI[ChNumIn].Pack.ChNumPair;

        //test value of pair channel
        if(!PLC_DI[ChNumPair].Pack.Val)
        {
            return (RTOS_TaskDI_Cntr(ChNumIn, ValIn));
        }
    }
    return (BIT_FALSE);
}


/** @brief  Incremental encoder (counter + tachometer).
 *  @param  ChNumIn - channel number.
 *  @param  ValIn   - channel value.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_Inc2(const uint8_t ChNumIn, const uint8_t ValIn)
{
    //used tachometer counter value of phase B to store tachometer counts of phase A
    uint8_t TachChNum = ((PLC_DI_IS_PHASE_A(ChNumIn)) ? PLC_DI[ChNumIn].Pack.ChNumPair : ChNumIn);
    RTOS_TaskDI_TachCntr(TachChNum, ValIn, PLC_DI[ChNumIn].Pack.Val);
    return (RTOS_TaskDI_Inc1(ChNumIn, ValIn));
}


/** @brief  Test pair dependent.
 *  @param  ChNumIn - channel number.
 *  @return Result:
 *  @arg      = 0 - the channel is not dependent
 *  @arg      = 1 - the channel is dependent
 */
uint8_t RTOS_TaskDI_TestPair(const uint8_t ChNumIn)
{
    if(PLC_DI_IS_PHASE_B(ChNumIn))
    {
        //the channel is phase B of pair (slave)
        //test mode of phase A (main)
        if(PLC_DI[ChNumIn-1].Pack.Mode >= PLC_DI_MODE_INC1) return (BIT_TRUE);
    }
    return (BIT_FALSE);
}


/** @brief  Set tachometer setpoint and allow to work by setpoint.
 *  @param  ChNumIn - channel number.
 *  @param  SetPointIn - setpoint value.
 *  @param  SetPointAllowIn - allow to work by the setpoint.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_SetTachSetpoint(const uint8_t ChNumIn, const uint16_t SetPointIn, const uint8_t SetPointAllowIn)
{
    if(ChNumIn < PLC_DI_SZ)
    {
        PLC_DI[ChNumIn].TachSetpoint = SetPointIn;
        PLC_DI[ChNumIn].Pack.TachSetpointAllow = ((SetPointAllowIn) ? BIT_TRUE : BIT_FALSE);
        RTOS_TaskDI_TachSetpoint(ChNumIn);

#ifdef DEBUG_LOG_DI
        DebugLog("DiSet: ch=%d tach sp=%d(%d) spa=%d\n", ChNumIn, SetPointIn, PLC_DI[ChNumIn].TachSetpoint, PLC_DI[ChNumIn].Pack.TachSetpointAllow);
#endif // DEBUG_LOG_DI

        return (BIT_TRUE);
    }
    return (BIT_FALSE);
}


/** @brief  Set counter setpoint and allow to work by setpoint.
 *  @param  ChNumIn - channel number.
 *  @param  SetPointIn - setpoint value.
 *  @param  SetPointAllowIn - allow to work by the setpoint.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_SetCntrSetpoint(const uint8_t ChNumIn, const uint32_t SetPointIn, const uint8_t SetPointAllowIn)
{
    if(ChNumIn < PLC_DI_SZ)
    {
        PLC_DI[ChNumIn].CntrSetpoint = SetPointIn;
        PLC_DI[ChNumIn].Pack.CntrSetpointAllow = ((SetPointAllowIn) ? BIT_TRUE : BIT_FALSE);
        RTOS_TaskDI_CntrSetpoint(ChNumIn);

#ifdef DEBUG_LOG_DI
        DebugLog("DiSet: ch=%d cntr sp=%d(%d) spa=%d\n", ChNumIn, SetPointIn, PLC_DI[ChNumIn].CntrSetpoint, PLC_DI[ChNumIn].Pack.CntrSetpointAllow);
#endif // DEBUG_LOG_DI

        return (BIT_TRUE);
    }
    return (BIT_FALSE);
}


/** @brief  Set reset.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn   - value of command.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_SetReset(const uint8_t ChNumIn, const uint8_t ValIn)
{
    if(ChNumIn < PLC_DI_SZ)
    {
        //command from not encoder channels
        //or from encoder channels of pair phase A
        if(PLC_DI[ChNumIn].Pack.Mode < PLC_DI_MODE_INC1 || (PLC_DI[ChNumIn].Pack.Mode >= PLC_DI_MODE_INC1 && PLC_DI_IS_PHASE_A(ChNumIn)))
        {
            PLC_DI[ChNumIn].Pack.Reset = ((ValIn) ? BIT_TRUE : BIT_FALSE);

            if(PLC_DI[ChNumIn].Pack.Reset)
            {
                RTOS_TaskDI_CntrReset(ChNumIn);
                RTOS_TaskDI_TachReset(ChNumIn);

                if(PLC_DI[ChNumIn].Pack.Mode >= PLC_DI_MODE_INC1)
                {
                    //reset channel of pair phase B
                    RTOS_TaskDI_CntrReset(PLC_DI[ChNumIn].Pack.ChNumPair);
                    RTOS_TaskDI_TachReset(PLC_DI[ChNumIn].Pack.ChNumPair);
                }

                PLC_DI[ChNumIn].Pack.Reset = BIT_FALSE;
            }

#ifdef DEBUG_LOG_DI
            DebugLog("DiSet: ch=%d rst=%d(%d)\n", ChNumIn, ValIn, PLC_DI[ChNumIn].Pack.Reset);
#endif // DEBUG_LOG_DI

            return (BIT_TRUE);
        }
    }
    return (BIT_FALSE);
}


/** @brief  Set mode.
 *  @param  ChNumIn - channel number.
 *  @param  ModeIn  - channel mode:
 *  @arg      = 0 - normal
 *  @arg      = 1 - counter
 *  @arg      = 2 - tachometer
 *  @arg      = 3 - incremental encoder (counter)
 *  @arg      = 4 - incremental encoder (counter + tachometer)
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskDI_SetMode(const uint8_t ChNumIn, const uint8_t ModeIn)
{
    uint8_t Res = BIT_FALSE;

    if(ChNumIn < PLC_DI_SZ)
    {
        uint8_t ChNumPair = PLC_DI[ChNumIn].Pack.ChNumPair;

        switch(ModeIn)
        {
            case PLC_DI_MODE_NORM:
            case PLC_DI_MODE_CNTR:
            case PLC_DI_MODE_TACH:
                //for channels of pair phase A
                //or channels of pair phase B are not dependent by phase A
                if(!RTOS_TaskDI_TestPair(ChNumIn))
                {
                    if(PLC_DI_IS_PHASE_A(ChNumIn) && PLC_DI[ChNumIn].Pack.Mode >= PLC_DI_MODE_INC1)
                    {
                        //reset mode of pair phase B to Normal
                        PLC_DI[ChNumPair].Pack.Mode = PLC_DI_MODE_NORM;
                        RTOS_TaskDI_SetReset(ChNumPair, BIT_TRUE);
                    }

                    PLC_DI[ChNumIn].Pack.Mode = ModeIn;
                    RTOS_TaskDI_SetReset(ChNumIn, BIT_TRUE);
                    Res = BIT_TRUE;

                    if(ModeIn == PLC_DI_MODE_TACH) RTOS_TaskDI_RefreshTach(ChNumIn);
                }
                break;

            case PLC_DI_MODE_INC1:
            case PLC_DI_MODE_INC2:
                //only for channels of pair phase A
                if(PLC_DI_IS_PHASE_A(ChNumIn))
                {
                    //phase A
                    PLC_DI[ChNumIn].Pack.Mode = ModeIn;
                    RTOS_TaskDI_SetReset(ChNumIn, BIT_TRUE);
                    //phase B
                    PLC_DI[ChNumPair].Pack.Mode = ModeIn;
                    RTOS_TaskDI_SetReset(ChNumPair, BIT_TRUE);
                    Res = BIT_TRUE;

                    if(ModeIn == PLC_DI_MODE_INC2) RTOS_TaskDI_RefreshTach(ChNumIn);
                }
                break;
        }
#ifdef DEBUG_LOG_DI
        DebugLog("DiSet: ch=%d mode=%d(%d)\0", ChNumIn, ModeIn, PLC_DI[ChNumIn].Pack.Mode);
        if(ModeIn >= PLC_DI_MODE_INC1)
        {
            DebugLog(" p=%d\0", PLC_DI[ChNumIn].Pack.ChNumPair);
        }
        DebugLog("\n");
#endif // DEBUG_LOG_DI
    }
    return (Res);
}


/** @brief  Task `DI Settings`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskDI_Set(void *ParamsIn)
{
    PlcDI_Set_t QueueData_Set;
    BaseType_t  QueueStatus;
    uint8_t     Res = BIT_FALSE;

    //INIT
    (void)ParamsIn; //fix unused

    //START
    for(;;)
    {
        //Read Queue (blocking)
        //get updated settings
        QueueStatus = xQueueReceive(RTOS_Q_DiSet, &QueueData_Set, portMAX_DELAY);
        if(QueueStatus == pdPASS)
        {
            if(QueueData_Set.ChNum < PLC_DI_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_Di, portMAX_DELAY);

                switch(QueueData_Set.SetID)
                {
                    //DI.Mode
                    case PLC_DI_SET_MODE:
                        Res = RTOS_TaskDI_SetMode(QueueData_Set.ChNum, (uint8_t)QueueData_Set.SetVal);
                        break;

                    //DI.Reset
                    case PLC_DI_SET_RESET:
                        Res = RTOS_TaskDI_SetReset(QueueData_Set.ChNum, (uint8_t)QueueData_Set.SetVal);
                        break;

                    //DI.Cntr.Setpoint
                    case PLC_DI_SET_CNTR_SETPOINT:
                        Res = RTOS_TaskDI_SetCntrSetpoint(QueueData_Set.ChNum, QueueData_Set.SetVal, PLC_DI[QueueData_Set.ChNum].Pack.CntrSetpointAllow);
                        break;

                    //DI.Cntr.SetpointAllow
                    case PLC_DI_SET_CNTR_SETPOINT_ALLOW:
                        Res = RTOS_TaskDI_SetCntrSetpoint(QueueData_Set.ChNum, PLC_DI[QueueData_Set.ChNum].CntrSetpoint, (uint8_t)QueueData_Set.SetVal);
                        break;

                    //DI.Tach.Setpoint
                    case PLC_DI_SET_TACH_SETPOINT:
                        Res = RTOS_TaskDI_SetTachSetpoint(QueueData_Set.ChNum, (uint16_t)QueueData_Set.SetVal, PLC_DI[QueueData_Set.ChNum].Pack.TachSetpointAllow);
                        break;

                    //DI.Tach.SetpointAllow
                    case PLC_DI_SET_TACH_SETPOINT_ALLOW:
                        Res = RTOS_TaskDI_SetTachSetpoint(QueueData_Set.ChNum, PLC_DI[QueueData_Set.ChNum].TachSetpoint, (uint8_t)QueueData_Set.SetVal);
                        break;
                }

                xSemaphoreGive(RTOS_MTX_Di);
                //UNLOCK

                if(Res)
                {
                    //Write Queue (not-blocking)
                    //send updated channel data
                    xQueueSendToBack(RTOS_Q_DataDi, &PLC_DI[QueueData_Set.ChNum], 0);

                    if(QueueData_Set.SetID == PLC_DI_SET_MODE || QueueData_Set.SetID == PLC_DI_SET_RESET)
                    {
                        //send updated pair channel data
                        xQueueSendToBack(RTOS_Q_DataDi, &PLC_DI[PLC_DI[QueueData_Set.ChNum].Pack.ChNumPair], 0);
                    }
                }
            }
        }

        //fast switch to other task
        taskYIELD();
    }
}


/** @brief  Task `DI IRQ`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskDI_IRQ(void *ParamsIn)
{
    PlcDI_IRQ_t QueueData_IRQ;
    BaseType_t  QueueStatus;
    uint8_t     Val = BIT_FALSE;

    //INIT
    (void)ParamsIn; //fix unused

    //START
    for(;;)
    {
        //Read Queue (blocking)
        //get IRQ-data
        QueueStatus = xQueueReceive(RTOS_Q_DiIrq, &QueueData_IRQ, portMAX_DELAY);
        if(QueueStatus == pdPASS)
        {
            if(QueueData_IRQ.ChNum < PLC_DI_SZ)
            {
                //LOCK
                xSemaphoreTake(RTOS_MTX_Di, portMAX_DELAY);

                Val = GPIO_ReadInputDataBit(PLC_DI[QueueData_IRQ.ChNum].Pin->Port, PLC_DI[QueueData_IRQ.ChNum].Pin->Pin);

                switch(PLC_DI[QueueData_IRQ.ChNum].Pack.Mode)
                {
                    //counter
                    case PLC_DI_MODE_CNTR:
                        RTOS_TaskDI_Cntr(QueueData_IRQ.ChNum, Val);
                        break;

                    //tachometer
                    case PLC_DI_MODE_TACH:
                        RTOS_TaskDI_TachCntr(QueueData_IRQ.ChNum, Val, PLC_DI[QueueData_IRQ.ChNum].Pack.Val);
                        break;

                    //incremental encoder (counter)
                    case PLC_DI_MODE_INC1:
                        RTOS_TaskDI_Inc1(QueueData_IRQ.ChNum, Val);
                        break;

                    //incremental encoder (counter + tachometer)
                    case PLC_DI_MODE_INC2:
                        RTOS_TaskDI_Inc2(QueueData_IRQ.ChNum, Val);
                        break;
                }

                xSemaphoreGive(RTOS_MTX_Di);
                //UNLOCK

                //Update normal channel value
                PLC_DI[QueueData_IRQ.ChNum].Pack.Val = Val;

                //Write Queue (not-blocking)
                //send updated channel data
                xQueueSendToBack(RTOS_Q_DataDi, &PLC_DI[QueueData_IRQ.ChNum], 0);
            }
        }

        //fast switch to other task
        taskYIELD();
    }
}


/** @brief  Init. DI-channels.
 *  @param  none.
 *  @return none.
 */
void RTOS_TaskDI_Init(void)
{
    uint8_t  BuffBy;
    uint16_t BuffWo;
    uint32_t BuffDwo;

#ifdef DEBUG_LOG_DI
    DebugLog("DiInit\n");
#endif // DEBUG_LOG_DI

    for(uint16_t i=0; i<PLC_DI_SZ; i++)
    {
        PLC_DI[i].Pack.ChNum = i;

        //read from REG_t (retain)
        BuffBy = PLC_DI_MODE_DEF;
        REG_CopyRegByPos(REG_DI_MODE__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
        PLC_DI[i].Pack.Mode = BuffBy;

        //read from REG_t (retain)
        BuffWo = PLC_DI_TACH_SETPOINT_DEF;
        REG_CopyRegByPos(REG_DI_TACH_SETPOINT__POS+i, REG_COPY_MB_TO_VAR, &BuffWo);
        PLC_DI[i].TachSetpoint = BuffWo;

        //read from REG_t (retain)
        BuffBy = PLC_DI_TACH_SETPOINT_ALLOW_DEF;
        REG_CopyRegByPos(REG_DI_TACH_SETPOINT_ALLOW__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
        PLC_DI[i].Pack.TachSetpointAllow = BuffBy;

        //read from REG_t (retain)
        BuffDwo = PLC_DI_CNTR_SETPOINT_DEF;
        REG_CopyRegByPos(REG_DI_CNTR_SETPOINT__POS+i, REG_COPY_MB_TO_VAR, &BuffDwo);
        PLC_DI[i].CntrSetpoint = BuffDwo;

        //read from REG_t (retain)
        BuffBy = PLC_DI_CNTR_SETPOINT_ALLOW_DEF;
        REG_CopyRegByPos(REG_DI_TACH_SETPOINT_ALLOW__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
        PLC_DI[i].Pack.CntrSetpointAllow = BuffBy;

        PLC_DI[i].Pack.CntrSetpointRes   = BIT_FALSE;
        PLC_DI[i].Pack.TachSetpointRes   = BIT_FALSE;
        PLC_DI[i].Pack.Val               = GPIO_ReadInputDataBit(PLC_DI_PINS[i].Port, PLC_DI_PINS[i].Pin);
        PLC_DI[i].Pack.Reset             = BIT_FALSE;
        PLC_DI[i].Pack.ChNumPair         = ((PLC_DI_IS_PHASE_A(i)) ? (i+1) : (i-1));
        PLC_DI[i].CntrVal                = 0;
        PLC_DI[i].TachVal                = 0;
        PLC_DI[i].TachCntrVal            = 0;

        PLC_DI[i].Pin = &PLC_DI_PINS[i];

        BuffBy = (uint8_t)PLC_DI[i].Pack.Val;
        REG_CopyRegByPos(REG_DI_NORM_VAL__POS+i, REG_COPY_VAR_TO_MB, &BuffBy);

#ifdef DEBUG_LOG_DI
        DebugLog("Di[%d]: Mode=%d TachSp=%d TachAllow=%d CntrSp=%d CntrAllow=%d\n", i, PLC_DI[i].Pack.Mode, PLC_DI[i].TachSetpoint, PLC_DI[i].Pack.TachSetpointAllow, PLC_DI[i].CntrSetpoint, PLC_DI[i].Pack.CntrSetpointAllow);
#endif // DEBUG_LOG_DI
    }
}


/** @brief  Timer-handler `Tachometer reloading`.
 *  @param  TimerIn - timer.
 *  @return none.
 */
void RTOS_TimDiTach(TimerHandle_t TimerIn)
{
    (void)TimerIn; //fix unused
    uint16_t cTach = 0, ValPrev = 0;

    //LOCK
    xSemaphoreTake(RTOS_MTX_Di, portMAX_DELAY);

    for(uint16_t i=0; i<PLC_DI_SZ; i++)
    {
        if(PLC_DI[i].Pack.Mode == PLC_DI_MODE_TACH || (PLC_DI[i].Pack.Mode == PLC_DI_MODE_INC2 && PLC_DI_IS_PHASE_B(i)))
        {
            ValPrev = PLC_DI[i].TachVal;
            PLC_DI[i].TachVal     = (uint16_t)PLC_DI[i].TachCntrVal;
            PLC_DI[i].TachCntrVal = 0;

            RTOS_TaskDI_TachSetpoint(i);
            cTach++;

            if(PLC_DI[i].TachVal != ValPrev)
            {
                //Write Queue (blocking)
                //send updated channel data
                xQueueSendToBack(RTOS_Q_DataDi, &PLC_DI[i], 0);
            }
        }
    }

    xSemaphoreGive(RTOS_MTX_Di);
    //UNLOCK

    if(!cTach)
    {
        //stop tachometer-reloading timer
        RTOS_TimDiTach_Stop();
    }
}
