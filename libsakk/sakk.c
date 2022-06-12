/*
 * Progalap kotprog
 * Keszitette: Bakk Abel, Bucsu Aron
 */
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "sakk.h"
#include <errno.h>
#include <limits.h>

#define btoi(b) ((b) ? 1 : 0)
#define BUFFER 32

mezo tabla[PALYAMERET][PALYAMERET];
jatekos j[2];

csomopont_t *head = NULL;

int kor = 0;

//Bucsu Aron
char *string_olvas() {
    char *str = malloc(sizeof(char) * BUFFER), *err;
    int pos;
    for (pos = 0; str != NULL && (str[pos] = getchar()) != '\n'; pos++) {
        if (pos % BUFFER == BUFFER - 1) {
            if ((err = realloc(str, sizeof(char) * (BUFFER + pos + 1))) == NULL)
                free(str);
            str = err;
        }
    }
    if (str != NULL)
        str[pos] = '\0';
    return str;
}

//Bucsu Aron
void jatekos_beker() {
    char *szin = "vilagos";

    for (int i = 0; i < 2; i++) {
        if (i > 0) {
            szin = "sotet";
        }

        printf("Adja meg a %s jatekos nevet:\n", szin);
        fgets(j[i].nev, 50, stdin);
        j[i].nev[strlen(j[i].nev) - 1] = '\0';

        if (i < 1) {
            j[i].feher = true;
        } else {
            j[i].feher = false;
        }
    }
}

//Bakk Abel
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

//Bakk Abel
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

//Bakk Abel
void list_torol_elejerol() {
    csomopont_t *tmp = head;
    head = head->kovetkezo;
    free(tmp);
}

//Bucsu Aron
void tabla_inicializal() {
    for (int i = 0; i < PALYAMERET; i++) {
        for (int k = 0; k < PALYAMERET; k++) {
            tabla[i][k].tartalom[0] = '[';
            tabla[i][k].tartalom[1] = '_';
            tabla[i][k].tartalom[2] = ']';
            tabla[i][k].tartalom[3] = '\0';
        }
    }
}

//Bucsu Aron
void tabla_kiir() {
    printf("   ");
    for (int i = 'A'; i < 'A' + PALYAMERET; i++) {
        printf(" %c ", (char) i);
    }
    printf("\n");

    int sorszam = 8;
    for (int i = 0; i < PALYAMERET; i++) {
        for (int k = 0; k < PALYAMERET + 1; k++) {
            if (k == 0) {
                printf(" %d ", sorszam);
                sorszam--;
            } else {
                printf("%s", tabla[i][k - 1].tartalom);
            }
        }
        printf("\n");
    }
}

//Bucsu Aron
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

//Bakk Abel
bool jatek_elment(char *filenev) {
    FILE *output = fopen(filenev, "w");
    for (int i = 0; i < PALYAMERET; i++) {
        for (int j = 0; j < PALYAMERET; j++) {
            fprintf(output, "%c%c%c%c%d\n", tabla[i][j].tartalom[0], tabla[i][j].tartalom[1],
                    tabla[i][j].tartalom[2], tabla[i][j].tartalom[3], btoi(tabla[i][j].foglalt));
        }
    }
    fprintf(output, "%s\n%s\n", j[0].nev, j[1].nev);
    fclose(output);
    return true;
}

//Bakk Abel
bool jatek_betolt(char *filenev) {
    tabla_inicializal();
    FILE *input;
    if (!(input = fopen(filenev, "r"))) {
        return false;
    }
    j[0].feher = true;
    j[1].feher = false;
    for (int i = 0; i < PALYAMERET; i++) {
        for (int j = 0; j < PALYAMERET; j++) {
            int tmp1;
            fscanf(input, "%c%c%c%c%d", &tabla[i][j].tartalom[0], &tabla[i][j].tartalom[1],
                   &tabla[i][j].tartalom[2], &tabla[i][j].tartalom[3], &tmp1);
            tabla[i][j].foglalt = tmp1;
            fgetc(input);
        }
    }
    fgets(j[0].nev, 50, input);
    j[0].nev[strlen(j[0].nev) - 1] = '\0';
    fgets(j[1].nev, 50, input);
    j[1].nev[strlen(j[1].nev) - 1] = '\0';
    fclose(input);
    return true;
}

