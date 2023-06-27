#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "tela/tela.h"

#define TAM_R 64
#define INI_T 32
#define DIST_R 0

#define cor_A tela_cria_cor(0.40, 0.00, 0.61);
#define cor_B tela_cria_cor(0.32, 0.20, 0.60);
#define cor_C tela_cria_cor(0.24, 0.40, 0.59);
#define cor_D tela_cria_cor(0.16, 0.60, 0.58);
#define cor_E tela_cria_cor(0.08, 0.80, 0.57);
#define cor_F tela_cria_cor(0.00, 1.00, 0.56);

typedef struct{
    char grid[5][5];
    bool cresc, coluna;
    int pontos;
    int tecla;
} partida;

void inicializa(partida *p);
void desloca(partida *p, int x);
void imprime_matriz(partida p);
void adiciona_letra(partida *p);
void testa_tecla(partida *p);

int main(){
    srand(time(0));
    tela_inicio(640, 480, "jogo");
    partida p;
    inicializa(&p);
    adiciona_letra(&p);
    imprime_matriz(p);
    tela_atualiza();
    for(;;){
        p.tecla = tela_tecla();
        if(p.tecla != c_none){
            testa_tecla(&p);
            for(int i = 0; i < 5; i++){
                desloca(&p, i);
            }
            adiciona_letra(&p);
            imprime_matriz(p);
            tela_atualiza();
        }
    }
    tela_fim();
}

void desloca_linha(partida *p, int x, int i, int li, int lj, int add);
void desloca_coluna(partida *p, int x, int i, int li, int lj, int add);
void junta_linha(partida *p, int x, int i, int add);
void junta_coluna(partida *p, int x, int i, int add);
void cria_string(char letra, char *str);
void desenha_quadrado(char letra, int x, int y);

void desloca_linha(partida *p, int x, int i, int li, int lj, int add){
    char aux;
    while(i != li){
        aux = p->grid[x][i];
        int j = i-add;
        while(p->grid[x][j] == '-' && j!=lj){
            p->grid[x][j+add] = p->grid[x][j];
            j -= add;
        }
        p->grid[x][j+add] = aux;
        if(j+add != i && aux != '-'){
            p->pontos++;
        }
        i += add;
    }
}

void desloca_coluna(partida *p, int x, int i, int li, int lj, int add){
    char aux;
    while(i != li){
        aux = p->grid[i][x];
        int j = i-add;
        while(p->grid[j][x] == '-' && j!=lj){
            p->grid[j+add][x] = p->grid[j][x];
            j -= add;
        }
        p->grid[j+add][x] = aux;
        if(j+add != i && aux != '-'){
            p->pontos++;
        }
        i += add;
    }
}

void desloca(partida *p, int x){
    int i, li, lj, add;
    if(p->cresc){
        i = 0;
        li = 5;
        lj = -1;
        add = 1;
    }
    else {
        i = 4;
        li = -1;
        lj = 5;
        add = -1;
    }
    if(p->coluna){
        junta_coluna(p, x, i, add);
        desloca_coluna(p, x, i, li, lj, add);
        junta_coluna(p, x, i, add);
        desloca_coluna(p, x, i, li, lj, add);
    }
    else{
        junta_linha(p, x, i, add);
        desloca_linha(p, x, i, li, lj, add);
        junta_linha(p, x, i, add);
        desloca_linha(p, x, i, li, lj, add);
    }
}


void junta_linha(partida *p, int x, int i, int add){
    int li = i+3*add;
    while(i != li){
        if(p->grid[x][i] == p->grid[x][i+1*add] && p->grid[x][i] == p->grid[x][i+2*add] && p->grid[x][i] != '-'){
            p->grid[x][i] = p->grid[x][i]+1;
            p->grid[x][i+1*add] = '-';
            p->grid[x][i+2*add] = '-';
            p->pontos += pow(3, (p->grid[x][i] - 'A'))*10;
        }
        i+=add;
    }
}

void junta_coluna(partida *p, int x, int i, int add){
    int li = i+3*add;
    while(i != li){
        if(p->grid[i][x] == p->grid[i+1*add][x] && p->grid[i][x] == p->grid[i+2*add][x] && p->grid[i][x] != '-'){
            p->grid[i][x] = p->grid[i][x]+1;
            p->grid[i+1*add][x] = '-';
            p->grid[i+2*add][x] = '-';
            p->pontos += pow(3, (p->grid[i][x] - 'A'))*10;
        }
        i+=add;
    }
}

void imprime_matriz(partida p){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            desenha_quadrado(p.grid[i][j], INI_T+i*TAM_R, INI_T+j*TAM_R);
        }
    }
}

void adiciona_letra(partida *p){
    int l, c;
    do{
        l = rand()%5;
        c = rand()%5;
    } while (p->grid[l][c] != '-');
    p->grid[l][c] = 'A';
}

void inicializa(partida *p){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            p->grid[i][j] = '-';
        }
    }
    p->pontos = 0;
}

void testa_tecla(partida *p){
    if(p->tecla == 'a' || p->tecla == 'd'){
        p->coluna = true;
        if (p->tecla == 'a'){
            p->cresc = true;
        }
        else if (p->tecla == 'd'){
            p->cresc = false;
        }
    }
    else {
        p->coluna = false;
        if (p->tecla == 'w'){
            p->cresc = true;
        }
        else if (p->tecla == 's'){
            p->cresc = false;
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
