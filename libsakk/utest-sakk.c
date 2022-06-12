#include "sakk.h"
#include "utest-sakk.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

static void test_bastya_lepes() {
    int honnan_s = 0, honnan_o = 0, hova_s = 0, hova_o = 5;
    CU_ASSERT_TRUE(bastya_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_s = 1;
    CU_ASSERT_FALSE(bastya_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_s = 7; hova_o = 3;
    CU_ASSERT_FALSE(bastya_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
}

static void test_huszar_lepes() {
    int honnan_s = 0, honnan_o = 1, hova_s = 2, hova_o = 0;
    CU_ASSERT_TRUE(huszar_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_o = 2;
    CU_ASSERT_TRUE(huszar_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_o = 1;
    CU_ASSERT_FALSE(huszar_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_o = 3;
    CU_ASSERT_FALSE(huszar_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
}

static void test_kiraly_lepes() {
    int honnan_s = 3, honnan_o = 4, hova_s = 3, hova_o = 3;

    CU_ASSERT_TRUE(kiraly_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_o = 6;
    CU_ASSERT_FALSE(kiraly_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_s=5;
    CU_ASSERT_FALSE(kiraly_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_s = 2; hova_o = 3;
    CU_ASSERT_TRUE(kiraly_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    honnan_s = 5; honnan_o = 1; hova_s = 6; hova_o = 2;
    CU_ASSERT_TRUE(kiraly_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_s = 5; hova_o = 6;
    CU_ASSERT_FALSE(kiraly_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_s = 3; hova_o = 3;
    CU_ASSERT_FALSE(kiraly_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
}

static void test_futo_lepes(){
    int honnan_s = 0, honnan_o = 2, hova_s = 3, hova_o = 5;

    CU_ASSERT_TRUE(futo_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_s = 2;
    CU_ASSERT_FALSE(futo_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_s = 2; hova_o = 1;
    CU_ASSERT_FALSE(futo_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_s = 2; hova_o = 5;
    CU_ASSERT_FALSE(futo_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    hova_s = 0; hova_o = 5;
    CU_ASSERT_FALSE(futo_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
    honnan_s = 4; honnan_o = 7; hova_s = 6; hova_o = 5;
    CU_ASSERT_TRUE(futo_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o));
}

static void test_beolvas_int() {
    int szam;
    freopen("../test_input/test_beolvas_int.dat", "r", stdin);
    CU_ASSERT_TRUE(beolvas_int(&szam));
    CU_ASSERT_EQUAL(szam, 5);
    CU_ASSERT_FALSE(beolvas_int(&szam));
    CU_ASSERT_TRUE(beolvas_int(&szam));
    CU_ASSERT_EQUAL(szam, 512512);
    szam = 0;
    CU_ASSERT_FALSE(beolvas_int(&szam));
    CU_ASSERT_EQUAL(szam, 0);
    freopen("/dev/stdin", "r", stdin);
}

static void test_beolvas_string() {
    freopen("../test_input/test_beolvas_string.dat", "r", stdin);

    char *szoveg = string_olvas();
    CU_ASSERT_EQUAL(szoveg[0], 'a');
    free(szoveg);
    szoveg = string_olvas();
    CU_ASSERT_TRUE(strcmp(szoveg, "12") == 0);
    CU_ASSERT_FALSE(strcmp(szoveg, "4234234") == 0);
    free(szoveg);
    szoveg = string_olvas();
    CU_ASSERT_EQUAL(szoveg[0], '\0');
    free(szoveg);
    szoveg = string_olvas();
    CU_ASSERT_TRUE(strcmp(szoveg, "egyszer volt hol nem volt volt egyszer egy teszteles") == 0);
    CU_ASSERT_FALSE(strcmp(szoveg, "fdasfdsf ddsfdasdfr") == 0);
    free(szoveg);
    szoveg = string_olvas();
    CU_ASSERT_TRUE(strcmp(szoveg, "szoveg 12") == 0);
    CU_ASSERT_FALSE(strcmp(szoveg, "12 szoveg") == 0);
    free(szoveg);

    freopen("/dev/stdin", "r", stdin);
}

static void test_linked_list() {
    m_cleanup();
    babu testbabu = {'b', false};
    lepes l1 = {0, 0, 1, 0, testbabu, 0};
    lepes l2 = {1, 0, 2, 0, testbabu, 1};
    lepes l3 = {2, 0, 3, 0, testbabu, 2};
    list_hozzaad(l1); list_hozzaad(l2); list_hozzaad(l3);
    CU_ASSERT_EQUAL(list_count(), 3);
    list_torol_elejerol();
    CU_ASSERT_EQUAL(list_count(), 2);
    list_torol_elejerol();
    list_torol_elejerol();
    CU_ASSERT_EQUAL(list_count(), 0);
    m_cleanup();
}

static void test_nyert_e_valaki(){
    reset_tartalom(get_mezo(0,3));
    reset_tartalom(get_mezo(0,4));
    CU_ASSERT_TRUE(nyert_e_valaki());
    tabla_feltolt();
    reset_tartalom(get_mezo(7,3));
    CU_ASSERT_FALSE(nyert_e_valaki());
    tabla_feltolt();
    reset_tartalom(get_mezo(0,4));
    reset_tartalom(get_mezo(7,3));
    CU_ASSERT_FALSE(nyert_e_valaki());
}

static void test_atvaltozas(){
    freopen("../test_input/test_atvaltozas.dat", "r", stdin);
    CU_ASSERT_FALSE(atvaltozas(*feher));
    lepes_teszteleshez(6, 1, 0, 1);
    CU_ASSERT_TRUE(atvaltozas(*feher));
    CU_ASSERT_EQUAL(get_mezo(0, 1)->tartalom[1], 'V');
    CU_ASSERT_NOT_EQUAL(get_mezo(0, 1)->tartalom[1], 'B');
    CU_ASSERT_FALSE(atvaltozas(*fekete));
    freopen("/dev/stdin", "r", stdin);
}

static void test_sancolas(){
    freopen("../test_input/test_sancolas.dat", "r", stdin);
    reset_tartalom(get_mezo(0,5));
    reset_tartalom(get_mezo(0,6));
    CU_ASSERT_TRUE(sancolas(*fekete));
    CU_ASSERT_EQUAL(get_mezo(0, 6)->tartalom[1], 'k');
    CU_ASSERT_EQUAL(get_mezo(0,5)->tartalom[1], 'b');
    CU_ASSERT_FALSE(sancolas(*feher));
    freopen("/dev/stdin", "r", stdin);
}

static void test_lepes_visszalepes() {
    freopen("../test_input/test_lepes.dat", "r", stdin);
    CU_ASSERT_TRUE(lepes_f(*feher));
    CU_ASSERT_EQUAL(get_mezo(5, 0)->tartalom[1], 'G');
    CU_ASSERT_NOT_EQUAL(get_mezo(6, 0)->tartalom[1], 'G');
    CU_ASSERT_TRUE(lepes_f(*feher));
    CU_ASSERT_EQUAL(get_mezo(4, 0)->tartalom[1], 'G');
    CU_ASSERT_TRUE(lepes_f(*feher));
    CU_ASSERT_EQUAL(get_mezo(6, 0)->tartalom[1], 'B');
    CU_ASSERT_TRUE(visszalepes_interact());
    CU_ASSERT_EQUAL(get_mezo(7, 0)->tartalom[1], 'B');
    CU_ASSERT_EQUAL(get_mezo(5, 0)->tartalom[1], 'G');
    freopen("/dev/stdin", "r", stdin);
}

static void test_tabla_inicializal_es_feltolt(){
    CU_ASSERT_EQUAL(get_mezo(0, 0)->tartalom[1], 'b');
    CU_ASSERT_EQUAL(get_mezo(0, 1)->tartalom[1], 'h');
    CU_ASSERT_EQUAL(get_mezo(0, 2)->tartalom[1], 'f');
    CU_ASSERT_EQUAL(get_mezo(0, 3)->tartalom[1], 'v');
    CU_ASSERT_EQUAL(get_mezo(0, 4)->tartalom[1], 'k');
    CU_ASSERT_EQUAL(get_mezo(0, 5)->tartalom[1], 'f');
    CU_ASSERT_EQUAL(get_mezo(0, 6)->tartalom[1], 'h');
    CU_ASSERT_EQUAL(get_mezo(0, 7)->tartalom[1], 'b');
    CU_ASSERT_TRUE(get_mezo(0, 7)->foglalt);
    CU_ASSERT_FALSE(get_mezo(2, 1)->foglalt);

    for (int i = 0; i < 7; ++i) {
        CU_ASSERT_EQUAL(get_mezo(1, i)->tartalom[1], 'g');
    }

    CU_ASSERT_NOT_EQUAL(get_mezo(7, 3)->tartalom[1], 'v');
    CU_ASSERT_NOT_EQUAL(get_mezo(7, 4)->tartalom[1], 'k');
    CU_ASSERT_NOT_EQUAL(get_mezo(6, 2)->tartalom[1], 'F');
    CU_ASSERT_EQUAL(get_mezo(3, 4)->tartalom[0], '[');
    CU_ASSERT_EQUAL(get_mezo(3, 4)->tartalom[1], '_');
    CU_ASSERT_EQUAL(get_mezo(3, 4)->tartalom[2], ']');
    CU_ASSERT_EQUAL(get_mezo(3, 4)->tartalom[3], '\0');
    CU_ASSERT_NOT_EQUAL(get_mezo(3, 4)->tartalom[1], 'g');
}

static void test_reverse_coord_s() {
    int coord = 0;
    CU_ASSERT_EQUAL(reverse_coord_s(&coord), 8);
    coord = 5;
    CU_ASSERT_EQUAL(reverse_coord_s(&coord), 3);
}

static void test_reverse_coord_o() {
    int coord = 0;
    CU_ASSERT_EQUAL((char) reverse_coord_o(&coord), 'A');
    coord = 5;
    CU_ASSERT_EQUAL((char) reverse_coord_o(&coord), 'F');
}

void static test_reset_tartalom(){
    reset_tartalom(get_mezo(0, 0));
    CU_ASSERT_EQUAL(get_mezo(0, 0)->tartalom[1], '_');
    reset_tartalom(get_mezo(7, 2));
    CU_ASSERT_EQUAL(get_mezo(7,2)->tartalom[1], '_');
}

void static test_validate_coord(){
    int c1 = 11, c2 = 21;
    CU_ASSERT_FALSE(validate_coord(&c1, &c2));
    c1 = 0; c2 = 52;
    CU_ASSERT_FALSE(validate_coord(&c1, &c2));
    c1 = 72; c2 = 0;
    CU_ASSERT_FALSE(validate_coord(&c1, &c2));
    c1 = -2; c2 = 6;
    CU_ASSERT_FALSE(validate_coord(&c1, &c2));
    c1 = 5; c2 = -4;
    CU_ASSERT_FALSE(validate_coord(&c1, &c2));
    c1 = -2; c2 = -7;
    CU_ASSERT_FALSE(validate_coord(&c1, &c2));
    c1 = 3; c2 = 4;
    CU_ASSERT_TRUE(validate_coord(&c1, &c2));
    c1 = 6; c2 = 7;
    CU_ASSERT_TRUE(validate_coord(&c1, &c2));
}

void static test_convert_coord(){
    int c1 = 8, c2 = 'A';
    convert_coord(&c1, &c2);
    CU_ASSERT_EQUAL(c1, 0);
    CU_ASSERT_EQUAL(c2, 0);
    c1 = 3; c2 = 'F';
    convert_coord(&c1, &c2);
    CU_ASSERT_EQUAL(c1, 5);
    CU_ASSERT_EQUAL(c2, 5);
}

static void test_jatekos_beker(){
    freopen("../test_input/test_beker.dat", "r", stdin);
    jatekos_beker();
    jatekos j1 = get_jatekos(true), j2 = get_jatekos(false);
    CU_ASSERT_TRUE(j1.feher);
    CU_ASSERT_FALSE(j2.feher);
    CU_ASSERT_TRUE(strcmp(j1.nev, "y") == 0);
    CU_ASSERT_TRUE(strcmp(j2.nev, "eezy") == 0);
    freopen("/dev/stdin", "r", stdin);
}

CU_TestInfo sakk_tests[] = {
    {"gyalogos lepese",                 test_gyalog_lepes},
    {"bastya lepese",                   test_bastya_lepes},
    {"huszar lepese",                   test_huszar_lepes},
    {"kiraly lepese",                   test_kiraly_lepes},
    {"futo lepese",                     test_futo_lepes},
    {"sztring beolvasasa",              test_beolvas_string},
    {"integer beolvasasa",              test_beolvas_int},
    {"jatek gyozelem",                  test_nyert_e_valaki},
    {"babu sancolas",                   test_sancolas},
    {"gyalog atvaltozas",               test_atvaltozas},
    {"babu lepes & visszalepes",        test_lepes_visszalepes},
    {"visszalepes lista tesztelese",    test_linked_list},
    {"sor koordinata megfordit",        test_reverse_coord_s},
    {"oszlop koordinata megfordit",     test_reverse_coord_o},
    {"tartalom visszaallit",            test_reset_tartalom},
    {"koordinata ellenorzes",           test_validate_coord},
    {"koordinata atvaltas",             test_convert_coord},
    {"tabla inicializal es feltolt",    test_tabla_inicializal_es_feltolt},
    {"jatekos bekeres",                 test_jatekos_beker},
    CU_TEST_INFO_NULL
};

void sakk_test_setup() {
    freopen("/tmp/outbin", "w", stdout);
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
    remove("/tmp/outbin");
    freopen("/dev/tty","w",stdout);
}