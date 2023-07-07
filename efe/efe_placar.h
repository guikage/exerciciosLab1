#ifndef _efe_placar_h_
#define _efe_placar_h_

#include <stdbool.h>
#include "efe_logica.h"

typedef struct{
    int pontos[5];
    char nome[5][16];
    bool ganhou[5];
} placar;

void le_arquivo(placar *p);
void grava_arquivo(placar p);
int gerencia_placar(int pontos, placar *p);
void gera_posicao(partida part, placar *p);

#endif

