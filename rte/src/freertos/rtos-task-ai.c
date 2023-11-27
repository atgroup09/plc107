/* @page rtos-task-ai.c
 *       FreeRTOS Task
 *       AI
 *       2020-2022
 */

#include "rtos-task-ai.h"


/** @var AI channels
 */
static PlcAI_t PLC_AI[PLC_AI_SZ];


/** @var  Status of TimAi.
 *  @arg    = 0 - off
 *  @arg    = 1 - on
 */
static uint8_t PLC_AI_TIM_STATUS = BIT_FALSE;


/** @brief  Turn-off channel.
 *  @param  ChNumIn - channel number.
 *  @return None.
 */
void RTOS_TaskAI_Off(const uint8_t ChNumIn)
{
    if(ChNumIn < PLC_AI_SZ)
    {
        PlcAI_Set_t QueueData;

        PLC_AI[ChNumIn].Pack.Status = PLC_AI_STATUS_OFF;
        PLC_AI[ChNumIn].Val         = PLC_AI_ANA_STATUS_OFF;

        //Send Status to T_Data
        QueueData.ChNum  = ChNumIn;
        QueueData.SetID  = PLC_AI_SET_STATUS;
        QueueData.SetVal = (float)(PLC_AI[ChNumIn].Pack.Status);
        //write Queue (not-blocking)
        xQueueSendToBack(RTOS_Q_DataAi, &QueueData, 0);

        //Send Value to T_Data
        QueueData.ChNum  = ChNumIn;
        QueueData.SetID  = PLC_AI_SET_VAL;
        QueueData.SetVal = PLC_AI[ChNumIn].Val;
        //write Queue (not-blocking)
        xQueueSendToBack(RTOS_Q_DataAi, &QueueData, 0);

#ifdef DEBUG_LOG_AI
        DebugLog("AiOff: ChNum=%d [OFF]\n", ChNumIn);
#endif // DEBUG_LOG_AI
    }
}


/** @brief  Start survey.
 *  @param  ChNumIn - channel number.
 *  @return None.
 */
void RTOS_TaskAI_StartSurvey(const uint8_t ChNumIn)
{
    if(ChNumIn < PLC_AI_SZ)
    {
        PlcAI_Set_t QueueData;

        PLC_AI[ChNumIn].Pack.Status = PLC_AI_STATUS_SURVEY;

        //Send Status to T_Data
        QueueData.ChNum  = ChNumIn;
        QueueData.SetID  = PLC_AI_SET_STATUS;
        QueueData.SetVal = (float)(PLC_AI[ChNumIn].Pack.Status);
        //write Queue (not-blocking)
        xQueueSendToBack(RTOS_Q_DataAi, &QueueData, 0);

        RTOS_TimAi_Start();

#ifdef DEBUG_LOG_AI
        DebugLog("AiSurvey: ChNum=%d [START]\n", ChNumIn);
#endif // DEBUG_LOG_AI
    }
}


/** @brief  Start calibration.
 *  @param  ChNumIn - channel number.
 *  @return None.
 */
void RTOS_TaskAI_StartCalb(const uint8_t ChNumIn)
{
    if(ChNumIn < PLC_AI_SZ)
    {
        PlcAI_Set_t QueueData;

        PLC_AI[ChNumIn].Pack.Status = PLC_AI_STATUS_CALB;
        PLC_AI[ChNumIn].Val         = PLC_AI_ANA_STATUS_CALB;

        //Send Status to T_Data
        QueueData.ChNum  = ChNumIn;
        QueueData.SetID  = PLC_AI_SET_STATUS;
        QueueData.SetVal = (float)(PLC_AI[ChNumIn].Pack.Status);
        //write Queue (not-blocking)
        xQueueSendToBack(RTOS_Q_DataAi, &QueueData, 0);

        //Send Value to T_Data
        QueueData.ChNum  = ChNumIn;
        QueueData.SetID  = PLC_AI_SET_VAL;
        QueueData.SetVal = PLC_AI[ChNumIn].Val;
        //write Queue (not-blocking)
        xQueueSendToBack(RTOS_Q_DataAi, &QueueData, 0);

#ifdef DEBUG_LOG_AI
        DebugLog("AiCalb: ChNum=%d [START]\n", ChNumIn);
#endif // DEBUG_LOG_AI
    }
}


