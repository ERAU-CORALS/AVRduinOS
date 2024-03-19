/**
 ********************************************************************************
 * @file    FreeRTOS_Wrapper_Types.h
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Type Wrappers for FreeRTOS
 * @version 1.0
 * @date    2024-03-08
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __AVRDUINOS_TYPES_H__
#define __AVRDUINOS_TYPES_H__

#ifdef __cplusplus
  extern "C" {
#endif // __cplusplus

#include <stdbool.h>

#include <Arduino_FreeRTOS.h>

typedef TaskHandle_t thread_handle_t;
typedef TaskFunction_t thread_loop_t;
typedef const configSTACK_DEPTH_TYPE thread_stack_size_t;
typedef TickType_t thread_time_t;
typedef uint32_t thread_notice_value_t;
typedef UBaseType_t thread_notice_index_t;

#define THREAD_MILLISEC portTICK_PERIOD_MS

typedef enum __thread_return {
    THREAD_SUCCESS = 0,
    THREAD_FAILURE_MEMORY_ALLOCATION,
    THREAD_FAILURE_QUEUE_BLOCKED,
    THREAD_FAILURE_QUEUE_YIELD,
    THREAD_HANDLE_INVALID,
    THREAD_FUNCTION_INVALID,
    THREAD_NOTICE_INDEX_INVALID,
    THREAD_FAILURE_UNKNOWN,
} thread_return_t;

typedef enum __thread_priority {
    THREAD_PRIORITY_IDLE = tskIDLE_PRIORITY,
    THREAD_PRIORITY_LOW,
    THREAD_PRIORITY_MEDIUM,
    THREAD_PRIORITY_HIGH
} thread_priority_t;

typedef enum __thread_notice_give_action {
  SET = eSetValueWithoutOverwrite,
  SET_BITWISE_OR = eSetBits,
  SET_FORCE = eSetValueWithOverwrite,
  INCREMENT = eIncrement,
  NO_ACTION = eNoAction
} thread_notice_give_action_t;

typedef enum __thread_notice_take_action {
  DECREMENT = pdFALSE,
  CLEAR = pdTRUE
} thread_notice_take_action_t;

typedef enum __thread_valid {
        THREAD_STRUCT_VALID = 0,
        THREAD_NAME_NOT_PROVIDED,
        THREAD_NAME_TOO_LONG,
        THREAD_FUNCTION_NOT_PROVIDED,
        THREAD_STACK_SIZE_INVALID,
        THREAD_PRIORITY_INVALID
    } thread_valid_t;

typedef struct __thread_function {
    thread_loop_t function;
    thread_priority_t priority;
    thread_stack_size_t stack_size;
    const char *thread_name;
    thread_valid_t valid;
} thread_function_t;

#ifdef __cplusplus
  }
#endif // __cplusplus

#endif // __AVRDUINOS_TYPES_H__