/* @page delay.c
 *       Delay functions
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020
 */

#include "delay.h"


//Init. status
static uint8_t PlcDelay_Inited = 0;

//For store tick counts in us
static volatile uint32_t PlcDelay_usTicks = 0;


/** @brief   Init. Delay.
 *  @param   none.
 *  @return  none.
 */
void DelayInit(void)
{
    if(!PlcDelay_Inited)
    {
#ifdef DELAY_SYSTICK
        // Update SystemCoreClock value
        SystemCoreClockUpdate();
        // Configure the SysTick timer to overflow every 1 us
        SysTick_Config(SystemCoreClock/1000000);
#endif // DELAY_SYSTICK
        PlcDelay_Inited = 1;
    }
}


/** @brief   Delay in microseconds.
 *  @param   UsIn - microseconds (16-bit value).
 *  @return  none.
 */
void DelayUs(const uint16_t UsIn)
{
    PlcDelay_usTicks = UsIn;

#ifndef DELAY_SYSTICK
    DelayTim_Start();
#endif // DELAY_SYSTICK

    // Wait until usTick reach zero
    while(PlcDelay_usTicks);

#ifndef DELAY_SYSTICK
    DelayTim_Stop();
#endif // DELAY_SYSTICK
}


/** @brief   Delay in milliseconds.
 *  @param   MsIn - milliseconds (16-bit value).
 *  @return  none.
 */
void DelayMs(const uint16_t MsIn)
{
    PlcDelay_usTicks = MsIn;

    DelayTim_Start();

    // Wait until usTick reach zero
    while(PlcDelay_usTicks);

    DelayTim_Stop();
/*
    uint16_t Ms = MsIn;

    while(Ms--)
    {
        //Delay 1ms == 1000us
        DelayUs((uint16_t)1000);
    }
*/
}


/** @brief   Delay in seconds.
 *  @param   SecIn - seconds (16-bit value).
 *  @return  none.
 */
void DelaySec(const uint16_t SecIn)
{
    uint16_t Sec = SecIn;

    while(Sec--)
    {
        //Delay 1s == 1000ms
        DelayMs((uint16_t)1000);
    }
}


/** @brief  Delay TIM start.
 *  @param  none.
 *  @return none.
 */
void DelayTim_Start(void)
{
    TIM_SetCounter(DELAY_TIM, (uint32_t)0);
    TIM_ITConfig(DELAY_TIM, TIM_IT_Update, ENABLE); //TIM_DIER_UIE
    TIM_Cmd(DELAY_TIM, ENABLE);
}


/** @brief  Delay TIM stop.
 *  @param  none.
 *  @return none.
 */
void DelayTim_Stop(void)
{
    TIM_Cmd(DELAY_TIM, DISABLE);
    TIM_ITConfig(DELAY_TIM, TIM_IT_Update, DISABLE); //TIM_DIER_UIE
    TIM_SetCounter(DELAY_TIM, (uint32_t)0);
}


#ifdef DELAY_SYSTICK
/** @brief  SysTick interrupts handler.
 *  @param  none.
 *  @return none.
 */
void SysTick_Handler()
{
    if(PlcDelay_usTicks != 0) PlcDelay_usTicks--;
}
#else
/** @brief  TIM interrupts handler.
 *  @param  none.
 *  @return none.
 */
void DELAY_TIM_IRQ(void)
{
    if(TIM_GetITStatus(DELAY_TIM, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(DELAY_TIM, TIM_IT_Update);
        if(PlcDelay_usTicks != 0) PlcDelay_usTicks--;
    }
}
#endif // DELAY_TIM
