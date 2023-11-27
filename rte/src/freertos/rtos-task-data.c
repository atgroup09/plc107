/* @page rtos-task-data.h
 *       FreeRTOS Task
 *       Data manager
 *       2020-2022
 */

#include "rtos-task-data.h"


#ifdef RTE_MOD_DI

/** @brief  Send DI settings.
 *  @param  RegIn - pointer to register.
 *  @param  SetIdIn  - settings ID.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_DiSet(REG_t *RegIn, const uint8_t SetIdIn)
{
    if(RegIn)
    {
        LWORD_uwt Ut;
        Type_InitWords(Ut.words, TYPE_LWORD_WSZ, 0);

        uint8_t BitVal = BIT_FALSE;

        //Read settings from MB-table
        if(REG_CopyValueFromMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->pMbVar))
        {
            //Send settings to T_DI
            PlcDI_Set_t QueueData_Set;
            QueueData_Set.ChNum  = RegIn->iGroup;
            QueueData_Set.SetID  = SetIdIn;
            QueueData_Set.SetVal = (uint32_t)Ut.data;
            //write Queue (not-blocking)
            xQueueSendToBack(RTOS_Q_DiSet, &QueueData_Set, 0);

            //Send settings (retain) to T_EEPROM
            //RTOS_TaskData_RetainSet(RegIn->EeAreaID, RegIn->EeAddr, RegIn->Type, (double)QueueData_Set.SetVal);

#ifdef DEBUG_LOG_DATA_DI
            DebugLog("DataDiSet: ChNum=%d SetID=%d SetVal=%d\n", QueueData_Set.ChNum, QueueData_Set.SetID, (uint32_t)QueueData_Set.SetVal);
#endif // DEBUG_LOG_DATA_DI

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}

/** @brief  Send DI settings (bit-pack).
 *  @param  RegIn   - pointer to register.
 *  @param  SetIdIn - settings ID.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_DiSetBitPack(REG_t *RegIn, const uint8_t SetIdIn)
{
    if(RegIn)
    {
        LWORD_uwt Ut;
        Type_InitWords(Ut.words, TYPE_LWORD_WSZ, 0);

        uint8_t BitVal = BIT_FALSE;

        if(REG_CopyValueFromMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->pMbVar))
        {
#ifdef DEBUG_LOG_DATA_DI
            DebugLog("DataDiSetBitPack: Pack=%d SetID=%d\n", (uint16_t)Ut.data, SetIdIn);
#endif // DEBUG_LOG_DATA_DI

            PlcDI_Set_t QueueData_Set;
            uint8_t i;

            for(i=0; i<16; i++)
            {
                if(i == PLC_DI_SZ) break;

                BitVal = BIT_GET_VALUE(Ut.data, i);

                QueueData_Set.ChNum  = i;
                QueueData_Set.SetID  = SetIdIn;
                QueueData_Set.SetVal = (uint32_t)BitVal;
                //write Queue (not-blocking)
                xQueueSendToBack(RTOS_Q_DiSet, &QueueData_Set, 0);

                if(BitVal && (SetIdIn == PLC_DI_SET_RESET))
                {
                    //clear command-bit
                    BitVal  = BIT_FALSE;
                    Ut.data = BIT_SET_VALUE(Ut.data, i, BitVal);
                    REG_CopyValueToMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->MbAddr, RegIn->pMbVar, BIT_FALSE);
                }
            }

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}

/** @brief  Unpack DI-channel data.
 *  @param  DataIn - pointer to data.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_Di(const PlcDI_t *DataIn)
{
    if(DataIn)
    {
        if(DataIn->Pack.ChNum < PLC_DI_SZ)
        {
            uint8_t  Buff   = 0;
            uint16_t BuffWo = 0;

            //copy DI-channel data into ModBus Tables

            //Normal value
            Buff = (uint8_t)DataIn->Pack.Val;
            REG_CopyRegByPos((REG_DI_NORM_VAL__POS+DataIn->Pack.ChNum), REG_COPY_VAR_TO_MB__NO_MON, &Buff);
            //read packed values
            REG_CopyRegByPos(REG_SYS_STAT__POS_DI_NORM, REG_COPY_MB_TO_VAR, &BuffWo);
            //update packed value
            BuffWo = BIT_SET_VALUE(BuffWo, DataIn->Pack.ChNum, Buff);
            REG_CopyRegByPos(REG_SYS_STAT__POS_DI_NORM, REG_COPY_VAR_TO_MB__NO_MON, &BuffWo);

            //Mode
            Buff = (uint8_t)DataIn->Pack.Mode;
            REG_CopyRegByPos((REG_DI_MODE__POS+DataIn->Pack.ChNum), REG_COPY_VAR_TO_MB__NO_MON, &Buff);

            //Reset
            Buff = (uint8_t)DataIn->Pack.Reset;
            REG_CopyRegByPos((REG_DI_RESET__POS+DataIn->Pack.ChNum), REG_COPY_VAR_TO_MB__NO_MON, &Buff);
            //read packed values
            //REG_CopyRegByPos(REG_SYS_SET__MBPOS_DI_CNT_RESET, REG_COPY_MB_TO_VAR, &BuffWo);
            //update packed value
            //BuffWo = BIT_SET_VALUE(BuffWo, DataIn->Pack.ChNum, Buff);
            //REG_CopyRegByPos(REG_SYS_SET__MBPOS_DI_CNT_RESET, REG_COPY_VAR_TO_MB__NO_MON, &BuffWo);

            //Counter setpoint reached
            Buff = (uint8_t)DataIn->Pack.CntrSetpointRes;
            REG_CopyRegByPos((REG_DI_CNTR_SETPOINT_RES__POS+DataIn->Pack.ChNum), REG_COPY_VAR_TO_MB__NO_MON, &Buff);
            REG_CopyRegByPos((REG_DI_CNTR_VAL__POS+DataIn->Pack.ChNum), REG_COPY_VAR_TO_MB__NO_MON, (void *)&(DataIn->CntrVal));
            //read packed values
            REG_CopyRegByPos(REG_SYS_STAT__POS_DI_CNT_SP_RES, REG_COPY_MB_TO_VAR, &BuffWo);
            //update packed value
            BuffWo = BIT_SET_VALUE(BuffWo, DataIn->Pack.ChNum, Buff);
            REG_CopyRegByPos(REG_SYS_STAT__POS_DI_CNT_SP_RES, REG_COPY_VAR_TO_MB__NO_MON, &BuffWo);

            //tachometer setpoint reached
            Buff = (uint8_t)DataIn->Pack.TachSetpointRes;
            REG_CopyRegByPos((REG_DI_TACH_SETPOINT_RES__POS+DataIn->Pack.ChNum), REG_COPY_VAR_TO_MB__NO_MON, &Buff);
            REG_CopyRegByPos((REG_DI_TACH_VAL__POS+DataIn->Pack.ChNum), REG_COPY_VAR_TO_MB__NO_MON, (void *)&(DataIn->TachVal));
            //read packed values
            REG_CopyRegByPos(REG_SYS_STAT__POS_DI_TACH_SP_RES, REG_COPY_MB_TO_VAR, &BuffWo);
            //update packed value
            BuffWo = BIT_SET_VALUE(BuffWo, DataIn->Pack.ChNum, Buff);
            REG_CopyRegByPos(REG_SYS_STAT__POS_DI_TACH_SP_RES, REG_COPY_VAR_TO_MB__NO_MON, &BuffWo);

#ifdef DEBUG_LOG_DATA_DI
            DebugLog("DataDi: ChNum=%d Mode=%d Val=%d Reset=%d\0", DataIn->Pack.ChNum, DataIn->Pack.Mode, DataIn->Pack.Val, DataIn->Pack.Reset);
            if(DataIn->Pack.Mode == PLC_DI_MODE_CNTR)
            {
                DebugLog(" CntrVal=%d CntrSetPointAllow=%d(%d)\0", DataIn->CntrVal, DataIn->Pack.CntrSetpointAllow, DataIn->Pack.CntrSetpointRes);
            }
            else if(DataIn->Pack.Mode == PLC_DI_MODE_TACH)
            {
                DebugLog(" TachVal=%d TachSetPointAllow=%d(%d)\0", DataIn->TachVal, DataIn->Pack.TachSetpointAllow, DataIn->Pack.TachSetpointRes);
            }
            DebugLog("\n");
#endif // DEBUG_LOG_DATA_DI

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}

#endif // RTE_MOD_DI


#ifdef RTE_MOD_DO

/** @brief  Send DO settings (INT).
 *  @param  RegIn - pointer to register.
 *  @param  SetIdIn  - settings ID.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_DoSetInt(REG_t *RegIn, const uint8_t SetIdIn)
{
    if(RegIn)
    {
        LWORD_uwt Ut;
        Type_InitWords(Ut.words, TYPE_LWORD_WSZ, 0);

        uint8_t BitVal = BIT_FALSE;

        if(REG_CopyValueFromMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->pMbVar))
        {
            PlcDO_Set_t QueueData_Set;
            QueueData_Set.ChNum  = RegIn->iGroup;
            QueueData_Set.SetID  = SetIdIn;
            QueueData_Set.SetVal = (float)Ut.data;
            //write Queue (not-blocking)
            xQueueSendToBack(RTOS_Q_DoSet, &QueueData_Set, 0);

            //Send settings (retain) to T_EEPROM
            //RTOS_TaskData_RetainSet(RegIn->EeAreaID, RegIn->EeAddr, RegIn->Type, (double)QueueData_Set.SetVal);

#ifdef DEBUG_LOG_DATA_DO
            DebugLog("DataDoSetInt: ChNum=%d SetID=%d SetVal=%d\n", QueueData_Set.ChNum, QueueData_Set.SetID, (uint32_t)QueueData_Set.SetVal);
#endif // DEBUG_LOG_DATA_DO

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}

/** @brief  Send DO settings (REAL).
 *  @param  RegIn - pointer to register.
 *  @param  SetIdIn  - settings ID.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_DoSetReal(REG_t *RegIn, const uint8_t SetIdIn)
{
    if(RegIn)
    {
        FLOAT_uwt Ut;
        Type_InitWords(Ut.words, TYPE_FLOAT_WSZ, 0);

        uint8_t BitVal = BIT_FALSE;

        if(REG_CopyValueFromMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->pMbVar))
        {
            PlcDO_Set_t QueueData_Set;
            QueueData_Set.ChNum  = RegIn->iGroup;
            QueueData_Set.SetID  = SetIdIn;
            QueueData_Set.SetVal = Ut.data;
            //write Queue (not-blocking)
            xQueueSendToBack(RTOS_Q_DoSet, &QueueData_Set, 0);

            //Send settings (retain) to T_EEPROM
            //RTOS_TaskData_RetainSet(RegIn->EeAreaID, RegIn->EeAddr, RegIn->Type, (double)QueueData_Set.SetVal);

#ifdef DEBUG_LOG_DATA_DO
            DebugLog("DataDoSetReal: ChNum=%d SetID=%d SetVal=%d\n", QueueData_Set.ChNum, QueueData_Set.SetID, (uint32_t)QueueData_Set.SetVal);
#endif // DEBUG_LOG_DATA_DO

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}

/** @brief  Send DO settings (bit-pack).
 *  @param  RegIn   - pointer to register.
 *  @param  SetIdIn - settings ID.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_DoSetBitPack(REG_t *RegIn, const uint8_t SetIdIn)
{
    if(RegIn)
    {
        LWORD_uwt Ut;
        Type_InitWords(Ut.words, TYPE_LWORD_WSZ, 0);

        uint8_t BitVal = BIT_FALSE;

        if(REG_CopyValueFromMb(RegIn->Type, &BitVal, Ut.words, RegIn->MbTable, RegIn->pMbVar))
        {
#ifdef DEBUG_LOG_DATA_DO
            DebugLog("DataDoSetBitPack: Pack=%d SetID=%d\n", (uint16_t)Ut.data, SetIdIn);
#endif // DEBUG_LOG_DATA_DO

            PlcDO_Set_t QueueData_Set;
            uint8_t i;

            for(i=0; i<16; i++)
            {
                if(i == PLC_DO_SZ) break;

                QueueData_Set.ChNum  = i;
                QueueData_Set.SetID  = SetIdIn;
                QueueData_Set.SetVal = (float)BIT_GET_VALUE(Ut.data, i);
                //write Queue (not-blocking)
                xQueueSendToBack(RTOS_Q_DoSet, &QueueData_Set, 0);
            }

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}

/** @brief  Unpack DO-channel data.
 *  @param  DataIn - pointer to data.
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_Do(const PlcDO_Set_t *DataIn)
{
    if(DataIn)
    {
        if(DataIn->ChNum < PLC_DO_SZ)
        {
            uint8_t Buff;

            //copy DO-channel data into ModBus Tables
            switch(DataIn->SetID)
            {
                default:
                    (void)Buff; //fix unused
            }

#ifdef DEBUG_LOG_DATA_DO
            DebugLog("DataDo: ChNum=%d SetID=%d SetVal=%d\n", DataIn->ChNum, DataIn->SetID, (uint32_t)DataIn->SetVal);
#endif // DEBUG_LOG_DATA_DO

            return (BIT_TRUE);
        }
    }

    return (BIT_FALSE);
}

#endif // RTE_MOD_DO


#ifdef RTE_MOD_REG_MONITOR

/** @brief  Unpack updated register.
 *  @param  IDxIn - register IDx (position in REGS).
 *  @return Result:
 *  @arg      = 0 - no
 *  @arg      = 1 - done
 */
