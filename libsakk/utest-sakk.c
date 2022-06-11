#include "sakk.h"
#include "utest-sakk.h"
#include <stdlib.h>
#include <stdio.h>
#include <CUnit/CUnit.h>

static jatekos *feher = NULL, *fekete = NULL;

static void test_gyalog_lepes() {
    int honnan_s = 1, honnan_o = 3, hova_s = 2, hova_o = 2;
    char szin = 'g';
    CU_ASSERT_FALSE(gyalog_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o, &szin)); //elvart: lefele nem lephet balra
    hova_o = 4;
    CU_ASSERT_FALSE(gyalog_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o, &szin)); //elvart: lefele nem lephet jobbra
    hova_s = 2; hova_o = 3;
    CU_ASSERT_TRUE(gyalog_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o, &szin)); //elvart: OK, lefele (elore) lephet egyet
    hova_s = 4; hova_o = 3;
    CU_ASSERT_FALSE(gyalog_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o, &szin)); //elvart: elore nem lephet kettot
}

CU_TestInfo sakk_tests[] = {
    {"gyalogos lepese",         test_gyalog_lepes},
    CU_TEST_INFO_NULL
};

void sakk_test_setup() {
    feher = (jatekos *) malloc (sizeof(jatekos));
    feher->feher = true;
    fekete = (jatekos *) malloc (sizeof(jatekos));
    fekete->feher = false;
    tabla_inicializal();
    tabla_feltolt();
}

void sakk_test_teardown() {
    free(feher);
    free(fekete);
}