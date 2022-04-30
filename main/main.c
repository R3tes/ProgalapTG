#include <stdio.h>
#include <stdbool.h>

#include "sakk.h"

#include <wchar.h>
#include <locale.h>

int main() {
    mezo **tabla = tabla_letrehoz();
    tabla_inicializal(tabla);
    tabla_kiir(tabla);

    setlocale(LC_CTYPE, "");
    for (wchar_t p = 0x2654; p <= 0x265F; p++) {
        wprintf(L"%lc\n", p);
    }
    return 0;
}

