/* @page sysclock.h
 *       SysClock initialization
 *       platform-dependent code
 *       stm32f10x, SPL
 *       2020-2022
 */

/** SysClock configure
 *
 *  HSE[25] > Prediv2[/5] > PLL2Mul[x8] > Prediv1 Source Mux[PLL2] > Prediv1[/5] >
 *          > PLL Source Mux[Prediv1] > PLLMul[x9] >
 *          > System Clock Mux[PLLCLK](72) >
 *          > AHB Prescaler[/1] >
 *          > APB1 Prescaler[/2](PCLK1 36, TCLK1 72)
 *          > APB2 Prescaler[/1](PCLK2 72, TCLK2 72)
 */

#ifndef PLC_SYSCLOCK_H
#define PLC_SYSCLOCK_H

#include "config.h"


/** @def SysClock defines
 */
#define PLC_F_CPU                      72000000UL

#define PLC_HSE_FREQ                   (uint32_t)(25*MHZ_BASE)   //HSE    25 MHz
#define PLC_SYSCLK_FREQ                (uint32_t)(72*MHZ_BASE)   //SYSCLK 72 MHz
#define PLC_HCLK_FREQ                  (uint32_t)(72*MHZ_BASE)   //HCLK   72 MHz
#define PLC_AHB_FREQ                   PLC_HCLK_FREQ             //AHB    72 MHz
#define PLC_APB1_PCLK_FREQ             (uint32_t)(36*MHZ_BASE)   //APB1 Peripheral clocks  36 MHz
#define PLC_APB1_TCLK_FREQ             (uint32_t)(72*MHZ_BASE)   //APB1 Timer clocks       72 MHz
#define PLC_APB2_PCLK_FREQ             (uint32_t)(72*MHZ_BASE)   //APB2 Peripheral clocks  72 MHz
#define PLC_APB2_TCLK_FREQ             (uint32_t)(72*MHZ_BASE)   //APB2 Timer clocks       72 MHz


/** @brief   SysClock initialization.
 *  @param   none.
 *  @return  none.
 */
void PlcSysClock_Init(void);


#endif //PLC_SYSCLOCK_H
