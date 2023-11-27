/*	JAVASCRIPT DOCUMENT
*	UTF-8
*/

/*  WebHMI client
*   SCADA / PLC107
*
*   UI
*
*   Copyright (C) 2022  AT09 (atgroup09@gmail.com)
*
*   The JavaScript code in this page is free software: you can
*   redistribute it and/or modify it under the terms of the GNU
*   General Public License (GNU GPL) as published by the Free Software
*   Foundation, either version 3 of the License, or (at your option)
*   any later version.  The code is distributed WITHOUT ANY WARRANTY;
*   without even the implied warranty of MERCHANTABILITY or FITNESS
*   FOR A PARTICULAR PURPOSE.  See the GNU GPL for more details.
*
*   As additional permission under GNU GPL version 3 section 7, you
*   may distribute non-source (e.g., minimized or compacted) forms of
*   that code without the copy of the GNU GPL normally required by
*   section 4, provided you include this license notice and a URL
*   through which recipients can access the Corresponding Source.
*/

/** Dependencies:
 *    + mod/ui-hmi-v2.min.js
 *    + mod/ui-hmi-v2.min.css
 */

/*
@brief  Inititialize UI.
@param  None.
@return None.
*/
function Main_InitUI()
{
	if(typeof initUI == "function")
	{
		var WsUri = "ws://192.168.1.100:8100";
		var WsID  = "wsSCADA";

		var Opts = {  DI0: { DataKey:"DI0", BoolNum:true, Type:"BitLamp" },
                      DI1: { DataKey:"DI1", BoolNum:true, Type:"BitLamp" },
                      DI2: { DataKey:"DI2", BoolNum:true, Type:"BitLamp" },
                      DI3: { DataKey:"DI3", BoolNum:true, Type:"BitLamp" },
                      DO0: { DataKey:"DO0", BoolNum:true, Type:"BitLamp" },
                      DO1: { DataKey:"DO1", BoolNum:true, Type:"BitLamp" },
                      DO2: { DataKey:"DO2", BoolNum:true, Type:"BitLamp" },
                      DO3: { DataKey:"DO3", BoolNum:true, Type:"BitLamp" },
                      App: { DataKey:"STAT1", Bit:0,  BoolNum:true, Type:"BitLamp" },
                      Run: { DataKey:"HW_CODE", BoolNum:true, Type:"BitLampBlink" },
                      Pwr: { DataKey:"HW_CODE", BoolNum:true, Type:"BitLamp" },
                      HW_CODE: { DataKey:"HW_CODE", Type:"Number" },
                       HW_VAR: { DataKey:"HW_VAR", Type:"Number" },
                      RTE_VER: { DataKey:"RTE_VER", Type:"Number" },
                     RTE_YEAR: { DataKey:"RTE_YEAR", Type:"Number" }
				   };

		initUI(WsUri, WsID, Opts);
	}
}