/** @brief  Set Mode.
 *  @param  ChNumIn - channel number.
 *  @param  ModeIn - Mode (see ai.h).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_SetMode(const uint8_t ChNumIn, const uint8_t ModeIn)
{
    if(ChNumIn < PLC_AI_SZ)
    {
        if(PLC_AI[ChNumIn].Pack.Mode != ModeIn && ModeIn <= PLC_AI_MODE_OFF)
        {
            PLC_AI[ChNumIn].Pack.Mode    = ModeIn;
            PLC_AI[ChNumIn].Pack.ModeRes = PLC_AI[ChNumIn].Pack.Mode;

            switch(PLC_AI[ChNumIn].Pack.Mode)
            {
                case PLC_AI_MODE_SURVEY:
                    RTOS_TaskAI_StartSurvey(ChNumIn);
                    break;

                case PLC_AI_MODE_CALB:
                    RTOS_TaskAI_StartCalb(ChNumIn);
                    break;

                case PLC_AI_MODE_OFF:
                    RTOS_TaskAI_Off(ChNumIn);
                    break;
            }

#ifdef DEBUG_LOG_AI
            DebugLog("AiSetMode: ChNum=%d Mode=%d %d(%d) [SET]\n", ChNumIn, ModeIn, PLC_AI[ChNumIn].Pack.Mode, PLC_AI[ChNumIn].Pack.ModeRes);
#endif // DEBUG_LOG_AI

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set value.
 *  @param  ChNumIn - channel number.
 *  @param  ValIn   - value.
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_SetVal(const uint8_t ChNumIn, const float ValIn)
{
    if(ChNumIn < PLC_AI_SZ)
    {
        if(PLC_AI[ChNumIn].Val != ValIn)
        {
            PLC_AI[ChNumIn].Val = ValIn;

#ifdef DEBUG_LOG_AI
            DebugLog("AiSetVal: ChNum=%d Val=%d %d [SET]\n", ChNumIn, (uint32_t)ValIn, (uint32_t)PLC_AI[ChNumIn].Val);
#endif // DEBUG_LOG_AI

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set status.
 *  @param  ChNumIn  - channel number.
 *  @param  StatusIn - status (see ai.h).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_SetStatus(const uint8_t ChNumIn, const uint8_t StatusIn)
{
    if(ChNumIn < PLC_AI_SZ)
    {
        PLC_AI[ChNumIn].Pack.Status = StatusIn;

#ifdef DEBUG_LOG_AI
            DebugLog("AiSetStatus: ChNum=%d Val=%d %d [SET]\n", ChNumIn, StatusIn, PLC_AI[ChNumIn].Pack.Status);
#endif // DEBUG_LOG_AI

        return (BIT_TRUE);
    }

    return (BIT_FALSE);
}


/** @brief  Set calibrated current ADC-code for Lo-level.
 *  @param  ChNumIn - channel number.
 *  @param  CmdIn   - command (0, 1).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_SetCalbLoCmd(const uint8_t ChNumIn, const uint8_t CmdIn)
{
    if(ChNumIn < PLC_AI_SZ)
    {
        if(CmdIn && PLC_AI[ChNumIn].Pack.Mode == PLC_AI_MODE_CALB)
        {
            PLC_AI[ChNumIn].I1 = PlcAI_GetDigLv(ChNumIn);

#ifdef DEBUG_LOG_AI
            DebugLog("AiSetCalbLoCmd: ChNum=%d Cmd=%d Y1=%d I1=%d [SET]\n", ChNumIn, CmdIn, (uint32_t)PLC_AI_ANA_MIN, PLC_AI[ChNumIn].I1);
#endif // DEBUG_LOG_AI

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}


/** @brief  Set calibrated current ADC-code for Hi-level.
 *  @param  ChNumIn - channel number.
 *  @param  CmdIn   - command (0, 1).
 *  @return Result:
 *  @arg      = 0 - not updated
 *  @arg      = 1 - updated
 */
