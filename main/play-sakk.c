#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sakk.h"

int main() {

    jatekos_beker();
    tabla_inicializal();
    tabla_feltolt();
    tabla_kiir();

    //tabla_test_print();
    
    /*lepes *uj = (lepes *) malloc (1 * sizeof(lepes));
    uj->kor = 0;
    lepes *uj2 = (lepes *) malloc (1 * sizeof(lepes));
    uj2->kor = 1;
    list_hozzaad(uj);
    list_hozzaad(uj2);
    list_print();
    list_torol_elejerol();
    printf("----------\n");
    list_print();
    list_torol_elejerol();
    free(uj);
    free(uj2);*/

    //input_test();

    /*babu egy_b = {'p', true};
    lepes egy = {0, 0, 5, 0, egy_b, 0};
    babu ketto_b = {'a', false};
    lepes ketto = {1, 1, 6, 6, ketto_b, 0};
    list_hozzaad(&egy);
    list_hozzaad(&ketto);
    list_print();*/

    /*jatekos j = get_jatekos(false);

    tabla_kiir();
    sancolas(j);
    tabla_kiir();*/

    jatekos j = {false, "asd"};

    lepes_f(j);
    tabla_kiir();
    lepes_f(j);
    tabla_kiir();
    lepes_f(j);
    tabla_kiir();
    //char filename[] = "asd.txt";
    //jatek_elment(filename, false);

    m_cleanup();

    return 0;
}

