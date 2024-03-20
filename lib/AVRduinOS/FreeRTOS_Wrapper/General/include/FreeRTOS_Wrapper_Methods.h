/**
 ********************************************************************************
 * @file    FreeRTOS_Wrapper_Methods.h
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Function Wrappers for FreeRTOS
 * @version 1.0
 * @date    2024-03-08
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include <Arduino_FreeRTOS.h>

#include "FreeRTOS_Wrapper_Types.h"

#ifndef __FREERTOS_WRAPPER_METHODS_H__
#define __FREERTOS_WRAPPER_METHODS_H__

#ifdef __cplusplus
  extern "C" {
#endif // __cplusplus

/**
 ********************************************************************************
 * @brief   Method to create a FreeRTOS Wrapper Thread Configuration Struct
 ********************************************************************************
 * @param[in]     thread_name TYPE: const char *
 * @param[in]     function    TYPE: thread_loop_t
 * @param[in]     priority    TYPE: thread_priority_t
 * @param[in]     stack_size  TYPE: thread_stack_size_t
 ********************************************************************************
 * @return  thread_function_t
 ********************************************************************************
 * @note    This function creates a thread configuration struct that can be used
 *          to create a thread. The struct is used to ensure that the thread is
 *          created with the correct parameters.
 ******************************************************************************** 
**/
thread_function_t ConfigureThread(const char *thread_name, 
                                  thread_loop_t function, 
                                  thread_priority_t priority, 
                                  thread_stack_size_t stack_size);

/**
 ********************************************************************************
 * @brief   Create a Thread
 ********************************************************************************
 * @param[out]    thread    TYPE: thread_handle_t *
 * @param[in]     function  TYPE: thread_function_t
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
 * @note    This function creates a thread and returns a handle to the thread.
 ********************************************************************************
**/
thread_return_t CreateThread(thread_handle_t *thread, 
                             thread_function_t function);

/**
 ********************************************************************************
 * @brief   Delete a Thread object
 ********************************************************************************
 * @param[inout]  thread  TYPE: thread_handle_t *
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
 * @note    This function deletes a thread and nullifies the handle.
 ********************************************************************************
**/
thread_return_t DeleteThread(thread_handle_t *thread);

/**
 ********************************************************************************
 * @brief   Delay the current thread
 ********************************************************************************
 * @param[in]     delay_ms  TYPE: thread_time_t
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
**/
thread_return_t ThreadDelay(thread_time_t delay_ms);

/**
 ********************************************************************************
 * @brief   Delay the current thread until a specific time since a reference time
 ********************************************************************************
 * @param[in]     reference_time  TYPE: thread_time_t
 * @param[in]     delay_ms        TYPE: thread_time_t
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
**/
thread_return_t ThreadDeltaDelay(thread_time_t reference_time, 
                                 thread_time_t delay_ms);

/**
 ********************************************************************************
 * @brief   Start a thread
 ********************************************************************************
 * @param[in]     thread  TYPE: thread_handle_t
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
**/
thread_return_t StartThread(thread_handle_t thread);

/**
 ********************************************************************************
 * @brief   Stop a thread
 ********************************************************************************
 * @param[in]     thread  TYPE: thread_handle_t
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
**/
thread_return_t StopThread(thread_handle_t thread);

/**
 ********************************************************************************
 * @brief   Get the current time in milliseconds
 ********************************************************************************
 * @return  thread_time_t 
 ********************************************************************************
**/
thread_time_t ThreadTime();

/**
 ********************************************************************************
 * @brief   Enter a critical section
 ********************************************************************************
**/
void EnterThreadCritical();

/**
 ********************************************************************************
 * @brief   Exit a critical section
 ********************************************************************************
**/
void ExitThreadCritical();

/**
 ********************************************************************************
 * @brief   Set a notice on a thread
 ********************************************************************************
 * @param[in]     thread  TYPE: thread_handle_t *
 * @param[in]     action  TYPE: thread_notice_give_action_t
 * @param[in]     value   TYPE: thread_notice_value_t
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
 * @note    This function is used to give a notice to a thread.
 *          The notice is always set at the default index of 0.
 *          The notice can perform the following actions:
 *            - SET: Set the notice to the value if the notice is not already set
 *            - SET_BITWISE_OR: Set the notice to the value using a bitwise OR
 *              operation with the current value
 *            - SET_FORCE: Set the notice to the value regardless of the current 
 *              value
 *            - INCREMENT: Increment the current notice value 
 *            - NO_ACTION: Set the notice without modifying the value
 ********************************************************************************
**/
thread_return_t ThreadNotice(thread_handle_t *thread, 
                             thread_notice_give_action_t action, 
                             thread_notice_value_t value);

