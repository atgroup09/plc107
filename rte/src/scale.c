/* @page scale.c
 *       Scale functions
 *       2020, lamsystems-it.ru
 */

#include "scale.h"


/** @brief  Scale analog-values.
 *  @param  In   - input-value.
 *  @param  KaIn - scale Ka-factor.
 *  @param  KbIn - scale Kb-factor.
 *  @return Scaled value.
 *  @note
 *          Result = KaIn*In + KbIn
 */
inline float ScaleA(const float In, const float KaIn, const float KbIn)
{
    return ((In*KaIn)+KbIn);
}


/** @brief  Calculate scale Ka-factor.
 *  @param  Y1In - low  scaled value.
 *  @param  Y2In - high scaled value.
 *  @param  In1  - low  input value.
 *  @param  In2  - high input value.
 *  @return Scale Ka-factor.
 *  @note
 *          Ka = (Y2In - Y1In)/(In2 - In1)
 */
float ScaleA_Ka(const float Y1In, const float Y2In, const float In1, const float In2)
{
    float In = (In2 - In1);
    return ((In > 0.0) ? ((Y2In - Y1In)/In) : (float)0.0);
}


/** @brief  Calculate scale Kb-factor.
 *  @param  Y1In - low  scaled value.
 *  @param  Y2In - high scaled value.
 *  @param  In1  - low  input value.
 *  @param  In2  - high input value.
 *  @return Scale Kb-factor.
 *  @note
 *          Kb = (Y1In*In2 - Y2In*In1)/(In2 - In1)
 */
float ScaleA_Kb(const float Y1In, const float Y2In, const float In1, const float In2)
{
    float In = (In2 - In1);
    return ((In > 0.0) ? (((Y1In*In2) - (Y2In*In1))/In) : (float)0.0);
}
