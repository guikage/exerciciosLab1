#ifndef _efe_tela_h_
#define _efe_tela_h_

#include "efe_logica.h"
#include "efe_placar.h"

#define TAM_R 64
#define INI_T 32
#define DIST_R 0

#define cor_A tela_cria_cor(0.40, 0.00, 0.61);
#define cor_B tela_cria_cor(0.32, 0.15, 0.60);
#define cor_C tela_cria_cor(0.24, 0.35, 0.59);
#define cor_D tela_cria_cor(0.16, 0.65, 0.58);
#define cor_E tela_cria_cor(0.08, 0.85, 0.57);
#define cor_F tela_cria_cor(0.00, 1.00, 0.56);

void imprime_matriz(partida p);
void imprime_pontuacao(partida p);
void imprime_fim_de_jogo(partida p);
void imprime_placar(placar pl);

void cria_string(char letra, char *str);
void desenha_quadrado(char letra, int x, int y);

#endif
