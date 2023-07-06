#ifndef _efe_tela_h_
#define _efe_tela_h_

#include "efe_logica.h"
#include "efe_placar.h"

#define TAM_R 64
#define INI_T 32
#define DIST_R 0

#define cor_A tela_cria_cor(.40, .10, .60);
#define cor_B tela_cria_cor(.24, .25, .58);
#define cor_C tela_cria_cor(.16, .40, .56);
#define cor_D tela_cria_cor(.08, .60, .54);
#define cor_E tela_cria_cor(.00, .75, .52);
#define cor_F tela_cria_cor(.00, .85, .50);

void imprime_matriz(partida p);
void imprime_pontuacao(partida p);
void imprime_fim_de_jogo(partida p);
void imprime_pause(partida p);
void imprime_placar(placar pl);

void cria_string(char letra, char *str);
void desenha_quadrado(char letra, int x, int y);

#endif
