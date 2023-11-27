/* @page scale.h
 *       Scale functions
 *       2020, lamsystems-it.ru
 */

#ifndef SCALE_H_
#define SCALE_H_

#include <stdint.h>


/** @brief  Scale analog-values.
 *  @param  In   - input-value (ADC code).
 *  @param  KaIn - scale Ka-factor.
 *  @param  KbIn - scale Kb-factor.
 *  @return Scaled value.
 *  @note
 *          Y = KaIn*In + KbIn
 */
float ScaleA(const float In, const float KaIn, const float KbIn);


/** @brief  Calculate scale Ka-factor.
 *  @param  Y1In - low  scaled value (C*, Pa, ...).
 *  @param  Y2In - high scaled value (C*, Pa, ...).
 *  @param  In1  - low  input value  (ADC code).
 *  @param  In2  - high input value  (ADC code).
 *  @return Scale Ka-factor.
 *  @note
 *          Ka = (Y2In - Y1In)/(In2 - In1)
 */
float ScaleA_Ka(const float Y1In, const float Y2In, const float In1, const float In2);


/** @brief  Calculate scale Kb-factor.
 *  @param  Y1In - low  scaled value (C*, Pa, ...).
 *  @param  Y2In - high scaled value (C*, Pa, ...).
 *  @param  In1  - low  input value  (ADC code).
 *  @param  In2  - high input value  (ADC code).
 *  @return Scale Kb-factor.
 *  @note
 *          Kb = (Y1In*In2 - Y2In*In1)/(In2 - In1)
 */
float ScaleA_Kb(const float Y1In, const float Y2In, const float In1, const float In2);


#endif /* SCALE_H_ */
