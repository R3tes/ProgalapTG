#include <stdio.h>
#include <stdbool.h>
#include "sakk.h"

int main() {

<<<<<<< HEAD
    tabla_inicializal();
    tabla_feltolt();
    tabla_kiir();
    //if (jatek_elment("teszt.txt")) printf("mentes done\n");
    //if (jatek_betolt("teszt.txt")) {
    //    printf ("betoltes ok, itt van a palya: \n");
    //    tabla_kiir();
    //}
=======
    jatekos_beker();
    mezo **tabla = tabla_letrehoz();
    tabla_inicializal(tabla);
    tabla_feltolt(tabla);
    tabla_kiir(tabla);
>>>>>>> a142f47268e77359745466078cf18dec845a9b71

    return 0;
}

