/* @page rtos.h
 *       FreeRTOS
 *       defines
 *       2020-2022
 */

#ifndef RTOS_H
#define RTOS_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "type.h"
#include "config.h"


/** @def RTOS tick time
 *       1kHz = 1000Hz = 1ms
 */
#define RTOS_TICK_MS                   (uint32_t)1        //ms
#define RTOS_TICK_NS                   (uint32_t)1000000  //ns


/** @note Task priorities
 *        = 0 - lower
 *        = configMAX_PRIORITIES - higher (see FreeRTOSConfig.h)
 *
 *        Stack size is the number of words (not bytes!)
 */

#ifdef DEBUG

/** @def Task `Debug Log`
 *       blocking
 */
#define RTOS_T_LOG_ID                  (uint8_t)1                                        //Task ID
#define RTOS_T_LOG_NAME                "T_Log"                                           //Task name (for debug)
#define RTOS_T_LOG_STACK_SZ            (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE  //Stack size for the task
#define RTOS_T_LOG_PRIORITY            (UBaseType_t)8                                    //Task priority

/** @var Queue `Data for Debug Log`
 *  @note
 *       Tasks: ANY > T_Log
 */
#define RTOS_Q_LOG_ID                  (uint8_t)11                                       //Queue ID
#define RTOS_Q_LOG_ISZ                 (UBaseType_t)sizeof(uint8_t)                      //size of one item (sizeof(t))
#define RTOS_Q_LOG_SZ                  (UBaseType_t)DEBUG_LOG_BUFF_SZ                    //quantity of items
extern QueueHandle_t RTOS_Q_Log;

/** @var Mutex `Debug Log`
 *  @note
 *       Tasks: T_Log
 */
#define RTOS_MTX_LOG_ID                (uint8_t)11                                       //Mutex ID
extern SemaphoreHandle_t RTOS_MTX_Log;

#endif // DEBUG


#ifdef RTE_MOD_DI

#include "di.h"

/** @def Task `DI IRQ`
 *       blocking
 */
#define RTOS_T_DI_IRQ_ID               (uint8_t)2                                        //Task ID
#define RTOS_T_DI_IRQ_NAME             "T_DI_IRQ"                                        //Task name (for debug)
#define RTOS_T_DI_IRQ_STACK_SZ         (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE  //Stack size for the task
#define RTOS_T_DI_IRQ_PRIORITY         (UBaseType_t)3                                    //Task priority

/** @def Task `DI Settings`
 *       blocking
 */
#define RTOS_T_DI_SET_ID               (uint8_t)21                                        //Task ID
#define RTOS_T_DI_SET_NAME             "T_DI_SET"                                         //Task name (for debug)
#define RTOS_T_DI_SET_STACK_SZ         (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE  //Stack size for the task
#define RTOS_T_DI_SET_PRIORITY         (UBaseType_t)3                                    //Task priority

/** @var Queue `DI IRQ`
 *  @note
 *       Tasks: DI IRQ > T_DI
 */
#define RTOS_Q_DI_IRQ_ID               (uint8_t)21                                       //Queue ID
#define RTOS_Q_DI_IRQ_ISZ              (UBaseType_t)sizeof(PlcDI_IRQ_t)                  //size of one item (sizeof(t))
#define RTOS_Q_DI_IRQ_SZ               (UBaseType_t)(32*PLC_DI_SZ)                       //quantity of items
extern QueueHandle_t RTOS_Q_DiIrq;

/** @var Queue `DI Settings`
 *  @note
 *       Tasks: T_Data > T_DI
 */
#define RTOS_Q_DI_SET_ID               (uint8_t)22                                       //Queue ID
#define RTOS_Q_DI_SET_ISZ              (UBaseType_t)sizeof(PlcDI_Set_t)                  //size of one item (sizeof(t))
#define RTOS_Q_DI_SET_SZ               (UBaseType_t)(32*PLC_DI_SZ)                       //quantity of items
extern QueueHandle_t RTOS_Q_DiSet;

