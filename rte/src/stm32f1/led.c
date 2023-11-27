/* @page led.c
 *       LED Driver
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#include "led.h"


/** @brief  LED initialization.
 *  @param  none.
 *  @return none.
 */
void PlcLed_Init(void)
{
    GPIO_InitTypeDef PortDef;

    //Enable clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	//GPIO configuration
	GPIO_StructInit(&PortDef);
    PortDef.GPIO_Pin   = GPIO_Pin_15;
    PortDef.GPIO_Mode  = GPIO_Mode_Out_PP;
    PortDef.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOE, &PortDef);
}
