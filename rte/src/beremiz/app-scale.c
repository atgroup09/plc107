/* @page app-scale.h
 *       Application functions / Scale
 *       2020-2022
 */

#include "app-scale.h"


void PlcApp_ScaleA_Ka(BOOL *Ex, REAL *In1, REAL *In2, REAL *Y1, REAL *Y2, REAL *Ka, REAL *OKa)
{
    if(Ex && In1 && In2 && Y1 && Y2 && Ka && OKa)
    {
        *OKa = ((*Ex) ? ScaleA_Ka(*Y1, *Y2, *In1, *In2) : *Ka);
    }
}


void PlcApp_ScaleA_Kb(BOOL *Ex, REAL *In1, REAL *In2, REAL *Y1, REAL *Y2, REAL *Kb, REAL *OKb)
{
    if(Ex && In1 && In2 && Y1 && Y2 && Kb && OKb)
    {
        *OKb = ((*Ex) ? ScaleA_Kb(*Y1, *Y2, *In1, *In2) : *Kb);
    }
}


void PlcApp_ScaleA(BOOL *Ex, REAL *In, REAL *Ka, REAL *Kb, REAL *Oy)
{
    if(Ex && In && Ka && Kb && Oy)
    {
        *Oy = ((*Ex) ? ScaleA(*In, *Ka, *Kb) : 0.0);
    }
}