//Bucsu Aron
bool lepes_interact(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o) {
    char *koordinataBeolvas;
    printf("\nMelyik babuval szeretne lepni / utni? Sor, oszlop (pl. 6C/6c): ");
    koordinataBeolvas = string_olvas();
    *honnan_s = (int) koordinataBeolvas[0] - '0';
    *honnan_o = toupper((int) koordinataBeolvas[1]);
    free(koordinataBeolvas);
    convert_coord(honnan_s, honnan_o);
    if (tabla[*honnan_s][*honnan_o].tartalom[1] == '_') {
        printf("\nUres mezot adott meg!\n");
        return false;
    }
    printf("\nHova szeretne lepni / utni? Sor, oszlop: ");
    koordinataBeolvas = string_olvas();
    *hova_s = (int) koordinataBeolvas[0] - '0';
    *hova_o = toupper((int) koordinataBeolvas[1]);
    free(koordinataBeolvas);
    convert_coord(hova_s, hova_o);
    printf("\n");
    if (!validate_coord(honnan_s, honnan_o) || !validate_coord(hova_s, hova_o)) {
        printf("Nem megfelelo koordinatak, sikertelen lepes!\n");
        return false;
    }
    return true;
}

//Bucsu Aron
bool lepes_f(jatekos j) {
    int honnan_s, honnan_o, hova_s, hova_o;
    if (!lepes_interact(&honnan_s, &honnan_o, &hova_s, &hova_o)) return false;
    if (j.feher) {
        if (tabla[honnan_s][honnan_o].tartalom[1] == 'g' || tabla[honnan_s][honnan_o].tartalom[1] == 'b' ||
            tabla[honnan_s][honnan_o].tartalom[1] == 'h' || tabla[honnan_s][honnan_o].tartalom[1] == 'f' ||
            tabla[honnan_s][honnan_o].tartalom[1] == 'k' || tabla[honnan_s][honnan_o].tartalom[1] == 'v') {
            printf("Nem a sajat figurajaval lep!\n");
            return false;
        }
        if (tabla[hova_s][hova_o].tartalom[1] == 'G' || tabla[hova_s][hova_o].tartalom[1] == 'B' ||
            tabla[hova_s][hova_o].tartalom[1] == 'H' || tabla[hova_s][hova_o].tartalom[1] == 'F' ||
            tabla[hova_s][hova_o].tartalom[1] == 'K' || tabla[hova_s][hova_o].tartalom[1] == 'V') {
            printf("Nem lephetsz a sajat figuradra!\n");
            return false;
        }
    } else {
        if (tabla[honnan_s][honnan_o].tartalom[1] == 'G' || tabla[honnan_s][honnan_o].tartalom[1] == 'B' ||
            tabla[honnan_s][honnan_o].tartalom[1] == 'H' || tabla[honnan_s][honnan_o].tartalom[1] == 'F' ||
            tabla[honnan_s][honnan_o].tartalom[1] == 'K' || tabla[honnan_s][honnan_o].tartalom[1] == 'V') {
            printf("Nem a sajat figurajaval lep!\n");
            return false;
        }
        if (tabla[hova_s][hova_o].tartalom[1] == 'g' || tabla[hova_s][hova_o].tartalom[1] == 'b' ||
            tabla[hova_s][hova_o].tartalom[1] == 'h' || tabla[hova_s][hova_o].tartalom[1] == 'f' ||
            tabla[hova_s][hova_o].tartalom[1] == 'k' || tabla[hova_s][hova_o].tartalom[1] == 'v') {
            printf("Nem lephetsz a sajat figuradra!\n");
            return false;
        }
    }
    switch (tabla[honnan_s][honnan_o].tartalom[1]) {
        case 'G':
        case 'g': {
            if (gyalog_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o, &tabla[honnan_s][honnan_o].tartalom[1])) {
                break;
            } else {
                printf("Sikertelen lepes!\n");
                return false;
            }
        }
        case 'B':
        case 'b': {
            if (bastya_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o)) {
                break;
            } else {
                printf("Sikertelen lepes!\n");
                return false;
            }
        }
        case 'H':
        case 'h': {
            if (huszar_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o)) {
                break;
            } else {
                printf("Sikertelen lepes!\n");
                return false;
            }
        }
        case 'F':
        case 'f': {
            if (futo_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o)) {
                break;
            } else {
                printf("Sikertelen lepes!\n");
                return false;
            }
        }
        case 'V':
        case 'v': {
            if (futo_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o) ||
                bastya_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o)) {
                break;
            } else {
                printf("Sikertelen lepes!\n");
                return false;
            }
        }
        case 'K':
        case 'k': {
            if (kiraly_lepes(&honnan_s, &honnan_o, &hova_s, &hova_o)) {
                break;
            } else {
                printf("Sikertelen lepes!\n");
                return false;
            }
        }
        default: {
            printf("Sikertelen lepes!\n");
            return false;
        }
    }
    tabla[hova_s][hova_o].tartalom[1] = tabla[honnan_s][honnan_o].tartalom[1];
    tabla[hova_s][hova_o].mezobabu = tabla[honnan_s][honnan_o].mezobabu;
    tabla[hova_s][hova_o].foglalt = true;
    lepes lepes_new = {honnan_s, honnan_o, hova_s, hova_o, tabla[hova_s][hova_o].mezobabu, kor};
    list_hozzaad(lepes_new);
    reset_tartalom(&tabla[honnan_s][honnan_o]);
    return true;
}

