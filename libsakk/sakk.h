/*
 * Progalap kotprog
 * Keszitette: Bakk Abel, Bucsu Aron
 */
#ifndef SAKK_H
#define SAKK_H

#include <stdbool.h>

#define PALYAMERET 8

//Bucsu Aron
typedef struct {
    char tartalom;
    bool feher;
} babu;

//Bucsu Aron
typedef struct {
    char tartalom[4];
    bool foglalt;
    babu mezobabu;
    int ertek; //huszar lehetseges lepesei
} mezo;

//Bucsu Aron
typedef struct {
    bool feher;
    char nev[51];
} jatekos;

//Bakk Abel
typedef struct lepes {
    int honnan_s, honnan_o, hova_s, hova_o;
    babu mezobabu;
    int kor;
} lepes;

//Bakk Abel
struct csomopont {
    lepes aktualis_lepes;
    struct csomopont *kovetkezo;
};

typedef struct csomopont csomopont_t;

//Bakk Abel
void list_hozzaad(lepes milyen_lepes); //tesztelve

//Bakk Abel
void list_print();

//Bakk Abel
void list_torol_elejerol(); //tesztelve

//Bucsu Aron
void jatekos_beker(); //tesztelve

//Bucsu Aron
void tabla_kiir();

//Bucsu Aron
void tabla_inicializal(); //tesztelve

//Bucsu Aron
void tabla_feltolt(); //tesztelve

//Bakk Abel
bool jatek_elment(char *filenev);

//Bakk Abel
bool jatek_betolt(char *filenev);

//Bucsu Aron
void convert_coord(int *elso, int *masodik); //tesztelve

//Bucsu Aron
bool validate_coord(int *elso, int *masodik); //tesztelve

//Bucsu Aron
bool lepes_f(jatekos j); //tesztelve

//Bakk Abel
void visszalepes_f(); //tesztelve

//Bucsu Aron
void reset_tartalom(mezo *honnan); //tesztelve

//Bakk Abel
void m_cleanup();

//Bucsu Aron
int reverse_coord_s(int *coord); //tesztelve

//Bucsu Aron
int reverse_coord_o(int *coord); //tesztelve

//Bucsu Aron
int list_count(); //tesztelve

//Bakk Abel
bool visszalepes_interact(); //tesztelve

//Bucsu Aron
bool lepes_interact(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o); //tesztelve

//Bucsu Aron
bool atvaltozas(jatekos j); //tesztelve

//Bucsu Aron
bool atvaltozas_f(jatekos j, char *milyen_karakter); //tesztelve

//Bakk Abel
bool sancolas(jatekos j); //tesztelve

//Bakk Abel
bool sancolas_f(jatekos j); //tesztelve

//Bakk Abel
bool gyalog_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o, char *szin); //tesztelve

//Bakk Abel
bool bastya_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o); //tesztelve

//Bakk Abel
bool huszar_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o); //tesztelve

//Bakk Abel
bool futo_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o); //tesztelve

//Bakk Abel
bool kiraly_lepes(int *honnan_s, int *honnan_o, int *hova_s, int *hova_o); //tesztelve

//Bakk Abel
bool nyert_e_valaki(); //tesztelve

//Bakk Abel
bool beolvas_int(int *szam); //tesztelve

//Bucsu Aron
jatekos get_jatekos(bool feher);

//Bucsu Aron
mezo *get_mezo(int s, int o);

//Bakk Abel
void lepes_teszteleshez(int honnan_s, int honnan_o, int hova_s, int hova_o);

//Bucsu Aron
char *string_olvas(); //tesztelve

#endif //SAKK_H
