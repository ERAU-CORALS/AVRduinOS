/**
 ********************************************************************************
 * @file    FreeRTOS_Wrapper_Methods.c
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Function Wrappers for FreeRTOS
 * @version 1.0
 * @date    2024-03-08
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "FreeRTOS_Wrapper_Methods.h"

#include <stdbool.h>
#include <string.h>

#include <Arduino_FreeRTOS.h>

#include "FreeRTOS_Wrapper_Types.h"

thread_return_t ThreadAssert(BaseType_t return_in);

thread_function_t ConfigureThread(const char *thread_name, thread_loop_t function, thread_priority_t priority, thread_stack_size_t stack_size) {
  if (thread_name == NULL) 
    return (thread_function_t) { .valid = THREAD_NAME_NOT_PROVIDED };
  if (strlen(thread_name) > configMAX_TASK_NAME_LEN) 
    return (thread_function_t) { .valid = THREAD_NAME_TOO_LONG };
  if (function == NULL) 
    return (thread_function_t) { .valid = THREAD_NAME_NOT_PROVIDED };
  if (stack_size == 0) 
    return (thread_function_t) { .valid = THREAD_STACK_SIZE_INVALID };
  if (priority > THREAD_PRIORITY_HIGH || priority < THREAD_PRIORITY_LOW) 
    return (thread_function_t) { .valid = THREAD_PRIORITY_INVALID };        

  return (thread_function_t) {
    .function = function,
    .priority = priority,
    .stack_size = stack_size,
    .thread_name = thread_name,
    .valid = THREAD_STRUCT_VALID,
  };
}

thread_return_t CreateThread(thread_handle_t *thread, thread_function_t function) {
  if (thread == NULL) 
    return THREAD_HANDLE_INVALID;
  if (*thread != NULL) 
    return THREAD_HANDLE_INVALID;
  if (function.valid != THREAD_STRUCT_VALID) 
    return THREAD_FUNCTION_INVALID;

  BaseType_t retval = xTaskCreate(function.function, function.thread_name, function.stack_size, NULL, function.priority, thread);
  return ThreadAssert(retval);
}

thread_return_t DeleteThread(thread_handle_t *thread) {
  if (thread == NULL) 
    return THREAD_HANDLE_INVALID;
  if (*thread == NULL) 
    return THREAD_HANDLE_INVALID;

  vTaskDelete(*thread);
  *thread = NULL;
  return THREAD_SUCCESS;
}

thread_return_t ThreadDelay(thread_time_t delay_ms) {
  vTaskDelay(delay_ms);
  return THREAD_SUCCESS;
}

thread_return_t ThreadDeltaDelay(thread_time_t reference_time, thread_time_t delay_ms) {
  BaseType_t retval = xTaskDelayUntil(&reference_time, delay_ms);
  return ThreadAssert(retval);
}

thread_return_t StartThread(thread_handle_t *thread) {
  if (thread == NULL) 
    return THREAD_HANDLE_INVALID;

  vTaskResume(*thread);
  return THREAD_SUCCESS;
}

thread_return_t StopThread(thread_handle_t *thread) {
  if (thread == NULL) 
    return THREAD_HANDLE_INVALID;

  vTaskSuspend(*thread);
  return THREAD_SUCCESS;
}

thread_time_t ThreadTime() {
  return THREAD_MILLISEC * xTaskGetTickCount();
}

void EnterThreadCritical() {
  taskENTER_CRITICAL();
}
void ExitThreadCritical() {
  taskEXIT_CRITICAL();
}

thread_return_t ThreadNotice(thread_handle_t *thread, thread_notice_give_action_t action, thread_notice_value_t value) {
  return ThreadNoticeIndex(thread, action, value, 0);
}

thread_return_t ThreadNoticeIndex(thread_handle_t *thread, thread_notice_give_action_t action, thread_notice_value_t value, thread_notice_index_t index) {
  if (thread == NULL) 
    return THREAD_HANDLE_INVALID;
  if (index >= configTASK_NOTIFICATION_ARRAY_ENTRIES) 
    return THREAD_NOTICE_INDEX_INVALID;

  BaseType_t retval = xTaskNotifyIndexed(*thread, index, value, action);
  return ThreadAssert(retval);
}

thread_return_t ThreadNoticeQuery(thread_handle_t *thread, thread_notice_give_action_t action, thread_notice_value_t value, thread_notice_value_t *previous_value) {
  return ThreadNoticeQueryIndex(thread, action, value, previous_value, 0);
}

thread_return_t ThreadNoticeQueryIndex(thread_handle_t *thread, thread_notice_give_action_t action, thread_notice_value_t value, thread_notice_value_t *previous_value, thread_notice_index_t index) {
  if (thread == NULL) 
    return THREAD_HANDLE_INVALID;
  if (previous_value == NULL)
    return THREAD_FAILURE_UNKNOWN;
  if (index >= configTASK_NOTIFICATION_ARRAY_ENTRIES) 
    return THREAD_NOTICE_INDEX_INVALID;

  BaseType_t retval = xTaskNotifyAndQueryIndexed(*thread, index, value, action, previous_value);
  return ThreadAssert(retval);
}

thread_return_t ThreadWaitforNotice(thread_notice_value_t *value, thread_notice_value_t entry_clear_bits, thread_notice_value_t exit_clear_bits, thread_time_t max_wait) {
  return ThreadWaitforNoticeIndex(value, entry_clear_bits, exit_clear_bits, max_wait, 0);
}

thread_return_t ThreadWaitforNoticeIndex(thread_notice_value_t *value, thread_notice_value_t entry_clear_bits, thread_notice_value_t exit_clear_bits, thread_time_t max_wait, thread_notice_index_t index) {
  if (value == NULL) 
    return THREAD_FAILURE_UNKNOWN;
  if (index >= configTASK_NOTIFICATION_ARRAY_ENTRIES) 
    return THREAD_NOTICE_INDEX_INVALID;
  
  BaseType_t retval = xTaskNotifyWaitIndexed(index, entry_clear_bits, exit_clear_bits, value, pdMS_TO_TICKS(max_wait));
  return ThreadAssert(retval);
}

thread_return_t ThreadNoticeGive(thread_handle_t *thread) {
  return ThreadNoticeGiveIndex(thread, 0);
}

thread_return_t ThreadNoticeGiveIndex(thread_handle_t *thread, thread_notice_index_t index) {
  if (thread == NULL) 
    return THREAD_HANDLE_INVALID;
  if (index >= configTASK_NOTIFICATION_ARRAY_ENTRIES) 
    return THREAD_NOTICE_INDEX_INVALID;
  
  BaseType_t retval = xTaskNotifyGiveIndexed(*thread, index);
  return ThreadAssert(retval);
}

thread_notice_value_t ThreadNoticeTake(thread_notice_take_action_t action, thread_time_t max_wait) {
  return ThreadNoticeTakeIndex(action, max_wait, 0);
}

thread_notice_value_t ThreadNoticeTakeIndex(thread_notice_take_action_t action, thread_time_t max_wait, thread_notice_index_t index) {
  if (index >= configTASK_NOTIFICATION_ARRAY_ENTRIES) 
    return THREAD_NOTICE_INDEX_INVALID;
  
  return ulTaskNotifyTakeIndexed(index, action, pdMS_TO_TICKS(max_wait));
}

thread_return_t ThreadNoticeClear(thread_handle_t *thread) {  
  return ThreadNoticeClearIndex(thread, 0);
}

thread_return_t ThreadNoticeClearIndex(thread_handle_t *thread, thread_notice_index_t index) {
  if (thread == NULL) 
    return THREAD_HANDLE_INVALID;
  if (index >= configTASK_NOTIFICATION_ARRAY_ENTRIES) 
    return THREAD_NOTICE_INDEX_INVALID;
  
  BaseType_t retval = xTaskNotifyStateClearIndexed(*thread, index);
  return ThreadAssert(retval);
}

thread_notice_value_t ThreadNoticeValueClear(thread_handle_t *thread, thread_notice_value_t clear_mesh) {
  return ThreadNoticeValueClearIndex(thread, clear_mesh, 0);
}

thread_notice_value_t ThreadNoticeValueClearIndex(thread_handle_t *thread, thread_notice_value_t clear_mesh, thread_notice_index_t index) {
  if (thread == NULL) 
    return THREAD_HANDLE_INVALID;
  if (index >= configTASK_NOTIFICATION_ARRAY_ENTRIES) 
    return THREAD_NOTICE_INDEX_INVALID;
  
  return ulTaskNotifyValueClearIndexed(*thread, index, clear_mesh);
}

thread_return_t ThreadAssert(BaseType_t return_in) {
  switch (return_in) {
    case pdPASS:
      return THREAD_SUCCESS;
    case errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY:
      return THREAD_FAILURE_MEMORY_ALLOCATION;
    case errQUEUE_BLOCKED:
      return THREAD_FAILURE_QUEUE_BLOCKED;
    case errQUEUE_YIELD:
      return THREAD_FAILURE_QUEUE_YIELD;
    default:
      return THREAD_FAILURE_UNKNOWN;
  }
}