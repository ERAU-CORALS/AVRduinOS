/**
 ********************************************************************************
 * @file    DeleteThread.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests for the DeleteThread Function in the FreeRTOS Wrapper
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "DeleteThread.hpp"

#include "FreeRTOS_Wrapper.h"

#include "thread_test_utilities.hpp"
#include "test_utilities.hpp"

test_results_t SDD_020() {
    const char *testDescription = "This function will verify that " \
        "the DeleteThread function throws an error if the thread handle " \
        "pointer is NULL.";
    
    const char *testPreconditionsList[] = {"Valid Thread"};
    const char *testResultsList[] = {"Error is thrown when NULL handle pointer"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);

    // Configuring Valid Thread
    Print("Configuring Thread with Valid Name");
    thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
    Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);

    // Creating Thread
    Print("Creating Thread with NULL Handle Pointer");
    thread_handle_t handle = NULL; 
    thread_return_t retval = CreateThread(&handle, thread_config);
    Verify("Thread Creation Status", THREAD_SUCCESS, retval, EQUAL);  
    if (retval != THREAD_SUCCESS) goto Early_Fail_Jump;

    // Test Delete Thread with NULL Handle Pointer
    {
        retval = DeleteThread(NULL);
        Verify("Thread Creation Status", THREAD_SUCCESS, retval, NOT_EQUAL);
        if (retval == THREAD_SUCCESS) goto Early_Fail_Jump;
    }

    // Delete Thread
    Print("Deleting Thread...");
    DeleteThread(&handle);

    Early_Fail_Jump:

    TestPostamble();
}

test_results_t SDD_021() {
    const char *testDescription = "This function will verify that " \
        "the DeleteThread function throws an error if the thread handle " \
        "is NULL.";
    
    const char *testPreconditionsList[] = {"Valid Thread",
                                           "Valid Thread Handle Pointer"};
    const char *testResultsList[] = {"Error is thrown when NULL handle"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);

    // Configuring Valid Thread
    Print("Configuring Thread with Valid Name");
    thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
    Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);

    // Creating Thread
    Print("Creating Thread with NULL Handle Pointer");
    thread_handle_t handle = NULL; 
    thread_return_t retval = CreateThread(&handle, thread_config);
    Verify("Thread Creation Status", THREAD_SUCCESS, retval, EQUAL);
    if (retval != THREAD_SUCCESS) goto Early_Fail_Jump;

    // Test Delete Thread with NULL Handle Pointer
    {
        thread_handle_t invalid_handle = NULL;
        retval = DeleteThread(&invalid_handle);
        Verify("Thread Creation Status", THREAD_SUCCESS, retval, NOT_EQUAL);
        if (retval == THREAD_SUCCESS) goto Early_Fail_Jump;
    }

    // Delete Thread
    Print("Deleting Thread...");
    DeleteThread(&handle);

    Early_Fail_Jump:

    TestPostamble();
}

test_results_t SDD_022() {
    const char *testDescription = "This function will verify that " \
        "the DeleteThread function sets the thread handle to NULL " \
        "if successful.";
    
    const char *testPreconditionsList[] = {"Valid Thread",
                                           "Valid Thread Handle Pointer",
                                           "Valid Thread Handle"};
    const char *testResultsList[] = {"Thread Handle is set to NULL"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);

    // Configuring Valid Thread
    Print("Configuring Thread with Valid Name");
    thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
    Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);

    // Creating Thread
    Print("Creating Thread with NULL Handle Pointer");
    thread_handle_t handle = NULL; 
    thread_return_t retval = CreateThread(&handle, thread_config);
    Verify("Thread Creation Status", THREAD_SUCCESS, retval, EQUAL);
    if (retval != THREAD_SUCCESS) goto Early_Fail_Jump;

    // Delete Thread
    Print("Deleting Thread...");
    retval = DeleteThread(&handle);
    Verify("Thread Deletion Status", THREAD_SUCCESS, retval, EQUAL);
    if (retval != THREAD_SUCCESS) goto Early_Fail_Jump;

    // Test Nullification of Thread Handle
    Verify("Thread Handle", (int)NULL, (int)handle, EQUAL);

    Early_Fail_Jump:

    TestPostamble();
}