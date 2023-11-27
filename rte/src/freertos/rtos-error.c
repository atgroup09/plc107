/* @page rtos-error.c
 *       FreeRTOS Error
 *       defines and handlers
 *       2020, lamsystems-it.ru
 */

#include "rtos-error.h"


/** @var RTOS Error fixed (flag)
 *  @arg  = 0 - not fixed
 *  @arg  = 1 - fixed
 */
static uint8_t RTOS_ERR_FIXED = 0;


/** @brief  Handler of error init. RTOS.
 *  @param  ErrIn      - error code.
 *  @param  TargetIdIn - ID of target (task, queue, mutex, ...).
 *  @return none.
 */
void RTOS_Error(const uint8_t ErrIn, const uint8_t TargetIdIn)
{
    for(;;)
    {
        if(RTOS_ERR_FIXED == 0)
        {
#ifdef DEBUG
            switch(ErrIn)
            {
                case RTOS_ERROR_CREATE_QUEUE:
                    DebugLog("RTOS Error! Queue(%d).\n", TargetIdIn);
                    break;

                case RTOS_ERROR_CREATE_MUTEX:
                    DebugLog("RTOS Error! Mutex(%d).\n", TargetIdIn);
                    break;

                case RTOS_ERROR_CREATE_SEMAPHORE:
                    DebugLog("RTOS Error! Semaphore(%d).\n", TargetIdIn);
                    break;

                case RTOS_ERROR_CREATE_TASK:
                    DebugLog("RTOS Error! Task(%d).\n", TargetIdIn);
                    break;

                case RTOS_ERROR_CREATE_TIMER:
                    DebugLog("RTOS Error! Timer(%d).\n", TargetIdIn);
                    break;

                case RTOS_ERROR_START_SCHED:
                    (void)TargetIdIn;
                    DebugLog("RTOS Error! Scheduler doesn't start.\n");
                    break;

                case RTOS_MODE_DEFAULTS:
                    (void)TargetIdIn;
                    DebugLog("Mode 'Defaults'! Scheduler doesn't start.\n");
                    break;

                default:
                    DebugLog("RTOS Error! (%d).\n", TargetIdIn);
            }
#endif // DEBUG
            RTOS_ERR_FIXED = 1;
        }
    }
}
