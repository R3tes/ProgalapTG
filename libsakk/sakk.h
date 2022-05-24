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

<<<<<<< HEAD
void tabla_kiir();
=======
typedef struct {
    bool feher;
    char *nev;
} jatekos[2];

void jatekos_beker();

void tabla_kiir(mezo **tabla);
>>>>>>> a142f47268e77359745466078cf18dec845a9b71

void tabla_inicializal();

void tabla_feltolt();

bool jatek_elment(char *filenev);

bool jatek_betolt(char *filenev);

#endif //SAKK_H
