#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "tela/tela.h"

#include "efe_logica.h"
#include "efe_tela.h"
#include "efe_placar.h"

void imprime_matriz(partida p);
void imprime_pontuacao(partida p);
void imprime_fim_de_jogo(partida p);
void imprime_placar(placar pl);

void cria_string(char letra, char *str);
void desenha_quadrado(char letra, int x, int y);

void imprime_matriz(partida p){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            desenha_quadrado(p.grid[i][j], INI_T+i*TAM_R, INI_T+j*TAM_R);
        }
    }
}

void cria_string(char letra, char *str){
    str[0] = letra;
    str[1] = '\0';
}

void desenha_quadrado(char letra, int x, int y){
    int cor;
    char str[2];
    cria_string(letra, str);
    switch(letra){
        case 'A':
            cor = cor_A;
            break;
        case 'B':
            cor = cor_B;
            break;
        case 'C':
            cor = cor_C;
            break;
        case 'D':
            cor = cor_D;
            break;
        case 'E':
            cor = cor_E;
            break;
        case 'F':
            cor = cor_F;
            break;
        default:
            cor = preto;
            break;
    }
    tela_retangulo(x, y, x+TAM_R, y+TAM_R, 2, branco, cor);
    tela_texto(x+TAM_R/2, y+TAM_R/2, 32, branco, str);
}

void imprime_pontuacao(partida p){
    char str[20];
    sprintf(str, "%d", p.pontos);
    tela_texto_dir(384, 32, 32, branco, "PONTOS:");
    tela_texto_dir(384, 64, 32, branco, str);
}

void imprime_fim_de_jogo(partida p){
    imprime_matriz(p);
    imprime_pontuacao(p);
    tela_retangulo(180, 200, 460, 280, 4, branco, preto); 
    if(p.ganhou){
        tela_texto(320, 240, 32, branco, "VOCE GANHOU!");
    }
    else if(p.perdeu){
        tela_texto(320, 240, 32, branco, "VOCE PERDEU!");
    }
    tela_atualiza();
}

void imprime_placar(placar pl){
    char str[30];
    for (int i = 0; i < 5; i++){
        sprintf(str, "%s: %d", pl.nome[i], pl.pontos[i]);
        tela_texto(320, 160+(40*i), 32, branco, str);
    }
    tela_atualiza();
}