uint8_t RTOS_TaskData_RegMonitor(const uint16_t IDxIn)
{
    uint8_t Res = BIT_FALSE;

    REG_t *Reg = REG_GetByIDx(IDxIn);

    if(Reg)
    {
#ifdef DEBUG_LOG_DATA_REG
        DebugLog("DataReg: IDx=%d Reg.GID=%d\n", IDxIn, Reg->GID);
#endif // DEBUG_LOG_DATA_REG

        switch(Reg->GID)
        {
#ifdef RTE_MOD_DI
            case REG_DI_MODE__GID:
                //retain
                Res = RTOS_TaskData_DiSet(Reg, PLC_DI_SET_MODE);
                break;

            case REG_DI_RESET__GID:
                Res = RTOS_TaskData_DiSet(Reg, PLC_DI_SET_RESET);
                break;

            case REG_DI_TACH_SETPOINT__GID:
                //retain
                Res = RTOS_TaskData_DiSet(Reg, PLC_DI_SET_TACH_SETPOINT);
                break;

            case REG_DI_TACH_SETPOINT_ALLOW__GID:
                //retain
                Res = RTOS_TaskData_DiSet(Reg, PLC_DI_SET_TACH_SETPOINT_ALLOW);
                break;

            case REG_DI_CNTR_SETPOINT__GID:
                //retain
                Res = RTOS_TaskData_DiSet(Reg, PLC_DI_SET_CNTR_SETPOINT);
                break;

            case REG_DI_CNTR_SETPOINT_ALLOW__GID:
                //retain
                Res = RTOS_TaskData_DiSet(Reg, PLC_DI_SET_CNTR_SETPOINT_ALLOW);
                break;
#endif // RTE_MOD_DI

#ifdef RTE_MOD_DO
            case REG_DO_NORM_VAL__GID:
                Res = RTOS_TaskData_DoSetInt(Reg, PLC_DO_SET_NORM_VAL);
                break;

            case REG_DO_FAST_VAL__GID:
                Res = RTOS_TaskData_DoSetInt(Reg, PLC_DO_SET_FAST_VAL);
                break;

            case REG_DO_PWM_VAL__GID:
                Res = RTOS_TaskData_DoSetReal(Reg, PLC_DO_SET_PWM_FILL_FACTOR);
                break;

            case REG_DO_PWM_ALLOW__GID:
                Res = RTOS_TaskData_DoSetInt(Reg, PLC_DO_SET_PWM_ALLOW);
                break;

            case REG_DO_PWM_PERIOD__GID:
                //retain
                Res = RTOS_TaskData_DoSetInt(Reg, PLC_DO_SET_PWM_PERIOD);
                break;

            case REG_DO_MODE__GID:
                //retain
                Res = RTOS_TaskData_DoSetInt(Reg, PLC_DO_SET_MODE);
                break;

            case REG_DO_SAFE_ALLOW__GID:
                //retain
                Res = RTOS_TaskData_DoSetInt(Reg, PLC_DO_SET_SAFE_ALLOW);
                break;

            case REG_DO_SAFE_VAL__GID:
                //retain
                Res = RTOS_TaskData_DoSetInt(Reg, PLC_DO_SET_SAFE_VAL);
                break;
#endif // RTE_MOD_DO

            default:
                (void)IDxIn;
        }
    }

    return (Res);
}