//Bakk Abel
bool bastya_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o) {
    if ((*honnan_s == *hova_s) || (*honnan_o == *hova_o)) return true;
    return false;
}

//Bakk Abel
bool huszar_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o) {
    if ((*hova_s == (*honnan_s - 2) || *hova_s == (*honnan_s + 2)) &&
        (*hova_o == (*honnan_o - 1) || *hova_o == (*honnan_o + 1)))
        return true;
    if ((*hova_o == (*honnan_o - 2) || *hova_o == (*honnan_o + 2)) &&
        (*hova_s == (*honnan_s + 1) || *hova_s == (*honnan_s - 1)))
        return true;
    return false;
}

//Bakk Abel
bool kiraly_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o) {
    for (int i = *honnan_s - 1; i <= *honnan_s + 1; i++) {
        for (int j = *honnan_o - 1; j <= *honnan_o + 1; j++) {
            if (*hova_s == i && *hova_o == j) return true;
        }
    }
    return false;
}

//Bakk Abel
bool futo_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i - *honnan_s == j - *honnan_o) || (i - *honnan_s == -(j - *honnan_o))) {
                tabla[i][j].ertek = 1;
            } else {
                tabla[i][j].ertek = 0;
            }
        }
    }
    if (tabla[*hova_s][*hova_o].ertek == 1) {
        return true;
    }
    return false;
}

//Bakk Abel
bool gyalog_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o, char *szin) { // vagy utes
    if (*szin == 'G') {
        if (*hova_s >= *honnan_s) return false; //visszafele nem lephet
        if (!tabla[*hova_s][*hova_o].foglalt && *honnan_o == *hova_o &&
            (*hova_s == *honnan_s - 1))
            return true;
        //ugyanabban az oszlopban lep nem foglalt mezore egyet <= lepes
        if (tabla[*hova_s][*hova_o].foglalt && *hova_s == (*honnan_s - 1) &&
            (*hova_o == (*honnan_o - 1) || *hova_o == (*honnan_o + 1)))
            return true;
        //utes csak foglalt mezore lehetseges, egy mezot lephet felfele jobbra vagy balra <= utes
        return false;
    } else {
        if (*hova_s <= *honnan_s) {
            return false;
        } //visszafele nem lephet
        if (!tabla[*hova_s][*hova_o].foglalt && *honnan_o == *hova_o &&
            (*hova_s == *honnan_s + 1))
            return true;
        if (tabla[*hova_s][*hova_o].foglalt && *hova_s == (*honnan_s + 1) &&
            (*hova_o == (*honnan_o - 1) || *hova_o == (*honnan_o + 1)))
            return true;
    }
    return false;
}

