#ifndef SAKK_H
#define SAKK_H

#define PALYAMERET 8

typedef struct {
    char tartalom;
    short int pos_i, pos_j;
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
} jatekos[2];

typedef struct lepes {
    int oszlop;
    int sor;
    int kor;
    struct lepes* kovetkezo;
}lepes;

void lepesek_kiirasa();

void lepes_eltarolas();

void jatekos_beker();

void jatekos_lepes();

void tabla_kiir();

void tabla_inicializal();

void tabla_feltolt();

bool jatek_elment(char *filenev);

bool jatek_betolt(char *filenev);

#endif //SAKK_H
