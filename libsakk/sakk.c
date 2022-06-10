#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
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
    } else {
        res->kovetkezo = head;
        head = res;
    }
}

void list_print() {
    int count = 1;
    if (head == NULL) return;
    csomopont_t *temp = head;
    while (temp != NULL) {
        printf("%d. Honnan: %d%c. Hova: %d%c. Mivel: %c.\n", count, reverse_coord_s(&temp->aktualis_lepes.honnan_s),
               (char) reverse_coord_o(&temp->aktualis_lepes.honnan_o),
               reverse_coord_s(&temp->aktualis_lepes.hova_s), (char) reverse_coord_o(&temp->aktualis_lepes.hova_o),
               temp->aktualis_lepes.mezobabu.tartalom);
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

    printf("\nA vilagos jatekos neve: %s %d\n", j[0].nev, btoi(j[0].feher));
    printf("A sotet jatekos neve: %s %d\n", j[1].nev, btoi(j[1].feher));
}

void tabla_feltolt() {
    char roviditesek[9] = "bhfvkfhb";
    for (int i = 0; i < PALYAMERET; i++) {
        int sorindex = 0;
        for (int j = 0; j < PALYAMERET; j++) {
            bool set = true;
            babu ujbabu;
            ujbabu.feher = (i < 5) ? false : true;

            switch (i) {
                case 1:
                case 6: {
                    ujbabu.tartalom = (i == 1) ? 'g' : 'G';
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

bool jatek_elment(char *filenev, bool jatekos) {

    FILE *output = fopen(filenev, "w");

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

    j[0].feher = true;
    j[1].feher = false;


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

bool lepes_interact(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o) {
    char tmp;
    printf("\nMelyik babuval szeretne lepni / utni? Sor, oszlop (pl. 6C/6c): ");
    scanf("%d%c", honnan_s, &tmp);
    *honnan_o = toupper((int) tmp);
    getc(stdin);
    convert_coord(honnan_s, honnan_o);

    if (tabla[*honnan_s][*honnan_o].tartalom[1] == '_') {
        printf("\nUres mezot adott meg!\n");
        return false;
    }

    printf("\nHova szeretne lepni / utni? Sor, oszlop: ");
    scanf("%d%c", hova_s, &tmp);
    *hova_o = toupper((int) tmp);

    printf("\n");

    convert_coord(hova_s, hova_o);

    if (!validate_coord(honnan_s, honnan_o) || !validate_coord(hova_s, hova_o)) {
        printf("Nem megfelelo koordinatak, sikertelen lepes!\n");
        return false;
    }
    return true;
}

bool lepes_f(jatekos j) {
    int honnan_s, honnan_o, hova_s, hova_o;
    if (!lepes_interact(&honnan_s, &honnan_o, &hova_s, &hova_o)) return false;
    if (j.feher) {
        if (!strlen(strchr("GBHFVK", tabla[honnan_s][honnan_o].tartalom[1]))) {
            printf("Nem a sajat figurajaval lep!\n");
            return false;
        }
    } else {
        if (!strlen(strchr("gbhfvk", tabla[honnan_s][honnan_o].tartalom[1]))) {
            printf("Nem a sajat figurajaval lep!\n");
            return false;
        }
    }
    // meg tobb ellenorzes
    switch (tabla[honnan_s][honnan_o].tartalom[1]) {

    }
    tabla[hova_s][hova_o].tartalom[1] = tabla[honnan_s][honnan_o].tartalom[1];
    tabla[hova_s][hova_o].mezobabu = tabla[honnan_s][honnan_o].mezobabu;
    tabla[hova_s][hova_o].foglalt = true;
    lepes lepes_new = {honnan_s, honnan_o, hova_s, hova_o, tabla[hova_s][hova_o].mezobabu, kor};
    list_hozzaad(lepes_new);
    reset_tartalom(&tabla[honnan_s][honnan_o]);
    return true;
}

bool sancolas_f(jatekos j) {
    if (j.feher) {
        if (tabla[7][2].tartalom[1] == 'K') {
            tabla[7][3].tartalom[1] = 'B';
            tabla[7][3].mezobabu = tabla[7][0].mezobabu;
            tabla[7][3].foglalt = true;
            reset_tartalom(&tabla[7][0]);
            return true;
        } else if (tabla[7][6].tartalom[1] == 'K') {
            tabla[7][5].tartalom[1] = 'B';
            tabla[7][5].mezobabu = tabla[7][7].mezobabu;
            tabla[7][5].foglalt = true;
            reset_tartalom(&tabla[7][7]);
            return true;
        }
    } else {
        if (tabla[0][2].tartalom[1] == 'k') {
            tabla[0][3].tartalom[1] = 'b';
            tabla[0][3].mezobabu = tabla[0][0].mezobabu;
            tabla[0][3].foglalt = true;
            reset_tartalom(&tabla[0][0]);
            return true;
        } else if (tabla[7][6].tartalom[1] == 'k') {
            tabla[0][5].tartalom[1] = 'b';
            tabla[0][5].mezobabu = tabla[0][7].mezobabu;
            tabla[0][5].foglalt = true;
            reset_tartalom(&tabla[0][7]);
            return true;
        }
    }
    return false;
}

bool sancolas(jatekos j) {

    if (j.feher) {
        if (tabla[7][4].tartalom[1] == 'K' && (tabla[7][0].tartalom[1] == 'B' || tabla[7][7].tartalom[1] == 'B') &&
            tabla[7][1].tartalom[1] == '_' && tabla[7][3].tartalom[1] == '_' &&
            tabla[7][5].tartalom[1] == '_' && tabla[7][2].tartalom[1] == '_' && tabla[7][6].tartalom[1] == '_') {
            if (lepes_f(j)) {
                if(sancolas_f(j)) return true;
            }
            printf("A sancolas sikertelen!\n");
            return false;
        }

    } else {
        if (tabla[0][4].tartalom[1] == 'k' && (tabla[0][0].tartalom[1] == 'b' || tabla[0][7].tartalom[1] == 'b') &&
            tabla[0][1].tartalom[1] == '_' && tabla[0][3].tartalom[1] == '_' &&
            tabla[0][5].tartalom[1] == '_' && tabla[0][2].tartalom[1] == '_' && tabla[0][6].tartalom[1] == '_') {
            if (lepes_f(j)) {
                if (sancolas_f(j)) return true;
            }
            printf("A sancolas sikertelen!\n");
            return false;
        }
    }

    return true;
}

bool atvaltozas(jatekos j) {
    char milyen_karakter;
    for (int i = 0; i < PALYAMERET; i++) {
        if (j.feher) {
            if (tabla[0][i].tartalom[1] == 'G') {
                if (atvaltozas_f(j, &milyen_karakter)) {
                    tabla[0][i].tartalom[1] = milyen_karakter;
                    return true;
                }
                return false;
            }
        } else {
            if (tabla[PALYAMERET - 1][i].tartalom[1] == 'g') {
                if (atvaltozas_f(j, &milyen_karakter)) {
                    if (atvaltozas_f(j, &milyen_karakter)) {
                        tabla[PALYAMERET - 1][i].tartalom[1] = milyen_karakter;
                        return true;
                    }
                    return false;
                }
            }
        }
    }
    return false;
}

bool atvaltozas_f(jatekos j, char *milyen_karakter) {
    char tmp;
    printf("Mive szeretne atvaltozni? [V]ezer, [B]astya, [F]uto, [H]uszar: ");
    fflush(stdin); //TODO nem biztos h kell
    scanf("%c", &tmp);
    if (!strlen(strchr("vbfhVBFH", tmp))) {
        printf("Helytelen opcio!\n");
        return false;
    }
    if (j.feher) {
        *milyen_karakter = (char) toupper((int) tmp);
    } else {
        *milyen_karakter = (char) tolower((int) tmp);
    }
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

jatekos get_jatekos(bool feher) {
    return (feher) ? j[0] : j[1];
}

void m_cleanup() {
    while (list_count()) {
        list_torol_elejerol();
    }
    free(j[0].nev);
    free(j[1].nev);
}
