/**
 ********************************************************************************
 * @file    thread_test_utilities.cpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests supplements for the FreeRTOS Wrapper
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#include "thread_test_utilities.hpp"

#include "FreeRTOS_Wrapper.h"

#include <Arduino.h>

void Valid_Function(void *params) {
    for (;;) continue;
}

void Valid_Function2(void *params) {
    for (;;) continue;
}

void ThreadDelay_Test(void *params) {
    bool &delay_indicator = test_booleans[0];
    bool &start_indicator = test_booleans[1];

    delay_indicator = false;
    start_indicator = false;

    delay_test_time = 0;
    for (;;) {
        if (start_indicator) {
            delay_indicator = true;
            start_indicator = false;
            ThreadDelay(delay_test_time);
            delay_indicator = false;
        }

        ThreadDelay(1000);
    }
}