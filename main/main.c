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

    lepes_f();
    tabla_kiir();

    return 0;
}