/**
 ********************************************************************************
 * @brief   Set a notice on a thread at a specific index
 ********************************************************************************
 * @param[in]     thread  TYPE: thread_handle_t *
 * @param[in]     action  TYPE: thread_notice_give_action_t
 * @param[in]     value   TYPE: thread_notice_value_t
 * @param[in]     index   TYPE: thread_notice_index_t
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
 * @note    This function is used to give a notice to a thread.
 *          The notice can perform the following actions:
 *            - SET: Set the notice to the value if the notice is not already set
 *            - SET_BITWISE_OR: Set the notice to the value using a bitwise OR
 *              operation with the current value
 *            - SET_FORCE: Set the notice to the value regardless of the current 
 *              value
 *            - INCREMENT: Increment the current notice value 
 *            - NO_ACTION: Set the notice without modifying the value
 ********************************************************************************
**/
thread_return_t ThreadNoticeIndex(thread_handle_t *thread, 
                                  thread_notice_give_action_t action, 
                                  thread_notice_value_t value, 
                                  thread_notice_index_t index);

/**
 ********************************************************************************
 * @brief   Query and notice on a thread
 ********************************************************************************
 * @param[in]     thread          TYPE: thread_handle_t *
 * @param[in]     action          TYPE: thread_notice_give_action_t
 * @param[in]     value           TYPE: thread_notice_value_t
 * @param[out]    previous_value  TYPE: thread_notice_value_t * 
 ********************************************************************************
 * @return  thread_return_t
 ********************************************************************************
 * @note    This function is performs the same function as ThreadNotice, except
 *          that it also retrieves the existing value in the notice.
 * @see     ThreadNotice
 ********************************************************************************
**/
thread_return_t ThreadNoticeQuery(thread_handle_t *thread, 
                                  thread_notice_give_action_t action, 
                                  thread_notice_value_t value, 
                                  thread_notice_value_t *previous_value);

/**
 ********************************************************************************
 * @brief   Query and notice on a thread at a specific index
 ********************************************************************************
 * @param[in]     thread          TYPE: thread_handle_t *
 * @param[in]     action          TYPE: thread_notice_give_action_t
 * @param[in]     value           TYPE: thread_notice_value_t
 * @param[out]    previous_value  TYPE: thread_notice_value_t *
 * @param[in]     index           TYPE: thread_notice_index_t 
 ********************************************************************************
 * @return  thread_return_t
 ********************************************************************************
 * @note    This function is performs the same function as ThreadNoticeIndex, 
 *          except that it also retrieves the existing value in the notice.
 * @see     ThreadNoticeIndex
 ********************************************************************************
**/
thread_return_t ThreadNoticeQueryIndex(thread_handle_t *thread, 
                                       thread_notice_give_action_t action, 
                                       thread_notice_value_t value, 
                                       thread_notice_value_t *previous_value, 
                                       thread_notice_index_t index);

/**
 ********************************************************************************
 * @brief   Wait for a notice on a thread
 ********************************************************************************
 * @param[out]    value             TYPE: thread_notice_value_t *
 * @param[in]     entry_clear_bits  TYPE: thread_notice_value_t
 * @param[in]     exit_clear_bits   TYPE: thread_notice_value_t
 * @param[in]     max_wait          TYPE: thread_time_t
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
 * @note    This function is used to wait for a notice in a thread.
 *          The function always waits for the notice at the default index of 0.
 *          The function can clear bits when beginning to wait and when exiting
 *          the wait.
 *          The function has a maximum wait time.
 ********************************************************************************
**/
thread_return_t ThreadWaitforNotice(thread_notice_value_t *value, 
                                    thread_notice_value_t entry_clear_bits, 
                                    thread_notice_value_t exit_clear_bits, 
                                    thread_time_t max_wait);

/**
 ********************************************************************************
 * @brief   Wait for a notice on a thread at a specific index
 ********************************************************************************
 * @param[out]    value             TYPE: thread_notice_value_t *
 * @param[in]     entry_clear_bits  TYPE: thread_notice_value_t
 * @param[in]     exit_clear_bits   TYPE: thread_notice_value_t
 * @param[in]     max_wait          TYPE: thread_time_t
 * @param[in]     index             TYPE: thread_notice_index_t
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
 * @note    This function is used to wait for a notice at an indexc in a thread.
 *          The function can clear bits when beginning to wait and when exiting
 *          the wait.
 *          The function has a maximum wait time.
 ********************************************************************************
**/
thread_return_t ThreadWaitforNoticeIndex(thread_notice_value_t *value, 
                                         thread_notice_value_t entry_clear_bits, 
                                         thread_notice_value_t exit_clear_bits, 
                                         thread_time_t max_wait, 
                                         thread_notice_index_t index);

/**
 ********************************************************************************
 * @brief   Give a notice to a thread
 ********************************************************************************
 * @param[in]     thread  TYPE: thread_handle_t *
 ********************************************************************************
 * @return thread_return_t 
 ********************************************************************************
 * @note    This function is used to give a notice to a thread.
 *          The notice is always set at the default index of 0.
 *          The notice always increments the current value.
 ********************************************************************************
**/
thread_return_t ThreadNoticeGive(thread_handle_t *thread);

