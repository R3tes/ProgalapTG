#ifndef SAKK_H
#define SAKK_H

#define PALYAMERET 8

typedef struct {
    char tartalom[3];
    bool foglalt;
} mezo;

typedef struct {

} babu;

void tabla_kiir(mezo **tabla);

void tabla_inicializal(mezo **tabla);

mezo **tabla_letrehoz();

#endif //SAKK_H