//Bakk Abel
bool sancolas_f(jatekos j) {
    if (j.feher) {
        if (tabla[7][3].tartalom[1] == 'K') {
            tabla[7][2].tartalom[1] = 'K';
            tabla[7][2].mezobabu = tabla[7][3].mezobabu;
            tabla[7][2].foglalt = true;
            reset_tartalom(&tabla[7][3]);
            tabla[7][3].tartalom[1] = 'B';
            tabla[7][3].mezobabu = tabla[7][0].mezobabu;
            tabla[7][3].foglalt = true;
            reset_tartalom(&tabla[7][0]);
            return true;
        } else if (tabla[7][5].tartalom[1] == 'K') {
            tabla[7][6].tartalom[1] = 'K';
            tabla[7][6].mezobabu = tabla[7][5].mezobabu;
            tabla[7][6].foglalt = true;
            reset_tartalom(&tabla[7][5]);
            tabla[7][5].tartalom[1] = 'B';
            tabla[7][5].mezobabu = tabla[7][7].mezobabu;
            tabla[7][5].foglalt = true;
            reset_tartalom(&tabla[7][7]);
            return true;
        }
    } else {
        if (tabla[0][3].tartalom[1] == 'k') {
            tabla[0][2].tartalom[1] = 'k';
            tabla[0][2].mezobabu = tabla[0][3].mezobabu;
            tabla[0][2].foglalt = true;
            reset_tartalom(&tabla[0][3]);
            tabla[0][3].tartalom[1] = 'b';
            tabla[0][3].mezobabu = tabla[0][0].mezobabu;
            tabla[0][3].foglalt = true;
            reset_tartalom(&tabla[0][0]);
            return true;
        } else if (tabla[0][5].tartalom[1] == 'k') {
            tabla[0][6].tartalom[1] = 'k';
            tabla[0][6].mezobabu = tabla[0][5].mezobabu;
            tabla[0][6].foglalt = true;
            reset_tartalom(&tabla[0][5]);
            tabla[0][5].tartalom[1] = 'b';
            tabla[0][5].mezobabu = tabla[0][7].mezobabu;
            tabla[0][5].foglalt = true;
            reset_tartalom(&tabla[0][7]);
            return true;
        }
    }
    return false;
}

//Bakk Abel
bool sancolas(jatekos j) {
    if (j.feher) {
        if (tabla[7][4].tartalom[1] == 'K' &&
            ((tabla[7][0].tartalom[1] == 'B' && tabla[7][1].tartalom[1] == '_' && tabla[7][3].tartalom[1] == '_' &&
              tabla[7][2].tartalom[1] == '_')
             || (tabla[7][7].tartalom[1] == 'B' && tabla[7][5].tartalom[1] == '_' && tabla[7][6].tartalom[1] == '_'))) {
            if (lepes_f(j)) {
                if (sancolas_f(j)) return true;
            }
            printf("A sancolas sikertelen!\n");
            return false;
        }

    } else {
        if (tabla[0][4].tartalom[1] == 'k' &&
            ((tabla[0][0].tartalom[1] == 'b' && tabla[0][1].tartalom[1] == '_' && tabla[0][3].tartalom[1] == '_' &&
              tabla[0][2].tartalom[1] == '_')
             || (tabla[0][7].tartalom[1] == 'b' && tabla[0][5].tartalom[1] == '_' && tabla[0][6].tartalom[1] == '_'))) {
            if (lepes_f(j)) {
                if (sancolas_f(j)) return true;
            }
            printf("A sancolas sikertelen!\n");
            return false;
        }
    }
    printf("A sancolas sikertelen!\n");
    return false;
}

//Bakk Abel
bool nyert_e_valaki() {
    bool feher_k, feher_v, fekete_k, fekete_v;
    for (int i = 0; i < PALYAMERET; i++) {
        for (int j = 0; j < PALYAMERET; j++) {
            if (tabla[i][j].tartalom[1] == 'k') feher_k = true;
            if (tabla[i][j].tartalom[1] == 'v') feher_v = true;
            if (tabla[i][j].tartalom[1] == 'K') fekete_k = true;
            if (tabla[i][j].tartalom[1] == 'V') fekete_v = true;
        }
    }
    if (!feher_k && !feher_v) {
        printf("\n\nA jatekot %s nyerte!\n\n", j[1].nev);
        return true;
    }
    if (!fekete_k && !fekete_v) {
        printf("\n\nA jatekot %s nyerte!\n\n", j[0].nev);
        return true;
    }
    return false;
}

