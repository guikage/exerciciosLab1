#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "tela/tela.h"
#include "efe_logica.h"

void inicializa(partida *p);
bool desloca(partida *p, int x);
void adiciona_letra(partida *p);
void testa_tecla(partida *p);

bool desloca_linha(partida *p, int x, int i, int li, int lj, int add);
bool desloca_coluna(partida *p, int x, int i, int li, int lj, int add);
void junta_linha(partida *p, int x, int i, int add);
void junta_coluna(partida *p, int x, int i, int add);

bool desloca_linha(partida *p, int x, int i, int li, int lj, int add){
    char aux;
    bool moveu = false;
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
            moveu = true;
        }
        i += add;
    }
    return moveu;
}

bool desloca_coluna(partida *p, int x, int i, int li, int lj, int add){
    char aux;
    bool moveu = false;
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
            moveu = true;
        }
        i += add;
    }
    return moveu;
}

bool desloca(partida *p, int x){
    int i, li, lj, add;
    bool moveu1, moveu2;
    char debug[20];
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
        moveu1 = desloca_coluna(p, x, i, li, lj, add);
        junta_coluna(p, x, i, add);
        moveu2 = desloca_coluna(p, x, i, li, lj, add);
    }
    else{
        junta_linha(p, x, i, add);
        moveu1 = desloca_linha(p, x, i, li, lj, add);
        junta_linha(p, x, i, add);
        moveu2 = desloca_linha(p, x, i, li, lj, add);
    }
    sprintf(debug, "%d %d", moveu1, moveu2);
    tela_texto_dir(0, 540, 8, branco, debug);
    if(moveu1 || moveu2){
        return true;
    }
    return false;
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

void adiciona_letra(partida *p){
    int l, c, percentual;
    do{
        l = rand()%5;
        c = rand()%5;
    } while (p->grid[l][c] != '-');
    percentual = rand()%PERC;
    if(percentual < 1){
        p->grid[l][c] = 'B';
    }
    else{
        p->grid[l][c] = 'A';
    }
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

