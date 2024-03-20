/**
 ********************************************************************************
 * @file    ThreadDelay.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests for the ThreadDelay Function in the FreeRTOS Wrapper
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "ThreadDelay.hpp"

#include "FreeRTOS_Wrapper.h"

#include "thread_test_utilities.hpp"
#include "test_utilities.hpp"

void SDD_025_Thread(void *params __attribute__((unused))) {
    // Delay Test Indicators
    bool &delay_indicator = test_booleans[0];
    bool &start_indicator = test_booleans[1];

    // Delay Tests
    thread_time_t delay_set[] = {100, 500, 1000, 5000, 10000};

    for (thread_time_t delay_ms : delay_set) {
        Print("Starting %u ms Test...", delay_ms);
        unsigned long text_delay = millis();
        while (millis() - text_delay < 1000) continue;
        delay_test_time = delay_ms;
        start_indicator = true;
        // Wait for start signal processed (up to five seconds)
        unsigned long start_request_time = millis();
        while (start_indicator && millis() - start_request_time < 60000) taskYIELD();
        
        // Wait for delay completion (up to ten times test time)
        unsigned long start_time = millis();
        while (delay_indicator && millis() - start_time < 10 * delay_ms) continue;
        unsigned long end_time = millis();

        Verify_Margin("Delay Milliseconds", delay_ms, end_time - start_time, 10ul);
    }

    StopThreadScheduler();
}

test_results_t SDD_025() {
    const char *testDescription = "This function will verify that " \
        "the ThreadDelay function causes a delay within 10 ms " \
        "of the commanded delay duration.";
    
    const char *testForLoopSets[] = {"Delay Times (100, 500, 1000, 5000, 10000)"};
    const char *testPreconditionsList[] = {"Valid Thread"};
    const char *testResultsList[] = {"Delay is within 10 ms."};

    TestPreamble(testDescription, testForLoopSets, testPreconditionsList, testResultsList);

    // Configuring Valid Thread
    Print("Configuring Thread with ThreadDelay");
    thread_function_t thread_config = ConfigureThread("TestName", ThreadDelay_Test, THREAD_PRIORITY_MEDIUM, 16);
    Verify("Thread Valid Status", THREAD_STRUCT_VALID, thread_config.valid, EQUAL);
    
    // Creating Thread
    Print("Creating Thread with ThreadDelay");
    thread_handle_t handle = NULL; 
    thread_return_t retval = CreateThread(&handle, thread_config);
    Verify("Thread Creation Status", THREAD_SUCCESS, retval, EQUAL);

    // Configuring Test Thread
    Print("Configuring Parallel Thread for Test");
    thread_function_t test_thread_config = ConfigureThread("TestName", SDD_025_Thread, THREAD_PRIORITY_HIGH, 16);
    Verify("Thread Valid Status", THREAD_STRUCT_VALID, test_thread_config.valid, EQUAL);
    
    // Creating Test Thread
    Print("Creating Parallel Thread for Test");
    thread_handle_t test_handle = NULL; 
    retval = CreateThread(&test_handle, test_thread_config);
    Verify("Thread Creation Status", THREAD_SUCCESS, retval, EQUAL);

    // Starting Thread Scheduler
    Print("Starting Thread Scheduler...");
    unsigned long delay_start = millis();
    while (millis() - delay_start < 1000) continue;
    StartThreadScheduler();

    // Delete Thread
    Print("Deleting Threads...");
    DeleteThread(&handle);
    DeleteThread(&test_handle);

    TestPostamble();
}