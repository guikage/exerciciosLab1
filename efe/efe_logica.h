#ifndef _efe_logica_h_
#define _efe_logica_h_

#include <stdbool.h>

#define PERC 4

typedef struct{
    char grid[5][5];
    bool cresc, coluna;
    int pontos;
    int tecla;
    bool moveu, mover;
    bool ganhou, perdeu;
} partida;

void inicializa(partida *p);
bool desloca(partida *p, int x);
void adiciona_letra(partida *p);
void testa_tecla(partida *p);

#endif
