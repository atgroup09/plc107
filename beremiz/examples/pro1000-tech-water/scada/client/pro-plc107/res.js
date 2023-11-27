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
				                 St: {0:"выкл", 1:"вкл"},
				                St1: {0:"не загружена", 1:"загружена"},
				                St2: {0:"нет", 1:"есть"},
					            DI0: "DI0",
					            DI1: "DI1",
					            DI2: "DI2",
					            DI3: "DI3",
					            DO0: "DO0",
					            DO1: "DO1",
					            DO2: "DO2",
					            DO3: "DO3",
					            Run: "Программа",
					            Pwr: "Питание"
				  }
			};

