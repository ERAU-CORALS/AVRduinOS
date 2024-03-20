/**
 ********************************************************************************
 * @file    thread_test_utilities.hpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Unit Tests supplements for the FreeRTOS Wrapper
 * @version 1.0
 * @date    2024-03-18
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __THREAD_TEST_UTILITIES_HPP__
#define __THREAD_TEST_UTILITIES_HPP__

#include "FreeRTOS_Wrapper.h"

static bool test_booleans[32];
static thread_time_t delay_test_time;

void Valid_Function(void* params = NULL);
void Valid_Function2(void* params = NULL);

void ThreadDelay_Test(void* params = NULL);

#endif // __THREAD_TEST_UTILITIES_HPP__