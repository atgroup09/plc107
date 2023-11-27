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

 /* Rx-example:
  * {"ID":"wsSCADA", "Networks":[{"ID":1, "Devices":[{"ID":1, "BaseAddr":1, "Class":"plc107", "LT1":1, "LT2":0, "LT3":0, "LTSet":2, "LTErr":1, "PLC":234, "HS1":1, "P1Cmd":1, "P1Spd1":1, "P1Spd2":0 }]}], "Stamp":1546508489 }
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

		var Opts = {  LT1: { DataKey:"DI0", Type:"BitLamp", Func:onBitFuncWsLog, RiseEdge:true, BoolNum:true },
                     LT1w: { DataKey:"DI0", Type:"BitLamp" },
                      LT2: { DataKey:"DI1", Type:"BitLamp", Func:onBitFuncWsLog, RiseEdge:true, BoolNum:true },
                     LT2w: { DataKey:"DI1", Type:"BitLamp" },
                      LT3: { DataKey:"DI2", Type:"BitLamp", Func:onBitFuncWsLog, RiseEdge:true, BoolNum:true },
                     LT3w: { DataKey:"DI2", Type:"BitLamp" },
                    LTSet: { DataKey:"LT_SET", Type:"ArrayIDx", Arr:G_RES[G_LANG]["Set"], NodeID:"LTSet", BoolNum:true },
                   LTSet0: { DataKey:"LT_SET", Setpoint:0, Type:"BitLamp", NodeID:"LTSet0", BoolNum:true },
                   LTSet1: { DataKey:"LT_SET", Setpoint:1, Type:"BitLamp", NodeID:"LTSet1", BoolNum:true },
                 LTSetLog: { DataKey:"LT_SET", Type:"Func", NodeID:"LTSet", Func:onBitFuncWsLog, RiseEdge:true, BoolNum:true },
                    LTErr: { DataKey:"LT_ERR", Type:"ArrayIDx", Arr:G_RES[G_LANG]["St"], NodeID:"LTErr", BoolNum:true },
               LTErrColor: { DataKey:"LT_ERR", Type:"ArrayIDx", Arr:G_RES[G_LANG]["StRed"], NodeID:"LTErr", NodeAttr:"class", DefaultValue:"", BoolNum:true },
                 LTErrBlb: { DataKey:"LT_ERR", Type:"BitLampBlink", NodeID:"LTErr0", Func:onBitFuncWsRedLog2, RiseEdge:true, BoolNum:true },
                      PLC: { DataKey:"PLC", Type:"Text" },
                      HS1: { DataKey:"DI3", Type:"ArrayIDx", Arr:G_RES[G_LANG]["HS"], NodeID:"HS1", BoolNum:true },
                 HS1Color: { DataKey:"DI3", Type:"ArrayIDx", Arr:G_RES[G_LANG]["StGreen"], NodeID:"HS1", NodeAttr:"class", DefaultValue:"", BoolNum:true },
                   HS1Log: { DataKey:"DI3", Type:"Func", NodeID:"HS1", Func:onBitFuncWsGreenLog2, RiseEdge:true, BoolNum:true },
                       P1: { DataKey:"DO2", Type:"BitLamp", Func:onBitFuncWsGreenLog2, RiseEdge:true, BoolNum:true },
                      P1w: { DataKey:"DO2", Type:"BitLamp", NodeID:"P1w" },
                    P1Cmd: { DataKey:"DO2", Type:"ArrayIDx", Arr:G_RES[G_LANG]["P"], NodeID:"P1Cmd", BoolNum:true },
               P1CmdColor: { DataKey:"DO2", Type:"ArrayIDx", Arr:G_RES[G_LANG]["StGreen"], NodeID:"P1Cmd", NodeAttr:"class", DefaultValue:"", BoolNum:true },
              P1Spd1Color: { DataKey:"DO0", Type:"ArrayIDx", Arr:G_RES[G_LANG]["StBlue"], NodeID:"P1Spd1", NodeAttr:"class", DefaultValue:"", BoolNum:true },
              P1Spd2Color: { DataKey:"DO1", Type:"ArrayIDx", Arr:G_RES[G_LANG]["StBlue"], NodeID:"P1Spd2", NodeAttr:"class", DefaultValue:"", BoolNum:true },
                P1Spd1Log: { DataKey:"DO0", Type:"Func", NodeID:"P1Spd1", Func:onBitFuncWsLog, RiseEdge:true, BoolNum:true },
                P1Spd2Log: { DataKey:"DO1", Type:"Func", NodeID:"P1Spd2", Func:onBitFuncWsLog, RiseEdge:true, BoolNum:true }
				   };

		initUI(WsUri, WsID, Opts);
	}
}
