#ifndef SAKK_H
#define SAKK_H

#define PALYAMERET 8

typedef struct {
    char tartalom;
    bool feher;
} babu;

typedef struct {
    char tartalom[4];
    bool foglalt;
    babu mezobabu;
} mezo;

typedef struct {
    bool feher;
    char *nev;
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

void jatekos_lepes();

void tabla_kiir();

void tabla_inicializal();

void tabla_feltolt();

bool jatek_elment(char *filenev);

bool jatek_betolt(char *filenev);

void tabla_test_print();

void input_test();

void convert_coord(int *elso, int *masodik);

bool validate_coord(int *elso, int *masodik);

bool lepes_f();

bool visszalepes_f();

void reset_tartalom(mezo *honnan);

void m_cleanup();

int reverse_coord_s(int *coord);

int reverse_coord_o(int *coord);

#endif //SAKK_H
