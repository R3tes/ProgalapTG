#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>
#include "sakk.h"

#define btoi(b) ((b) ? 1 : 0)

mezo tabla[PALYAMERET][PALYAMERET];
jatekos j[2];

csomopont_t *head = NULL;

int kor = 0;

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

void list_hozzaad(lepes milyen_lepes) {
    csomopont_t *res = (csomopont_t *) malloc(1 * sizeof(csomopont_t));
    res->aktualis_lepes = milyen_lepes;
    res->kovetkezo = NULL;
    if (head == NULL) {
        head = res;
    }
    else {
        res->kovetkezo = head;
        head = res;
    }
}

int list_count() {
    if (head == NULL) return 0;
    int res = 0;
    csomopont_t *temp = head;
    while (temp != NULL) {
        res++;
        temp = temp->kovetkezo;
    }
    return res;
}

void list_print() {
    int count = 1;
    if (head == NULL) return;
    csomopont_t *temp = head;
    while (temp != NULL) {
        printf("%d. Honnan: %d%c. Hova: %d%c. Mivel: %c.\n", count, reverse_coord_s(&temp->aktualis_lepes.honnan_s), (char) reverse_coord_o(&temp->aktualis_lepes.honnan_o),
                                                        reverse_coord_s(&temp->aktualis_lepes.hova_s), (char) reverse_coord_o(&temp->aktualis_lepes.hova_o), temp->aktualis_lepes.mezobabu.tartalom);
        count++;
        temp = temp->kovetkezo;
    }
}

void list_torol_elejerol() {
    csomopont_t *tmp = head;
    head = head->kovetkezo;
    free(tmp);
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

    printf("A vilagos jatekos neve: %s %d\n", j[0].nev, btoi(j[0].feher));
    printf("A sotet jatekos neve: %s %d\n", j[1].nev, btoi(j[1].feher));
}

void tabla_feltolt() {
    char roviditesek[9] = "blfkvflb";
    for (int i = 0; i < PALYAMERET; i++) {
        int sorindex = 0;
        for (int j = 0; j < PALYAMERET; j++) {
            bool set = true;
            babu ujbabu;
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
            fprintf(output, "%c%c%c%c%d%c%d\n", tabla[i][j].tartalom[0], tabla[i][j].tartalom[1],
                    tabla[i][j].tartalom[2], tabla[i][j].tartalom[3], tabla[i][j].foglalt,
                    tabla[i][j].mezobabu.tartalom, btoi(tabla[i][j].mezobabu.feher));
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
            int tmp1, tmp2;
            fscanf(input, "%c%c%c%c%d%c%d*", &tabla[i][j].tartalom[0], &tabla[i][j].tartalom[1],
                   &tabla[i][j].tartalom[2], &tabla[i][j].tartalom[3], &tmp1,
                   &tabla[i][j].mezobabu.tartalom, &tmp2);
            tabla[i][j].foglalt = tmp1;
            tabla[i][j].mezobabu.feher = tmp2;
        }
    }

    return true;

}

void tabla_test_print() {
    for (int i = 0; i < PALYAMERET; i++) {
        for (int j = 0; j < PALYAMERET; j++) {
            printf("%c ", tabla[i][j].tartalom[1]);
        }
        printf("\n");
    }
}

void input_test() {
    int elso, masodik;
    char temp;
    printf("Sor: ");
    scanf("%d", &elso);
    getc(stdin);
    printf("Oszlop: ");
    scanf("%c", &temp);
    masodik = toupper((int)temp);
    convert_coord(&elso, &masodik);
    if (validate_coord(&elso, &masodik)) {
        printf("sor: %d, oszlop: %d\n", elso, masodik);
    } else {
        printf("hibas koordinatak\n");
    }
}

bool lepes_f() {
    int honnan_s, honnan_o, hova_s, hova_o;
    char tmp;
    printf("Melyik babuval szeretne lepni? Sor, oszlop (pl. 6C): ");
    scanf("%d%c", &honnan_s, &tmp);
    honnan_o = toupper((int)tmp);
    getc(stdin);
    printf("Hova szeretne lepni? Sor, oszlop: ");
    scanf("%d%c", &hova_s, &tmp);
    hova_o = toupper((int)tmp);
    convert_coord(&honnan_s, &honnan_o);
    convert_coord(&hova_s, &hova_o);
    if (!validate_coord(&honnan_s, &honnan_o) || !validate_coord(&hova_s, &hova_o) || tabla[hova_s][hova_o].foglalt) {
        printf("Nem megfelelo koordinatak vagy a mezo foglalt, sikertelen lepes!\n");
        return false;
    }
    tabla[hova_s][hova_o].tartalom[1] = tabla[honnan_s][honnan_o].tartalom[1];
    tabla[hova_s][hova_o].mezobabu = tabla[honnan_s][honnan_o].mezobabu;
    tabla[hova_s][hova_o].foglalt = true;
    lepes lepes_new = {honnan_s, honnan_o, hova_s, hova_o, tabla[hova_s][hova_o].mezobabu, kor};
    list_hozzaad(lepes_new);
    reset_tartalom(&tabla[honnan_s][honnan_o]);
    return true;
}

void visszalepes_f() {
    if (head == NULL) {
        printf("Visszalepes sikertelen!\n");
        return;
    }
    csomopont_t *temp = head;
    tabla[temp->aktualis_lepes.honnan_s][temp->aktualis_lepes.honnan_o].tartalom[1] = temp->aktualis_lepes.mezobabu.tartalom;
    tabla[temp->aktualis_lepes.honnan_s][temp->aktualis_lepes.honnan_o].foglalt = true;
    reset_tartalom(&tabla[temp->aktualis_lepes.hova_s][temp->aktualis_lepes.hova_o]);
    tabla[temp->aktualis_lepes.hova_s][temp->aktualis_lepes.hova_o].foglalt = false;
    list_torol_elejerol();
}

void convert_coord(int *elso, int *masodik) {
    *elso = PALYAMERET - *elso;
    *masodik = *masodik - (int) 'A';
}

int reverse_coord_s(int *coord) {
    int res = abs(*coord - PALYAMERET);
    return res;
}

int reverse_coord_o(int *coord) {
    int res = *coord + (int) 'A';
    return res;
}

bool validate_coord(int *elso, int *masodik) {
    return *elso >= 0 && *elso < PALYAMERET && *masodik >= 0 && *masodik < PALYAMERET;
}

void reset_tartalom(mezo *honnan) {
    honnan->tartalom[0] = '[';
    honnan->tartalom[1] = '_';
    honnan->tartalom[2] = ']';
    honnan->tartalom[3] = '\0';
    honnan->foglalt = false;
}

void visszalepes_interact(int n) {
    if (n > list_count()) {
        printf("Nem lehetseges ennyit visszalepni!\n");
        return;
    }
    while (n > 0) {
        visszalepes_f();
        n--;
    }
}

void m_cleanup() {
    free(j[0].nev);
    free(j[1].nev);
}
