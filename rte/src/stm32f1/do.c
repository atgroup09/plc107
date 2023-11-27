/* @page do.h
 *       Discrete Outputs
 *       platform-dependent code
 *       stm32f1xx, SPL
 *       2020-2022
 */

#include "do.h"


uint8_t PLC_DO_POSTPONED;


/** @brief  Init. DO.
 *  @param  none.
 *  @return none.
 */
void PlcDO_Init(void)
{
    GPIO_InitTypeDef PortDef;

    //Enable clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);

	//Configure GPIO
	// GPIOE
    GPIO_StructInit(&PortDef);
    PortDef.GPIO_Pin   = (GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14);
    PortDef.GPIO_Mode  = GPIO_Mode_Out_PP;
    PortDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &PortDef);
}


/** @brief DO on.
 *  @param  PortIn - port;
 *  @param  PinIn - pin number;
 *  @param  PinModeIn - pin mode:
 *  @arg      = 0 - push-pull,
 *  @arg      = 1 - open-drain.
 *  @return none.
 */
void PlcDO_On(GPIO_TypeDef *PortIn, const uint16_t PinIn, const uint8_t PinModeIn)
{
    if(PortIn)
    {
        if(PinModeIn)
        {
            GPIO_ResetBits(PortIn, PinIn);
        }
        else
        {
            GPIO_SetBits(PortIn, PinIn);
        }
    }
}


/** @brief DO off.
 *  @param  PortIn - port;
 *  @param  PinIn - pin number;
 *  @param  PinModeIn - pin mode:
 *  @arg      = 0 - push-pull,
 *  @arg      = 1 - open-drain.
 *  @return none.
 */
void PlcDO_Off(GPIO_TypeDef *PortIn, const uint16_t PinIn, const uint8_t PinModeIn)
{
    if(PortIn)
    {
        if(PinModeIn)
        {
            GPIO_SetBits(PortIn, PinIn);
        }
        else
        {
            GPIO_ResetBits(PortIn, PinIn);
        }
    }
}


/** @brief DO toggle.
 *  @param  PortIn - port;
 *  @param  PinIn - pin number;
 *  @param  PinModeIn - pin mode:
 *  @arg      = 0 - push-pull,
 *  @arg      = 1 - open-drain.
 *  @return Current Pin-status:
 *  @arg      = 0 - off,
 *  @arg      = 1 - on.
 */
uint8_t PlcDO_Toggle(GPIO_TypeDef *PortIn, const uint16_t PinIn, const uint8_t PinModeIn)
{
    if(PortIn)
    {
        uint8_t Bit = GPIO_ReadOutputDataBit(PortIn, PinIn);

        if(PinModeIn) Bit = !Bit;
        if(!Bit)
        {
            PlcDO_On(PortIn, PinIn, PinModeIn);
            return (1);
        }
        else
        {
            PlcDO_Off(PortIn, PinIn, PinModeIn);
        }
    }
    return (0);
}


/** @brief  Set DO state.
 *  @param  PortIn - port;
 *  @param  PinIn - pin number;
 *  @param  PinModeIn - pin mode:
 *  @arg      = 0 - push-pull,
 *  @arg      = 1 - open-drain.
 *  @param  StateIn - state:
 *  @arg      = 0 - off,
 *  @arg      = 1 - on.
 *  @return none.
 */
void PlcDO_Set(GPIO_TypeDef *PortIn, const uint16_t PinIn, const uint8_t PinModeIn, const uint8_t StateIn)
{
    if(PortIn)
    {
        if(StateIn)
        {
            PlcDO_On(PortIn, PinIn, PinModeIn);
        }
        else
        {
            PlcDO_Off(PortIn, PinIn, PinModeIn);
        }
    }
}