/** @var Queue `DI data for T_Data`
 *  @note
 *       Tasks: T_DI > T_Data
 */
#define RTOS_Q_DATA_DI_ID              (uint8_t)23                                       //Queue ID
#define RTOS_Q_DATA_DI_ISZ             (UBaseType_t)sizeof(PlcDI_t)                      //size of one item (sizeof(t))
#define RTOS_Q_DATA_DI_SZ              (UBaseType_t)(32*PLC_DI_SZ)                       //quantity of items
extern QueueHandle_t RTOS_Q_DataDi;

/** @var Mutex `DI-channels`
 *  @note
 *       Tasks: T_DI
 */
#define RTOS_MTX_DI_ID                 (uint8_t)21                                       //Mutex ID
extern SemaphoreHandle_t RTOS_MTX_Di;

/** @var Timer `Tachometer reloading` (auto-reloaded with controlled launch)
 *  @note
 *       Tasks: T_DI
 */
#define RTOS_TIM_DI_TACH_ID            (uint8_t)21                                       //Timer ID
#define RTOS_TIM_DI_TACH               "TIM_DiTach"                                      //timet name (for debug)
#define RTOS_TIM_DI_TACH_TM            (TickType_t)100                                   //timer period (100 msec)
#define RTOS_TIM_DI_TACH_MU            (uint8_t)10                                       //counter multiplier
extern TimerHandle_t RTOS_TIM_DiTach;

#endif // RTE_MOD_DI


#ifdef RTE_MOD_DO

#include "do.h"

/** @def Task `DO`
 *       blocking
 */
#define RTOS_T_DO_ID                   (uint8_t)3                                        //Task ID
#define RTOS_T_DO_NAME                 "T_DO"                                            //Task name (for debug)
#define RTOS_T_DO_STACK_SZ             (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE  //Stack size for the task
#define RTOS_T_DO_PRIORITY             (UBaseType_t)3                                    //Task priority

/** @var Queue `DO Settings`
 *  @note
 *       Tasks: T_Data > T_DO
 */
#define RTOS_Q_DO_SET_ID               (uint8_t)31                                       //Queue ID
#define RTOS_Q_DO_SET_ISZ              (UBaseType_t)sizeof(PlcDO_Set_t)                  //size of one item (sizeof(t))
#define RTOS_Q_DO_SET_SZ               (UBaseType_t)(8*PLC_DO_SZ)                        //quantity of items
extern QueueHandle_t RTOS_Q_DoSet;

/** @var Queue `DO data for T_Data`
 *       Tasks: T_DO > T_Data
 */
#define RTOS_Q_DATA_DO_ID              (uint8_t)32                                        //Queue ID
#define RTOS_Q_DATA_DO_ISZ             (UBaseType_t)sizeof(PlcDO_Set_t)                   //size of one item (sizeof(t))
#define RTOS_Q_DATA_DO_SZ              (UBaseType_t)(8*PLC_DO_SZ)                        //quantity of items
extern QueueHandle_t RTOS_Q_DataDo;

#endif // RTE_MOD_DO


#ifdef RTE_MOD_MBRTU_SLAVE

#include "mbrtu.h"

/** @def Task `MBRTU`
 *       blocking
 */
#define RTOS_T_MBRTU_ID                (uint8_t)8                                        //Task ID
#define RTOS_T_MBRTU_NAME              "T_MbRtu"                                         //Task name (for debug)
#define RTOS_T_MBRTU_STACK_SZ          (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE  //Stack size for the task
#define RTOS_T_MBRTU_PRIORITY          (UBaseType_t)3                                    //Task priority

/** @var Queue `MBRTU RX-data`
 *  @note
 *       Tasks: USART IRQ > T_COM1
 */
