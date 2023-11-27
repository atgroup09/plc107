/* @page sysclock.c
 *       SysClock initialization
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020-2022
 */

#include "sysclock.h"


/** @brief   SysClock initialization.
 *  @param   none.
 *  @return  none.
 */
void PlcSysClock_Init(void)
{
    //Disable PLL2
    RCC_PLL2Cmd(DISABLE);

    //Disable PLL
    RCC_PLLCmd(DISABLE);

    //Reset RCC
	RCC_DeInit();

    //Prediv2
    RCC_PREDIV2Config(RCC_PREDIV2_Div5);

    //PLL2Mul
    RCC_PLL2Config(RCC_PLL2Mul_8);

    //Prediv1 Source Mux
    //Prediv1
    RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);

    //PLL Source Mux
    //PLLMul
    RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);

    //AHB Prescaler
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    //APB1 Prescaler
    RCC_PCLK1Config(RCC_HCLK_Div2);

    //APB2 Prescaler
    RCC_PCLK2Config(RCC_HCLK_Div1);

	//Enable HSE
    RCC_HSEConfig(RCC_HSE_ON);
    //wait
    if(RCC_WaitForHSEStartUp() == SUCCESS)
    {
        //FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        //FLASH_SetLatency(FLASH_Latency_2);

        //Enable PLL2
        RCC_PLL2Cmd(ENABLE);
        //wait
        while(RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET);

        //Enable PLL
        RCC_PLLCmd(ENABLE);
        //wait
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);;

        //System Clock Mux
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        //wait
        while(RCC_GetSYSCLKSource() != 0x08);
    }
    else
    {
        //HSE error
        while(1);
    }
}
