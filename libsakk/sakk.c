#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#include <wchar.h>
#include <locale.h>

#include "sakk.h"

mezo **tabla_letrehoz() {
    mezo **tabla = (mezo **) malloc(PALYAMERET * sizeof(mezo *));
    for (int i = 0; i < PALYAMERET; i++) {
        tabla[i] = (mezo *) malloc(PALYAMERET * sizeof(mezo));
    }
    return tabla;
}

void tabla_inicializal(mezo **tabla) {
    for (int i = 0; i < PALYAMERET; i++) {
        for (int j = 0; j < PALYAMERET; j++) {
            tabla[i][j].tartalom[0] = '[';
            tabla[i][j].tartalom[1] = '_';
            tabla[i][j].tartalom[2] = ']';
        }
    }
}


void tabla_kiir(mezo **tabla) {
    printf("   ");
    for (char i = 'A'; i < 'A' + PALYAMERET; i++) {
        printf(" %c ", i);
    }
    printf("\n");

    int sorszam = 8;
    for (int i = 0; i < PALYAMERET; i++) {
        for (int j = 0; j < PALYAMERET + 1; j++) {
            if (j == 0) {
                printf(" %d ", sorszam);
                sorszam--;
            } else {
                printf("%s", tabla[i][j - 1].tartalom);
            }
        }
        printf("\n");
    }
}
