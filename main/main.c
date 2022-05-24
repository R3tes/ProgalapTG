#include <stdio.h>
#include <stdbool.h>
#include "sakk.h"

int main() {

    mezo **tabla = tabla_letrehoz();
    tabla_inicializal(tabla);
    tabla_feltolt(tabla);
    tabla_kiir(tabla);

    return 0;
}

