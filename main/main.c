#include <stdio.h>
#include <stdbool.h>
#include "sakk.h"

int main() {

    jatekos_beker();
    tabla_inicializal();
    tabla_feltolt();
    tabla_kiir();
    //if (jatek_elment("teszt.txt")) printf("mentes done\n");
    //if (jatek_betolt("teszt.txt")) {
    //    printf ("betoltes ok, itt van a palya: \n");
    //    tabla_kiir();
    //}

    lepes_eltarolas(1, 1, 1);
    lepes_eltarolas(2, 2, 2);
    lepes_eltarolas(3, 3, 3);
    lepesek_kiirasa();

    return 0;
}

