/* @page app.c
 *       Application functions
 *       2020-2022
 */

#include "app.h"


/** @brief  Init. Application functions.
 *  @param  None.
 *  @return None.
 */
void PlcApp_InitFuncs(void)
{
    if(PLC_APP_CURR)
    {
        if(PLC_APP_CURR->funcs)
        {
#ifdef RTE_MOD_DI
            PLC_APP_CURR->funcs->DIMode    = PlcApp_DIMode;
            PLC_APP_CURR->funcs->DIVal     = PlcApp_DIVal;
            PLC_APP_CURR->funcs->DICntT    = PlcApp_DICntT;
            PLC_APP_CURR->funcs->DICnt     = PlcApp_DICnt;
            PLC_APP_CURR->funcs->DICntRst  = PlcApp_DICntRst;
            PLC_APP_CURR->funcs->DIEnc     = PlcApp_DIEnc;
#endif // RTE_MOD_DI

#ifdef RTE_MOD_DO
            PLC_APP_CURR->funcs->DOMode    = PlcApp_DOMode;
            PLC_APP_CURR->funcs->DOVal     = PlcApp_DOVal;
            PLC_APP_CURR->funcs->DOFast    = PlcApp_DOFast;
            PLC_APP_CURR->funcs->DOPwm     = PlcApp_DOPwm;
            PLC_APP_CURR->funcs->DOSafe    = PlcApp_DOSafe;
#endif // RTE_MOD_DO

#ifdef RTE_MOD_AI
            PLC_APP_CURR->funcs->AIMode    = PlcApp_AIMode;
            PLC_APP_CURR->funcs->AIVal     = PlcApp_AIVal;
#endif // RTE_MOD_AI

#ifdef RTE_MOD_AO
            PLC_APP_CURR->funcs->AOMode    = PlcApp_AOMode;
            PLC_APP_CURR->funcs->AOVal     = PlcApp_AOVal;
            PLC_APP_CURR->funcs->AOFast    = PlcApp_AOFast;
            PLC_APP_CURR->funcs->AOSafe    = PlcApp_AOSafe;
#endif // RTE_MOD_AO

#ifdef RTE_MOD_SOFT_RESET
            PLC_APP_CURR->funcs->SoftReset = PlcApp_SoftwareReset;
#endif // RTE_MOD_SOFT_RESET

            PLC_APP_CURR->funcs->GetTime   = PlcApp_GetTime;
        }
    }
}

#ifdef RTE_MOD_SOFT_RESET
/** @brief  Get SysTime.
 *  @param  None.
 *  @return None.
 */
void PlcApp_GetTime(IEC_TIME *CurrentTimeIn)
{
    if(CurrentTimeIn)
    {
        //1 tick of  plc_sys_timer == 1 msec

        //part of seconds from plc_sys_timer
        CurrentTimeIn->tv_sec  = (long int)(plc_sys_timer/1000);
        //part of nanoseconds from plc_sys_timer
        CurrentTimeIn->tv_nsec = (long int)((plc_sys_timer-(CurrentTimeIn->tv_sec*1000))*1000000);
    }
}
#endif // RTE_MOD_SOFT_RESET