#endif // RTE_MOD_REG_MONITOR


/** @brief  Task `Data manager`.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return none.
 *  @details The task is blocked - wait for data in Queue.
 */
void RTOS_TaskData(void *ParamsIn)
{
    //VARIABLES

#ifdef RTE_MOD_DI
    PlcDI_t    QueueData_Di;
    BaseType_t QueueStatus_Di;
#endif // RTE_MOD_DI

#ifdef RTE_MOD_DO
    PlcDO_Set_t QueueData_Do;
    BaseType_t  QueueStatus_Do;
#endif // RTE_MOD_DO

#ifdef RTE_MOD_REG_MONITOR
    uint16_t    QueueData_RegMonitor;
    BaseType_t  QueueStatus_Reg;
#endif // RTE_MOD_REG_MONITOR

    //INIT
    (void)ParamsIn; //fix unused

    //START
    for(;;)
    {
#ifdef RTE_MOD_DI
        //Read Queue (not-blocking)
        //get updated DI-channel data
        QueueStatus_Di = xQueueReceive(RTOS_Q_DataDi, &QueueData_Di, 0);
        if(QueueStatus_Di == pdPASS)
        {
            //LOCK
            xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);
            //unpack DI-channel data
            RTOS_TaskData_Di(&QueueData_Di);
            xSemaphoreGive(RTOS_MTX_MbTables);
            //UNLOCK
        }
#endif // RTE_MOD_DI

#ifdef RTE_MOD_DO
        //Read Queue (not-blocking)
        //get updated DO-channel data
        QueueStatus_Do = xQueueReceive(RTOS_Q_DataDo, &QueueData_Do, 0);
        if(QueueStatus_Do == pdPASS)
        {
            //LOCK
            xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);
            //unpack DO-channel data
            RTOS_TaskData_Do(&QueueData_Do);
            xSemaphoreGive(RTOS_MTX_MbTables);
            //UNLOCK
        }
#endif // RTE_MOD_DO

#ifdef RTE_MOD_REG_MONITOR
        //Read Queue (not-blocking)
        //get updated register
        QueueStatus_Reg = xQueueReceive(RTOS_Q_DataRegMonitor, &QueueData_RegMonitor, 0);
        if(QueueStatus_Reg == pdPASS)
        {
            //LOCK
            xSemaphoreTake(RTOS_MTX_MbTables, portMAX_DELAY);
            //unpack updated register
            RTOS_TaskData_RegMonitor(QueueData_RegMonitor);
            xSemaphoreGive(RTOS_MTX_MbTables);
            //UNLOCK
        }
#endif // RTE_MOD_REG_MONITOR

        //fast switch to other task
        taskYIELD();
    }
}