//Bucsu Aron
bool atvaltozas(jatekos j) {
    char milyen_karakter;
    for (int i = 0; i < PALYAMERET; i++) {
        if (j.feher) {
            if (tabla[0][i].tartalom[1] == 'G') {
                if (atvaltozas_f(j, &milyen_karakter)) {
                    tabla[0][i].tartalom[1] = milyen_karakter;
                    return true;
                }
                printf("Nem tud meg atvaltozni!\n");
                return false;
            }
        } else {
            if (tabla[PALYAMERET - 1][i].tartalom[1] == 'g') {
                if (atvaltozas_f(j, &milyen_karakter)) {
                    if (atvaltozas_f(j, &milyen_karakter)) {
                        tabla[PALYAMERET - 1][i].tartalom[1] = milyen_karakter;
                        return true;
                    }
                    printf("Nem tud meg atvaltozni!\n");
                    return false;
                }
            }
        }
    }
    printf("Nem tud meg atvaltozni!\n");
    return false;
}

//Bucsu Aron
bool atvaltozas_f(jatekos j, char *milyen_karakter) {
    char *tmp;
    printf("Mive szeretne atvaltozni? [V]ezer, [B]astya, [F]uto, [H]uszar: ");
    fflush(stdin);
    tmp = string_olvas();

    if (!strlen(strchr("vbfhVBFH", tmp[0]))) {
        printf("Helytelen opcio!\n");
        free(tmp);
        return false;
    }
    if (j.feher) {
        *milyen_karakter = (char) toupper((int) tmp[0]);
    } else {
        *milyen_karakter = (char) tolower((int) tmp[0]);
    }
    free(tmp);
    return true;
}

//Bakk Abel
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

//Bucsu Aron
void convert_coord(int *elso, int *masodik) {
    *elso = PALYAMERET - *elso;
    *masodik = *masodik - (int) 'A';
}

//Bucsu Aron
int reverse_coord_s(int *coord) {
    int res = abs(*coord - PALYAMERET);
    return res;
}

//Bucsu Aron
int reverse_coord_o(int *coord) {
    int res = *coord + (int) 'A';
    return res;
}

//Bucsu Aron
bool validate_coord(int *elso, int *masodik) {
    return *elso >= 0 && *elso < PALYAMERET && *masodik >= 0 && *masodik < PALYAMERET;
}

//Bucsu Aron
void reset_tartalom(mezo *honnan) {
    honnan->tartalom[0] = '[';
    honnan->tartalom[1] = '_';
    honnan->tartalom[2] = ']';
    honnan->tartalom[3] = '\0';
    honnan->foglalt = false;
}

//Bucsu Aron
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

//Bakk Abel
bool visszalepes_interact() {
    int n;
    printf("Hanyat szeretne visszalepni: ");
    char *tmp = string_olvas();
    n = (int) tmp[0] - '0';
    free(tmp);
    if (n > list_count()) {
        printf("Nem lehetseges ennyit visszalepni!\n");
        return false;
    }
    while (n > 0) {
        visszalepes_f();
        n--;
    }
    return true;
}

//Bakk Abel
bool beolvas_int(int *szam) {
    fflush(stdin);
    long tmp;
    char buf[512];
    if (!fgets(buf, 512, stdin)) return false;
    char *end;
    errno = 0;
    tmp = strtol(buf, &end, 10);
    if (errno == ERANGE || end == buf || (*end && *end != '\n')) return false;
    if (tmp < INT_MIN || tmp > INT_MAX) return false;
    *szam = (int) tmp;
    return true;
}

//Bucsu Aron
jatekos get_jatekos(bool feher) {
    return (feher) ? j[0] : j[1];
}

//Bucsu Aron
mezo *get_mezo(int s, int o) {
    return &tabla[s][o];
}

//Bakk Abel
void lepes_teszteleshez(int honnan_s, int honnan_o, int hova_s, int hova_o) {
    tabla[hova_s][hova_o].tartalom[1] = tabla[honnan_s][honnan_o].tartalom[1];
    tabla[hova_s][hova_o].mezobabu = tabla[honnan_s][honnan_o].mezobabu;
    tabla[hova_s][hova_o].foglalt = true;
    reset_tartalom(&tabla[honnan_s][honnan_o]);
}

//Bakk Abel
void m_cleanup() {
    while (list_count()) {
        list_torol_elejerol();
    }
}
