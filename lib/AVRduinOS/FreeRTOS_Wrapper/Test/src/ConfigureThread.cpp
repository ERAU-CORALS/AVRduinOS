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

    const char *testForLoopList[] = {"Thread Priorities (IDLE - HIGH+1)"};
    
    const char *testPreconditionsList[] = {"Valid Thread Name", 
                                           "Valid Thread Function",
                                           "Valid Stack Size"};
    const char *testResultsList[] = {"Error is thrown when thread priority is not LOW, MEDIUM, or HIGH", 
                                     "No Error is thrown when thread priority is LOW, MEDIUM, or HIGH"};

    TestPreamble(testDescription, testForLoopList, testPreconditionsList, testResultsList);

    struct test_case_data {
        thread_priority_t priority;
        bool valid;
        const char *case_name;
    } Test_Cases[] = {
        {THREAD_PRIORITY_IDLE,      false,  "IDLE (Low Invalid)"},
        {THREAD_PRIORITY_LOW,       true,   "LOW (Valid)"},
        {THREAD_PRIORITY_MEDIUM,    true,   "MEDIUM (Valid)"},
        {THREAD_PRIORITY_HIGH,      true,   "HIGH (Valid)"},
        {(thread_priority_t)(THREAD_PRIORITY_HIGH + 1), false, ">HIGH (Invalid)"}
    };

    // Test Medium Valid Thread Function
    for (test_case_data Test_Case : Test_Cases) {
        Print("Configuring Thread with %s Priority", Test_Case.case_name);
        thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, Test_Case.priority, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, Test_Case.valid ? EQUAL : NOT_EQUAL);
    }
    
    TestPostamble();
}

test_results_t SDD_009_010() {
    const char *testDescription = "This function will verify that " \
        "the ConfigureThread throws an error if the stack size " \
        "is zero.";
    
    const char *testPreconditionsList[] = {"Valid Thread Name", 
                                           "Valid Thread Function",
                                           "Valid Thread Priority"};
    const char *testResultsList[] = {"Error is thrown when Stack Size is zero", 
                                     "No Error is thrown when Stack Size is valid"};

    TestPreamble(testDescription, NULL, testPreconditionsList, testResultsList);
    
    // Test Invalid Stack Size
    {
        Print("Configuring Thread with Stack Size 0");
        thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 0);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, NOT_EQUAL);
    }

    // Test Valid Stack Size
    {
        Print("Configuring Thread with Stack Size 128");
        thread_function_t thread_config = ConfigureThread("TestName", Valid_Function, THREAD_PRIORITY_MEDIUM, 128);
        Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);
    }
    
    TestPostamble();
}

test_results_t SDD_011() {
    const char *testDescription = "This function will verify that " \
        "the ConfigureThread accurately fills the fields with the provided " \
        "information.";

    const char *testForLoopList[] = {"Thread Names (Name1, Second, TestName)",
                                     "Thread Functions (Valid_Function, Valid_Function2)"
                                     "Thread Priorities (LOW, MEDIUM, HIGH)",
                                     "Thread Stack Sizes (1, 16, 128, 1024)"};
    
    const char *testResultsList[] = {"Thread Parameters Match"};

    TestPreamble(testDescription, testForLoopList, NULL, testResultsList);

    // Test Cases
    const char *thread_names[] = {"Name1", "Second", "TestName"};
    struct thread_loop_function {
        thread_loop_t function;
        const char * name;
    } thread_functions[] = {
        {Valid_Function, "Valid_Function"}, 
        {Valid_Function2, "Valid_Function2"}
    };
    thread_priority_t thread_priorities[] = {THREAD_PRIORITY_LOW, THREAD_PRIORITY_MEDIUM, THREAD_PRIORITY_HIGH};
    thread_stack_size_t stack_sizes[] = {1, 16, 128, 1024};

    // Test Medium Valid Thread Function
    for (const char *thread_name : thread_names) {
        for (thread_loop_function thread_function : thread_functions) {
            for (thread_priority_t priority : thread_priorities) {
                for (thread_stack_size_t stack_size : stack_sizes) {
                    PrintLine();
                    Print("\nCase:\n");
                    Print("Thread Name: %s", thread_name);
                    Print("Thread Function: %s", thread_function.name);
                    Print("Thread Priority: %d", priority);
                    Print("Stack Size: %d", stack_size);
                    PrintLine();

                    Print("\nConfiguring Thread...");
                    thread_function_t thread_config = ConfigureThread(thread_name, thread_function.function, priority, stack_size);

                    Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);

                    if (thread_config.valid == THREAD_STRUCT_VALID) {
                        Verify("Thread Name", thread_name, thread_config.thread_name, EQUAL);
                        Verify("Thread Function", (int)thread_function.function, (int)thread_config.function, EQUAL);
                        Verify("Thread Priority", priority, thread_config.priority, EQUAL);
                        Verify("Stack Size", (int)stack_size, (int)thread_config.stack_size, EQUAL);
                    }
                }
            }
        }
    }
    
    TestPostamble();
}