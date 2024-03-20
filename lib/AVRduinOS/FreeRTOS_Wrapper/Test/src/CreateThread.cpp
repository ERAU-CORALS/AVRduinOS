/**
 ********************************************************************************
 * @file    CreateThread.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests for the CreateThread Function in the FreeRTOS Wrapper
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "CreateThread.hpp"

#include "FreeRTOS_Wrapper.h"

#include "thread_test_utilities.hpp"
#include "test_utilities.hpp"

test_results_t SDD_013_017() {
    const char *testDescription = "This function will verify that " \
        "the CreateThread function throws an error if the thread handle " \
        "pointer is NULL.";
    
    const char *testPreconditionsList[] = {"Valid Thread Configuration"};
    const char *testResultsList[] = {"Error is thrown when NULL handle pointer", 
                                     "No Error is thrown when defined handle pointer"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);

    // Configuring Valid Thread
    Print("Configuring Thread with Valid Name");
    thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
    Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);

    // Creating Thread with Null Thread Handle Pointer
    {
        Print("Creating Thread with NULL Handle Pointer");
        thread_handle_t *handle_ptr = NULL; 
        thread_return_t retval = CreateThread(handle_ptr, thread_config);
        Verify("Thread Creation Status", THREAD_SUCCESS, retval, NOT_EQUAL);
        if (retval == THREAD_SUCCESS) {
            Print("Deleting Thread...");
            DeleteThread(handle_ptr);
        }
    }

    // Creating Thread with Real Thread Handle Pointer
    {
        Print("Creating Thread with non-NULL Handle Pointer");
        thread_handle_t handle = NULL;
        thread_return_t retval = CreateThread(&handle, thread_config);
        Verify("Thread Creation Status", THREAD_SUCCESS, retval, EQUAL);
        if (retval == THREAD_SUCCESS) {
            Print("Deleting Thread...");
            DeleteThread(&handle);
        }
    }

    TestPostamble();
}

test_results_t SDD_014_017() {
    const char *testDescription = "This function will verify that " \
        "the CreateThread function throws an error if the thread handle " \
        "is not NULL.";
    
    const char *testPreconditionsList[] = {"Valid Thread Configuration"};
    const char *testResultsList[] = {"Error is thrown when not NULL handle", 
                                     "No Error is thrown when NULL handle"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);

    // Configuring Valid Thread
    Print("Configuring Thread with Valid Name");
    thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
    Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);

    // Creating Thread with Null Thread Handle Pointer
    {
        Print("Creating Thread with Invalid Thread Configuration");
        thread_handle_t handle = (thread_handle_t)0x1234;
        thread_return_t retval = CreateThread(&handle, thread_config);
        Verify("Thread Creation Status", THREAD_SUCCESS, retval, NOT_EQUAL);
        if (retval == THREAD_SUCCESS) {
            Print("Deleting Thread...");
            DeleteThread(&handle);
        }
    }

    // Creating Thread with Real Thread Handle Pointer
    {
        Print("Creating Thread with non-NULL Handle Pointer");
        thread_handle_t handle = NULL;
        thread_return_t retval = CreateThread(&handle, thread_config);
        Verify("Thread Creation Status", THREAD_SUCCESS, retval, EQUAL);
        if (retval == THREAD_SUCCESS) {
            Print("Deleting Thread...");
            DeleteThread(&handle);
        }
    }

    TestPostamble();
}

test_results_t SDD_015_017() {
    const char *testDescription = "This function will verify that " \
        "the CreateThread function throws an error if the thread " \
        "configuration is invalid.";
    
    const char *testPreconditionsList[] = {"Non-NULL Thread Handle Pointer",
                                           "NULL Thread Handle"};
    const char *testResultsList[] = {"Error is thrown when invalid configuration", 
                                     "No Error is thrown when valid configuration"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);

    // Creating Thread with Invalid Configuration
    {
        // Configuring Invalid Thread
        Print("Creating Invalid Thread Configuration");
        thread_function_t thread_config = ConfigureThread("TestName", NULL, THREAD_PRIORITY_MEDIUM, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, NOT_EQUAL);

        Print("Creating Thread with Invalid Thread Configuration");
        thread_handle_t handle = NULL;
        thread_return_t retval = CreateThread(&handle, thread_config);
        Verify("Thread Creation Status", THREAD_SUCCESS, retval, NOT_EQUAL);
        if (retval == THREAD_SUCCESS) {
            Print("Deleting Thread...");
            DeleteThread(&handle);
        }
    }

    // Creating Thread with Valid Configuration
    {
        // Configuring Valid Thread
        Print("Creating Valid Thread Configuration");
        thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);

        Print("Creating Thread with Valid Thread Configuration");
        thread_handle_t handle = NULL;
        thread_return_t retval = CreateThread(&handle, thread_config);
        Verify("Thread Creation Status", THREAD_SUCCESS, retval, EQUAL);
        if (retval == THREAD_SUCCESS) {
            Print("Deleting Thread...");
            DeleteThread(&handle);
        }
    }

    TestPostamble();
}

test_results_t SDD_018() {
    const char *testDescription = "This function will verify that " \
        "the CreateThread function sets the thread handle if " \
        "parameters are valid and the task function is created successfully.";
    
    const char *testPreconditionsList[] = {"Non-NULL Thread Handle Pointer",
                                           "NULL Thread Handle",
                                           "Valid Thread Configuration"};
    const char *testResultsList[] = {"Thread Handle is set when valid inputs and successful task creation"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);

    // Creating Thread
    {
        // Configuring Valid Thread
        Print("Creating Valid Thread Configuration");
        thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);

        Print("Creating Thread with Valid Thread Configuration");
        thread_handle_t handle = NULL;
        thread_return_t retval = CreateThread(&handle, thread_config);
        Verify("Thread Creation Status", THREAD_SUCCESS, retval, EQUAL);
        if (retval == THREAD_SUCCESS) {
            Verify("Thread Handle", (int)NULL, (int)handle, NOT_EQUAL);
            Print("Deleting Thread...");
            DeleteThread(&handle);
        }
    }

    TestPostamble();
}