#define RTOS_Q_MBRTU_RX_ID             (uint8_t)81                                       //Queue ID
#define RTOS_Q_MBRTU_RX_ISZ            (UBaseType_t)sizeof(uint8_t)                      //size of one item (sizeof(t))
#define RTOS_Q_MBRTU_RX_SZ             (UBaseType_t)8                                    //quantity of items
extern QueueHandle_t RTOS_Q_MbRtuRx;

/** @var Queue `MBRTU Settings`
 *  @note
 *       Tasks: T_Data > T_MBRTU
 */
#define RTOS_Q_MBRTU_SET_ID            (uint8_t)82                                       //Queue ID
#define RTOS_Q_MBRTU_SET_ISZ           (UBaseType_t)sizeof(MBRTU_Set_Q_t)                //size of one item (sizeof(t))
#define RTOS_Q_MBRTU_SET_SZ            (UBaseType_t)4                                    //quantity of items
extern QueueHandle_t RTOS_Q_MbRtuSet;

/** @var Mutex `ModBus Tables`
 *  @note
 *       Tasks: T_Data
 *              T_App
 *              T_Com1
 */
#define RTOS_MTX_MBTABLES_ID           (uint8_t)81                                        //Mutex ID
extern SemaphoreHandle_t RTOS_MTX_MbTables;

#endif // RTE_MOD_MBRTU_SLAVE


#ifdef RTE_MOD_APP

#include "plc_abi.h"

/** @def Task `Application`
 *       not-blocking
 */
#define RTOS_T_APP_ID                  (uint8_t)9                                        //Task ID
#define RTOS_T_APP_NAME                "T_App"                                           //Task name (for debug)
#define RTOS_T_APP_STACK_SZ            (configSTACK_DEPTH_TYPE)2048                      //Stack size for the task
#define RTOS_T_APP_PRIORITY            (UBaseType_t)3                                    //Task priority

/** @def Binary Semaphore `Application`
 */
#define RTOS_SEMA_APP_ID               (uint8_t)91                                       //Semaphore ID
extern SemaphoreHandle_t RTOS_SEMA_App;

/** @var Timer `Application period`
 *       (one-shot with controlled launch)
 *  @note
 *       Tasks: T_App
 */
#define RTOS_TIM_APP_ID                (uint8_t)91                                       //Timer ID
#define RTOS_TIM_APP                   "TIM_App"                                         //timet name (for debug)
#define RTOS_TIM_APP_TM                (TickType_t)1                                     //timer period (1 msec by default; modified in rtos-task-app.c)
extern TimerHandle_t RTOS_TIM_App;

#endif // RTE_MOD_APP



#ifdef RTE_MOD_APP_DEBUG


#endif // RTE_MOD_APP_DEBUG


#ifdef RTE_MOD_REG_MONITOR

/** @var Queue `Updated registers for T_Data`
 *  @note
 *       Tasks: T_MbRtuSlv1 > T_Data
 *              RegCopy     > T_Data
 */
#define RTOS_Q_DATA_REG_MONITOR_ID     (uint8_t)10                                       //Queue ID
#define RTOS_Q_DATA_REG_MONITOR_ISZ    (UBaseType_t)sizeof(uint16_t)                     //size of one item (sizeof(t))
#define RTOS_Q_DATA_REG_MONITOR_SZ     (UBaseType_t)128                                  //quantiry of items
extern QueueHandle_t RTOS_Q_DataRegMonitor;

#endif // RTE_MOD_REG_MONITOR


#ifdef RTE_MOD_DATA

/** @def Task `Data`
 *       not-blocking
 */
#define RTOS_T_DATA_ID                 (uint8_t)11                                       //Task ID
#define RTOS_T_DATA_NAME               "T_Data"                                          //Task name (for debug)
#define RTOS_T_DATA_STACK_SZ           (configSTACK_DEPTH_TYPE)256                       //Stack size for the task
#define RTOS_T_DATA_PRIORITY           (UBaseType_t)3                                    //Task priority

#endif // RTE_MOD_DATA


#endif //RTOS_H
