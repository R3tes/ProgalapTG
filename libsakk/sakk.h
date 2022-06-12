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

void list_hozzaad(lepes milyen_lepes); //tesztelve

void list_print();

void list_torol_elejerol(); //tesztelve

void jatekos_beker(); //tesztelve

void tabla_kiir();

void tabla_inicializal(); //tesztelve

void tabla_feltolt(); //tesztelve

bool jatek_elment(char *filenev);

bool jatek_betolt(char *filenev);

void convert_coord(int *elso, int *masodik); //tesztelve

bool validate_coord(int *elso, int *masodik); //tesztelve

bool lepes_f(jatekos j); //tesztelve

void visszalepes_f(); //tesztelve

void reset_tartalom(mezo *honnan); //tesztelve

void m_cleanup();

int reverse_coord_s(int *coord); //tesztelve

int reverse_coord_o(int *coord); //tesztelve

int list_count(); //tesztelve

bool visszalepes_interact(); //tesztelve

bool lepes_interact(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o); //tesztelve

bool atvaltozas(jatekos j); //tesztelve

bool atvaltozas_f(jatekos j, char *milyen_karakter); //tesztelve

bool sancolas(jatekos j); //tesztelve

bool sancolas_f(jatekos j); //tesztelve

bool gyalog_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o, char *szin); //tesztelve

bool bastya_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o); //tesztelve

bool huszar_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o); //tesztelve

bool futo_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o); //tesztelve

bool kiraly_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o); //tesztelve

bool nyert_e_valaki(); //tesztelve

bool beolvas_int(int *szam); //tesztelve

jatekos get_jatekos(bool feher);

mezo *get_mezo(int s, int o);

void lepes_teszteleshez(int honnan_s, int honnan_o, int hova_s, int hova_o);

char *string_olvas(); //tesztelve

#endif //SAKK_H
