/**
 ********************************************************************************
 * @file    ConfigureThread.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests for the ConfigureThread Function in the FreeRTOS Wrapper
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "ConfigureThread.hpp"

#include "FreeRTOS_Wrapper_Methods.h"
#include "FreeRTOS_Wrapper_Types.h"

#include "thread_test_utilities.hpp"
#include "test_utilities.hpp"

test_results_t SDD_005_010() {
    const char *testDescription = "This function will verify that " \
        "the ConfigureThread throws an error if the thread name " \
        "does not exist.";
    
    const char *testPreconditionsList[] = {"Valid Loop Function", 
                                           "Valid Thread Priority",
                                           "Valid Stack Size"};
    const char *testResultsList[] = {"Error is thrown when NULL Name", 
                                     "No Error is thrown when Valid Name"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);

    // Test Invalid Thread Name
    {
        Print("Configuring Thread with NULL Name");
        thread_function_t thread_config = ConfigureThread(NULL, Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, NOT_EQUAL);
    }

    // Test Valid Thread Name
    {
        Print("Configuring Thread with Valid Name");
        thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);
    }

    TestPostamble();
}

test_results_t SDD_006_010() {
    const char *testDescription = "This function will verify that " \
        "the ConfigureThread throws an error if the thread name " \
        "is longer than valid for FreeRTOS.";
    
    const char *testPreconditionsList[] = {"Valid Loop Function", 
                                           "Valid Thread Priority",
                                           "Valid Stack Size"};
    const char *testResultsList[] = {"Error is thrown when Name too Long", 
                                     "No Error is thrown when Valid Name"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);

    // Test Invalid Thread Name
    {
        Print("Configuring Thread with Name too Long");
        thread_function_t thread_config = ConfigureThread("Testname1", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, NOT_EQUAL);
    }

    // Test Valid Thread Name
    {
        Print("Configuring Thread with Valid Name");
        thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);
    }

    TestPostamble();
}

test_results_t SDD_007_010() {
    const char *testDescription = "This function will verify that " \
        "the ConfigureThread throws an error if the thread loop function " \
        "does not exist.";
    
    const char *testPreconditionsList[] = {"Valid Thread Name", 
                                           "Valid Thread Priority",
                                           "Valid Stack Size"};
    const char *testResultsList[] = {"Error is thrown when NULL Function", 
                                     "No Error is thrown when Valid Function"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);

    // Test Invalid Thread Function
    {
        Print("Configuring Thread with NULL Function");
        thread_function_t thread_config = ConfigureThread("Testname", NULL, THREAD_PRIORITY_MEDIUM, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, NOT_EQUAL);
    }

    // Test Valid Thread Function
    {
        Print("Configuring Thread with Valid Function");
        thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);
    }
    
    TestPostamble();
}

test_results_t SDD_008_010() {
    const char *testDescription = "This function will verify that " \
        "the ConfigureThread throws an error if the thread priority " \
        "is invalid.";
    
    const char *testPreconditionsList[] = {"Valid Thread Name", 
                                           "Valid Thread Priority",
                                           "Valid Stack Size"};
    const char *testResultsList[] = {"Error is thrown when NULL Function", 
                                     "No Error is thrown when Valid Function"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);

    // Test Medium Valid Thread Function
    {
        Print("Configuring Thread with Medium Valid Priority");
        thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);
    }
    
    // Test Low Invalid Thread Priority
    {
        Print("Configuring Thread with Low Invalid Priority");
        thread_function_t thread_config = ConfigureThread("Testname", Valid_Function, THREAD_PRIORITY_IDLE, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, NOT_EQUAL);
    }

    // Test Low Valid Thread Function
    {
        Print("Configuring Thread with Low Valid Function");
        thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_LOW, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);
    }

    // Test High Invalid Thread Priority
    {
        Print("Configuring Thread with High Invalid Priority");
        thread_function_t thread_config = ConfigureThread("Testname", Valid_Function, (thread_priority_t)(THREAD_PRIORITY_HIGH + 1), 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, NOT_EQUAL);
    }

    // Test High Valid Thread Function
    {
        Print("Configuring Thread with High Valid Function");
        thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_HIGH, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);
    }
    
    TestPostamble();
}