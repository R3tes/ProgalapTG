#ifndef SAKK_H
#define SAKK_H

#define PALYAMERET 8
#define SWITCH_TO_COLOR_RED printf("\033[0;31m");
#define SWITCH_TO_DEFAULT_COLOR printf("\033[0m");
#define SWITCH_TO_COLOR_BLUE printf("\033[0;34m");

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

void jatekos_beker();

void tabla_kiir(mezo **tabla);

void tabla_inicializal(mezo **tabla);

mezo **tabla_letrehoz();

void tabla_feltolt(mezo **tabla);

#endif //SAKK_H