uint8_t RTOS_TaskAI_SetCalbHiCmd(const uint8_t ChNumIn, const uint8_t CmdIn)
{
    if(ChNumIn < PLC_AI_SZ)
    {
        if(CmdIn && PLC_AI[ChNumIn].Pack.Mode == PLC_AI_MODE_CALB)
        {
            PLC_AI[ChNumIn].I2 = PlcAI_GetDigLv(ChNumIn);

#ifdef DEBUG_LOG_AI
            DebugLog("AiSetCalbLoCmd: ChNum=%d Cmd=%d Y2=%d I2=%d [SET]\n", ChNumIn, CmdIn, (uint32_t)PLC_AI_ANA_MAX, PLC_AI[ChNumIn].I2);
#endif // DEBUG_LOG_AI

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
uint8_t RTOS_TaskAI_SetCalbCmd(const uint8_t ChNumIn, const uint8_t CmdIn)
{
    if(ChNumIn < PLC_AI_SZ)
    {
        if(CmdIn && PLC_AI[ChNumIn].Pack.Mode == PLC_AI_MODE_CALB)
        {
            PLC_AI[ChNumIn].Ka = ScaleA_Ka(PLC_AI_ANA_MIN, PLC_AI_ANA_MAX, (float)PLC_AI[ChNumIn].I1, (float)PLC_AI[ChNumIn].I2);
            PLC_AI[ChNumIn].Kb = ScaleA_Kb(PLC_AI_ANA_MIN, PLC_AI_ANA_MAX, (float)PLC_AI[ChNumIn].I1, (float)PLC_AI[ChNumIn].I2);

            PLC_AI[ChNumIn].Pack.Status = PLC_AI_STATUS_CALB_DONE;

            PlcAI_Set_t QueueData;
            //Send Status to T_Data
            QueueData.ChNum  = ChNumIn;
            QueueData.SetID  = PLC_AI_SET_STATUS;
            QueueData.SetVal = (float)(PLC_AI[ChNumIn].Pack.Status);
            //write Queue (not-blocking)
            xQueueSendToBack(RTOS_Q_DataAi, &QueueData, 0);

#ifdef DEBUG_LOG_AI
            DebugLog("AiSetCalbCmd: ChNum=%d Cmd=%d Ka=%d Kb=%d [SET]\n", ChNumIn, CmdIn, (uint32_t)PLC_AI[ChNumIn].Ka, (uint32_t)PLC_AI[ChNumIn].Kb);
#endif // DEBUG_LOG_AI

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
uint8_t RTOS_TaskAI_Set(const PlcAI_Set_t *DataIn)
{
    uint8_t Res = BIT_FALSE;
    PlcAI_Set_t SetRes;

    if(DataIn)
    {
/*
#ifdef DEBUG_LOG_AI
        DebugLog("AiSet: ChNum=%d SetID=%d SetVal=%d\n", DataIn->ChNum, DataIn->SetID, (uint32_t)DataIn->SetVal);
#endif // DEBUG_LOG_AI
*/
        switch(DataIn->SetID)
        {
            //Mode
            case PLC_AI_SET_MODE:
                Res = RTOS_TaskAI_SetMode(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                if(Res)
                {
                    SetRes.SetID = PLC_AI_SET_MODE_RES;
                }
                break;

            //Val
            case PLC_AI_SET_VAL:
                Res = RTOS_TaskAI_SetVal(DataIn->ChNum, DataIn->SetVal);
                if(Res)
                {
                    SetRes.SetID = PLC_AI_SET_VAL;
                }
                break;

            //Status
            case PLC_AI_SET_STATUS:
                Res = RTOS_TaskAI_SetStatus(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                if(Res)
                {
                    SetRes.SetID = PLC_AI_SET_STATUS;
                }
                break;

            //CalbLoCmd (command to fix. ADC-code for Lo-level)
            case PLC_AI_SET_CALB_LO_CMD:
                Res = RTOS_TaskAI_SetCalbLoCmd(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                (void)SetRes;
                break;

            //CalbHiCmd (command to fix. ADC-code for Hi-level)
            case PLC_AI_SET_CALB_HI_CMD:
                Res = RTOS_TaskAI_SetCalbHiCmd(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                (void)SetRes;
                break;

            //CalbCmd (command to calculate calibration factors)
            case PLC_AI_SET_CALB_CMD:
                Res = RTOS_TaskAI_SetCalbCmd(DataIn->ChNum, (uint8_t)DataIn->SetVal);
                (void)SetRes;
                break;
        }

        if(Res)
        {
            if(DataIn->SetID == PLC_AI_SET_MODE || DataIn->SetID == PLC_AI_SET_VAL || DataIn->SetID == PLC_AI_SET_STATUS)
            {
                //Send updated Mode, Value, Status to T_Data
                SetRes.ChNum  = DataIn->ChNum;
                SetRes.SetVal = DataIn->SetVal;
                //write Queue (not-blocking)
                xQueueSendToBack(RTOS_Q_DataAi, &SetRes, 0);
            }
        }
    }

    return (Res);
}


/** @brief  Init. AI-channels.
 *  @param  none.
 *  @return none.
 */
void RTOS_TaskAI_Init(void)
{
    uint8_t BuffBy;

#ifdef DEBUG_LOG_AI
    DebugLog("AiInit\n");
#endif // DEBUG_LOG_AI

    for(uint16_t i=0; i<PLC_AI_SZ; i++)
    {
        PLC_AI[i].Pack.ChNum = i;

        //read from REG_t (retain)
        BuffBy = PLC_AI_MODE_DEF;
        REG_CopyRegByPos(REG_AI_MODE__POS+i, REG_COPY_MB_TO_VAR, &BuffBy);
        PLC_AI[i].Pack.Mode = BuffBy;

        PLC_AI[i].Pack.ModeRes = PLC_AI[i].Pack.Mode;
        PLC_AI[i].Pack.Status  = PLC_AI[i].Pack.Mode;
        PLC_AI[i].Val          = PLC_AI_ANA_STATUS_OFF;
        PLC_AI[i].Ka           = PLC_AI_KA_DEF;
        PLC_AI[i].Kb           = PLC_AI_KB_DEF;

#ifdef DEBUG_LOG_AI
        DebugLog("Ai[%d]: Mode=%d Ka=%d Kb=%d\n", i, PLC_AI[i].Pack.Mode, (uint32_t)(PLC_AI[i].Ka*1000000.0), (uint32_t)(PLC_AI[i].Kb*1000000.0));
#endif // DEBUG_LOG_AI
    }
}


/** @brief  Task `AI`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskAI(void *ParamsIn)
{
    //VARIABLES
    PlcAI_Set_t QueueData_Set;
    BaseType_t  QueueStatus;

    //INIT
    (void)ParamsIn; //fix unused

    RTOS_TimAi_Start();

    //START
    for(;;)
    {
        //Read Queue (blocking)
        //get updated settings
        QueueStatus = xQueueReceive(RTOS_Q_AiSet, &QueueData_Set, portMAX_DELAY);
        if(QueueStatus == pdPASS)
        {
            //unpack settings
            RTOS_TaskAI_Set(&QueueData_Set);
        }

        //fast switch to other task
        taskYIELD();
    }
}


/** @brief  Restart TimAi.
 *  @param  PeriodIn - timer period (ms).
 *  @return None.
 */
void RTOS_TimAi_Restart(const uint16_t PeriodIn)
{
    if(PeriodIn)
    {
        xTimerChangePeriod(RTOS_TIM_Ai, (TickType_t)PeriodIn, 0);
        xTimerReset(RTOS_TIM_Ai, 0);
    }
}


/** @brief  Start TimAi.
 *  @param  None.
 *  @return None.
 */
void RTOS_TimAi_Start(void)
{
    if(!PLC_AI_TIM_STATUS)
    {
        RTOS_TimAi_Restart(PLC_AI_SURVEY_PERIOD_MS);
        PLC_AI_TIM_STATUS = BIT_TRUE;

#ifdef DEBUG_LOG_AI
        DebugLog("AiTim: start\n");
#endif // DEBUG_LOG_AI
    }
}


/** @brief  Stop TimAi.
 *  @param  None.
 *  @return None.
 */
void RTOS_TimAi_Stop(void)
{
    if(PLC_AI_TIM_STATUS)
    {
        xTimerStop(RTOS_TIM_Ai, 0);
        PLC_AI_TIM_STATUS = BIT_FALSE;

#ifdef DEBUG_LOG_AI
        DebugLog("AiTim: stop\n");
#endif // DEBUG_LOG_AI
    }
}


/** @brief  TimAi-handler (`Read value`).
 *  @param  None.
 *  @return Quantity of AI-channels with mode 'Survey' (read value).
 */
uint16_t RTOS_TimAi_Read(void)
{
    float    Val;
    uint16_t cAi = 0;
    PlcAI_Set_t QueueSet;

    for(uint16_t i=0; i<PLC_AI_SZ; i++)
    {
        if(PLC_AI[i].Pack.Mode == PLC_AI_MODE_SURVEY)
        {
            Val = ((i != PLC_AI_MCU_TEMP) ? PlcAI_GetAnaLvByChNum(PLC_AI[i].Pack.ChNum, PLC_AI[i].Ka, PLC_AI[i].Kb) : PlcMCUTemp_GetTemp());
            cAi++;

            //Send updated Value to T_AI
            QueueSet.ChNum  = PLC_AI[i].Pack.ChNum;
            QueueSet.SetID  = PLC_AI_SET_VAL;
            QueueSet.SetVal = Val;
            //write Queue (not-blocking)
            xQueueSendToBack(RTOS_Q_AiSet, &QueueSet, 0);
        }
    }

    return (cAi);
}


/** @brief  TimAi-handler.
 *  @param  TimerIn - timer.
 *  @return none.
 */
void RTOS_TimAi(TimerHandle_t TimerIn)
{
    //fix unused
    (void)TimerIn;

    if(RTOS_TimAi_Read())
    {
        //restart timer
        RTOS_TimAi_Restart(PLC_AI_SURVEY_PERIOD_MS);
    }
    else
    {
        //stop timer
        RTOS_TimAi_Stop();
    }
}
