#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>
#include "sakk.h"

jatekos j;

mezo **tabla_letrehoz() {
    mezo **tabla = (mezo **) malloc(PALYAMERET * sizeof(mezo *));
    for (int i = 0; i < PALYAMERET; i++) {
        tabla[i] = (mezo *) malloc(PALYAMERET * sizeof(mezo));
    }
    return tabla;
}

void jatekos_beker() {

    char *szin = "vilagos";

    for (int i = 0; i < 2; i++) {
        j[i].nev = (char *) malloc(50 * sizeof(char *));

        if (i > 0) {
            szin = "sotet";
        }

        printf("Adja meg a %s jatekos nevet:\n", szin);
        scanf("%s", j[i].nev);

        if (i < 0) {
            j[i].feher = true;
        } else {
            j[i].feher = false;
        }
    }

}

void tabla_inicializal(mezo **tabla) {
    for (int i = 0; i < PALYAMERET; i++) {
        for (int j = 0; j < PALYAMERET; j++) {
            tabla[i][j].tartalom[0] = '[';
            tabla[i][j].tartalom[1] = '_';
            tabla[i][j].tartalom[2] = ']';
            tabla[i][j].tartalom[3] = '\0';
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

    printf("A vilagos jatekos neve: %s %d\n", j[0].nev, j[0].feher);
    printf("A sotet jatekos neve: %s %d\n", j[1].nev, j[1].feher);
}

void tabla_feltolt(mezo **tabla) {
    char roviditesek[9] = "blfkvflb";
    for (int i = 0; i < PALYAMERET; i++) {
        int sorindex = 0;
        for (int j = 0; j < PALYAMERET; j++) {
            bool set = true;
            babu ujbabu;
            ujbabu.pos_i = i;
            ujbabu.pos_j = j;
            ujbabu.feher == (i < 5) ? false : true;

            switch (i) {
                case 1:
                case 6: {
                    ujbabu.tartalom = (i == 1) ? 'p' : 'P';
                    break;
                }

                case 0:
                case 7: {
                    ujbabu.tartalom = (i == 0) ? roviditesek[sorindex] : toupper(roviditesek[sorindex]);
                    sorindex++;
                    if (sorindex == 8) {
                        sorindex = 0;
                    }
                    break;
                }

                default:
                    set = false;
            }

            if (set) {
                tabla[i][j].mezobabu = ujbabu;
                tabla[i][j].foglalt = true;
                tabla[i][j].tartalom[1] = ujbabu.tartalom;
            }
        }
    }

}
