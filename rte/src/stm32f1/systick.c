/* @page systick.c
 *       SysTick initialization
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020-2022
 */

#include "systick.h"


/** @brief   SysTick initialization.
 *  @param   none.
 *  @return  none.
 */
void PlcSysTick_Init(void)
{
    //Update SystemCoreClock value
    SystemCoreClockUpdate();
    //Configure the SysTick timer to overflow every 1 us
    SysTick_Config(SystemCoreClock / PLC_SYSTICK_FREQ_HZ);
}


/** @brief   SysTick interrupt hadler.
 *  @param   none.
 *  @return  none.
 */
/*
void sys_tick_handler(void)
{

}
*/
