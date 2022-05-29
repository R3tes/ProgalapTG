#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>
#include "sakk.h"

mezo tabla[PALYAMERET][PALYAMERET];
jatekos j;

struct lepes *fej = NULL;
struct lepes *jelenlegi = NULL;

void jatekos_beker() {

    char *szin = "vilagos";

    for (int i = 0; i < 2; i++) {
        j[i].nev = (char *) malloc(50 * sizeof(char *));

        if (i > 0) {
            szin = "sotet";
        }

        printf("Adja meg a %s jatekos nevet:\n", szin);
        scanf("%s", j[i].nev);

        if (i < 1) {
            j[i].feher = true;
        } else {
            j[i].feher = false;
        }
    }

}

void lepesek_kiirasa() {                    //tesztekhez
    struct lepes *mutato = fej;

    while (mutato != NULL) {
        printf("(%d, %d, %d) ", mutato->sor, mutato->oszlop, mutato->kor);
        mutato = mutato->kovetkezo;
    }
}

void lepes_eltarolas(int sor, int oszlop, int kor) {

    struct lepes *aktualis = (struct lepes*) malloc(sizeof(struct lepes));

    aktualis->sor = sor;
    aktualis->oszlop = oszlop;
    aktualis->kor=kor;

    aktualis->kovetkezo = fej;

    fej = aktualis;
}

void lepesek(){
    while (1){
        
    }
}

void tabla_inicializal() {
    for (int i = 0; i < PALYAMERET; i++) {
        for (int j = 0; j < PALYAMERET; j++) {
            tabla[i][j].tartalom[0] = '[';
            tabla[i][j].tartalom[1] = '_';
            tabla[i][j].tartalom[2] = ']';
            tabla[i][j].tartalom[3] = '\0';
        }
    }
}

void tabla_kiir() {
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

void tabla_feltolt() {
    char roviditesek[9] = "blfkvflb";
    for (int i = 0; i < PALYAMERET; i++) {
        int sorindex = 0;
        for (int j = 0; j < PALYAMERET; j++) {
            bool set = true;
            babu ujbabu;
            ujbabu.pos_i = i;
            ujbabu.pos_j = j;
            ujbabu.feher = (i < 5) ? false : true;

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

bool jatek_elment(char *filenev) {

    FILE *output = fopen(filenev, "w");

    //TODO meg kell: jatekosok nevei, lepesek listaja; jelenleg kizarolag: tabla

    for (int i = 0; i < PALYAMERET; i++) {
        for (int j = 0; j < PALYAMERET; j++) {
            /* format: tartalom foglalt babu_tartalom babu_pos_i babu_pos_j babu_feher\n */
            fprintf(output, "%c%c%c%c%d%c%d%d%d\n", tabla[i][j].tartalom[0], tabla[i][j].tartalom[1],
                    tabla[i][j].tartalom[2], tabla[i][j].tartalom[3], tabla[i][j].foglalt,
                    tabla[i][j].mezobabu.tartalom, tabla[i][j].mezobabu.pos_i, tabla[i][j].mezobabu.pos_j,
                    tabla[i][j].mezobabu.feher);
        }
    }

    fclose(output);

    return true;
}

bool jatek_betolt(char *filenev) {

    FILE *input;

    if (!(input = fopen(filenev, "r"))) {
        return false;
    }

    //TODO ugyanazokat potolni, mint az elozonel

    for (int i = 0; i < PALYAMERET; i++) {
        for (int j = 0; j < PALYAMERET; j++) {
            fscanf(input, "%c%c%c%c%d%c%d%d%d*", &tabla[i][j].tartalom[0], &tabla[i][j].tartalom[1],
                   &tabla[i][j].tartalom[2], &tabla[i][j].tartalom[3], &tabla[i][j].foglalt,
                   &tabla[i][j].mezobabu.tartalom, &tabla[i][j].mezobabu.pos_i, &tabla[i][j].mezobabu.pos_j,
                   &tabla[i][j].mezobabu.feher);
        }
    }

    return true;

}
