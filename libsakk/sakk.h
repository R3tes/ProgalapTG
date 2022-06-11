#ifndef SAKK_H
#define SAKK_H

#include <stdbool.h>

#define PALYAMERET 8

typedef struct {
    char tartalom;
    bool feher;
} babu;

typedef struct {
    char tartalom[4];
    bool foglalt;
    babu mezobabu;
    int ertek; //huszar lehetseges lepesei
} mezo;

typedef struct {
    bool feher;
    char nev[51];
} jatekos;

typedef struct lepes {
    int honnan_s, honnan_o, hova_s, hova_o;
    babu mezobabu;
    int kor;
} lepes;

struct csomopont {
    lepes aktualis_lepes;
    struct csomopont *kovetkezo;
};

typedef struct csomopont csomopont_t;

void list_hozzaad(lepes milyen_lepes);

void list_print();

void list_torol_elejerol();

void jatekos_beker();

void tabla_kiir();

void tabla_inicializal();

void tabla_feltolt();

bool jatek_elment(char *filenev);

bool jatek_betolt(char *filenev);

void convert_coord(int *elso, int *masodik);

bool validate_coord(int *elso, int *masodik);

bool lepes_f(jatekos j);

void visszalepes_f();

void reset_tartalom(mezo *honnan);

void m_cleanup();

int reverse_coord_s(int *coord);

int reverse_coord_o(int *coord);

int list_count();

bool visszalepes_interact();

bool lepes_interact(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o);

bool atvaltozas(jatekos j);

bool atvaltozas_f(jatekos j, char *milyen_karakter);

bool sancolas(jatekos j);

bool sancolas_f(jatekos j);

bool gyalog_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o, char *szin);

bool bastya_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o);

bool huszar_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o);

bool futo_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o);

bool kiraly_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o);

bool nyert_e_valaki();

bool beolvas_int(int *szam);

jatekos get_jatekos(bool feher);

char *string_olvas();

#endif //SAKK_H
