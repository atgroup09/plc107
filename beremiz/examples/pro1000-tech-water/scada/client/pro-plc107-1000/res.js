/*	JAVASCRIPT DOCUMENT
*	UTF-8
*/

/*  WebHMI client
*   SCADA / PLC107
*
*   Text Resources
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

//** GLOBAL VARIABLES

var G_RES = { ru: {      SrvConnErr: "Ошибка! Нет подключения к серверу {0}!",
						  NoDataErr: "Ошибка! Нет данных длительное время! Проверьте связь с сервером {0}.",
				    WsNotSupportErr: "Ошибка! Ваш браузер не поддерживает работу с web-сокетами!",
							Connect: "подключиться",
			             Disconnect: "отключиться",
			              WebSocket: "WebSocket",
						   WatchDog: "WatchDog",
						  Connected: "соединение установлено",
					   Disconnected: "соединение сброшено",
					  AutoReconnect: "попытка восстановления соединения...",
					     ConnStates: ["подключение...", "подключено", "отключение...", "отключено", "отключено"],
					           None: "---",
					             St: {0:"нет", 1:"есть"},
					            St1: {0:"выкл", 1:"вкл"},
					            LT1: "Нижний уровень",
					            LT2: "Средний уровень",
					            LT3: "Верхний уровень",
					             P1: "Насос",
					            HS1: "Режим работы",
					         P1Spd1: "Скорость 50%",
					         P1Spd2: "Скорость 100%",
					          LTErr: "Ошибки уровней",
					          LTSet: "Уровень опустошения",
				                Set: {0:"нижний", 1:"средний"},
				                 HS: {0:"РУЧ", 1:"АВТ"},
				                  P: {0:"СТОП", 1:"ПУСК"},
				            StGreen: {0:"", 1:"ui-state-green"},
				           StYellow: {0:"", 1:"ui-state-yellow"},
				              StRed: {0:"", 1:"ui-state-red"},
				             StBlue: {0:"", 1:"ui-state-blue"}
				  }
			};

