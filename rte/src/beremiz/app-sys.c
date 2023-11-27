/* @page app-sys.h
 *       Application functions / System
 *       2020-2022
 */

#include "app-sys.h"


void PlcApp_SoftwareReset(BOOL Ex)
{
    if(Ex) Plc_SoftwareReset();
}
