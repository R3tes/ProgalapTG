/*
 * Progalap kotprog
 * Keszitette: Bakk Abel, Bucsu Aron
 */
#include "sakk.h"
#include "utest-sakk.h"
#include "utest-sakk.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

CU_SuiteInfo sakk_suites[] = {
    {"sakk", NULL, NULL, sakk_test_setup, sakk_test_teardown, sakk_tests},
    CU_SUITE_INFO_NULL
};

//Gyakorlati anyagbol heavily inspired Bakk Abel
int main() {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return -1;
    };
    if (CU_register_suites(sakk_suites) != CUE_SUCCESS) {
        return -1;
    };
    CU_basic_set_mode(CU_BRM_VERBOSE); //CU_BRM_NORMAL
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0; 
}