/**
 ********************************************************************************
 * @brief   Give a notice to a thread at a specific index
 ********************************************************************************
 * @param[in]     thread  TYPE: thread_handle_t *
 * @param[in]     index   TYPE: thread_notice_index_t
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
 * @note    This function is used to give a notice to a thread.
 *          The notice always increments the current value.
 ********************************************************************************
**/
thread_return_t ThreadNoticeGiveIndex(thread_handle_t *thread, 
                                      thread_notice_index_t index);

/**
 ********************************************************************************
 * @brief   Take a notice from a thread
 ********************************************************************************
 * @param[in]     action    TYPE: thread_notice_take_action_t
 * @param[in]     max_wait  TYPE: thread_time_t
 ********************************************************************************
 * @return  thread_notice_value_t 
 ********************************************************************************
 * @note    This function is used to take a notice from a thread.
 *          The notice is always taken at the default index of 0.
 *          The notice can perform the following actions:
 *            - DECREMENT: Decrement the current notice value
 *            - CLEAR: Clear the notice
 ********************************************************************************
**/
thread_notice_value_t ThreadNoticeTake(thread_notice_take_action_t action, 
                                       thread_time_t max_wait);

/**
 ********************************************************************************
 * @brief   Take a notice from a thread at a specific index
 ********************************************************************************
 * @param[in]     action  TYPE: thread_notice_take_action_t
 * @param[in]     max_wait  TYPE: thread_time_t
 * @param[in]     index  TYPE: thread_notice_index_t
 ********************************************************************************
 * @return  thread_notice_value_t 
 ********************************************************************************
 * @note    This function is used to take a notice from a thread.
 *          The notice can perform the following actions:
 *            - DECREMENT: Decrement the current notice value
 *            - CLEAR: Clear the notice
 ********************************************************************************
**/
thread_notice_value_t ThreadNoticeTakeIndex(thread_notice_take_action_t action, 
                                            thread_time_t max_wait, 
                                            thread_notice_index_t index);

/**
 ********************************************************************************
 * @brief   Clear a notice from a thread
 ********************************************************************************
 * @param[in]     thread  TYPE: thread_handle_t *
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
 * @note    This function is used to clear a notice from a thread.
 *          The notice is always cleared at the default index of 0.
 ********************************************************************************
**/
thread_return_t ThreadNoticeClear(thread_handle_t *thread);

/**
 ********************************************************************************
 * @brief   Clear a notice from a thread at a specific index
 ********************************************************************************
 * @param[in]     thread  TYPE: thread_handle_t *
 * @param[in]     index   TYPE: thread_notice_index_t
 ********************************************************************************
 * @return  thread_return_t 
 ********************************************************************************
 * @note    This function is used to clear a notice from a thread.
 ********************************************************************************
**/
thread_return_t ThreadNoticeClearIndex(thread_handle_t *thread, 
                                       thread_notice_index_t index);

/**
 ********************************************************************************
 * @brief   Clear a notice value from a thread
 ********************************************************************************
 * @param[in]     thread  TYPE: thread_handle_t *
 * @param[in]     clear_mesh  TYPE: thread_notice_value_t
 ********************************************************************************
 * @return  thread_notice_value_t 
 ********************************************************************************
 * @note    This function is used to clear a notice value from a thread.
 *          The notice is always cleared at the default index of 0.
 ********************************************************************************
**/
thread_notice_value_t ThreadNoticeValueClear(thread_handle_t *thread, 
                                             thread_notice_value_t clear_mesh);

/**
 ********************************************************************************
 * @brief   Clear a notice value from a thread at a specific index
 ********************************************************************************
 * @param[in]     thread  TYPE: thread_handle_t *
 * @param[in]     clear_mesh  TYPE: thread_notice_value_t
 * @param[in]     index  TYPE: thread_notice_index_t
 ********************************************************************************
 * @return  thread_notice_value_t 
 ********************************************************************************
 * @note    This function is used to clear a notice value from a thread.
 ********************************************************************************
**/
thread_notice_value_t ThreadNoticeValueClearIndex(thread_handle_t *thread, 
                                                  thread_notice_value_t clear_mesh, 
                                                  thread_notice_index_t index);

/**
 *******************************************************************************
 * @brief   Start the Thread Scheduler
 *******************************************************************************
**/
void StartThreadScheduler();

/**
 *******************************************************************************
 * @brief   Stop the Thread Scheduler
 *******************************************************************************
**/
void StopThreadScheduler();

/**
 *******************************************************************************
 * @brief   Suspend the Thread Scheduler
 *******************************************************************************
**/
void SuspendThreadScheduler();

/**
 *******************************************************************************
 * @brief   Resume the Thread Scheduler
 *******************************************************************************
**/
void ResumeThreadScheduler();

/**
 *******************************************************************************
 * @brief   Get the handle of the current thread
 *******************************************************************************
 * @return  thread_handle_t
 *******************************************************************************
**/
thread_handle_t GetSelfThreadHandle();

#ifdef __cplusplus
  }
#endif // __cplusplus

#endif // __FREERTOS_WRAPPER_METHODS_H__