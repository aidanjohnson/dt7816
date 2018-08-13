/*
 * File:   newcunittest.c
 * Author: root
 *
 * Created on 17-Jul-2018, 16:49:15
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include </usr/include/CUnit/Basic.h>
#include "../recorder_helpers.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testLedIndicators() {
    uint8_t status;
    int streaming;
    ledIndicators(status, streaming);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testGetTime() {
    struct tm** pres_time;
    struct timeval* clock_time;
    getTime(pres_time, clock_time);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testGetTimeEpoch() {
    long year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    long result = getTimeEpoch(year, month, day, hour, minute, second);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testTimestamp() {
    char* file_path;
    char** argv;
    char* path_to_storage;
    timestamp(file_path, argv, path_to_storage);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testGetPresentTime() {
    long result = getPresentTime();
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testCheckFatal() {
    int gross_samples;
    int result = checkFatal(gross_samples);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testCreateChanMask() {
    int* ain;
    int* ch_on;
    chan_mask_t* chan_mask;
    createChanMask(ain, ch_on, chan_mask);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testConfigChan() {
    dt78xx_ain_config_t* ain_cfg;
    configChan(ain_cfg);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testInitTrig() {
    dt78xx_trig_config_t* trig_cfg_ai;
    initTrig(trig_cfg_ai);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

void testCalcSunUpDown() {
    long* sunsets;
    long* sunrises;
    int duration_days;
    long safety_margin;
    double lon;
    double lat;
    int night_cycle;
    calcSunUpDown(sunsets, sunrises, duration_days, safety_margin, lon, lat, night_cycle);
    if (1 /*check result*/) {
        CU_ASSERT(0);
    }
}

int testMain() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("newcunittest", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testLedIndicators", testLedIndicators)) ||
            (NULL == CU_add_test(pSuite, "testGetTime", testGetTime)) ||
            (NULL == CU_add_test(pSuite, "testGetTimeEpoch", testGetTimeEpoch)) ||
            (NULL == CU_add_test(pSuite, "testTimestamp", testTimestamp)) ||
            (NULL == CU_add_test(pSuite, "testGetPresentTime", testGetPresentTime)) ||
            (NULL == CU_add_test(pSuite, "testCheckFatal", testCheckFatal)) ||
            (NULL == CU_add_test(pSuite, "testCreateChanMask", testCreateChanMask)) ||
            (NULL == CU_add_test(pSuite, "testConfigChan", testConfigChan)) ||
            (NULL == CU_add_test(pSuite, "testInitTrig", testInitTrig)) ||
            (NULL == CU_add_test(pSuite, "testCalcSunUpDown", testCalcSunUpDown))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
