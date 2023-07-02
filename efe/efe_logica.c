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
int verifica_casas(partida p);
bool verifica_perdeu(partida p);

void inicializa_desloca(bool cresc, int *i, int *li, int *lj, int *add);
bool desloca_linha(partida *p, int x, int i, int li, int lj, int add);
bool desloca_coluna(partida *p, int x, int i, int li, int lj, int add);
bool junta_linha(partida *p, int x, int i, int add);
bool junta_coluna(partida *p, int x, int i, int add);

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

void inicializa_desloca(bool cresc, int *i, int *li, int *lj, int *add){
    if(cresc){
        *i = 0;
        *li = 5;
        *lj = -1;
        *add = 1;
    }
    else {
        *i = 4;
        *li = -1;
        *lj = 5;
        *add = -1;
    }
}

bool desloca(partida *p, int x){
    int i, li, lj, add;
    bool moveu1, moveu2, moveu3, moveu4;
    inicializa_desloca(p->cresc, &i, &li, &lj, &add);
    if(p->coluna){
        moveu1 = junta_coluna(p, x, i, add);
        moveu2 = desloca_coluna(p, x, i, li, lj, add);
        moveu3 = junta_coluna(p, x, i, add);
        moveu4 = desloca_coluna(p, x, i, li, lj, add);
    }
    else{
        moveu1 = junta_linha(p, x, i, add);
        moveu2 = desloca_linha(p, x, i, li, lj, add);
        moveu3 = junta_linha(p, x, i, add);
        moveu4 = desloca_linha(p, x, i, li, lj, add);
    }
    return (moveu1 || moveu2 || moveu3 || moveu4);
}


bool junta_linha(partida *p, int x, int i, int add){
    int li = i+3*add;
    bool moveu = false;
    while(i != li){
        if(p->grid[x][i] == p->grid[x][i+1*add] && p->grid[x][i] == p->grid[x][i+2*add] && p->grid[x][i] != '-'){
            p->grid[x][i] = p->grid[x][i]+1;
            p->grid[x][i+1*add] = '-';
            p->grid[x][i+2*add] = '-';
            p->pontos += pow(3, (p->grid[x][i] - 'A'))*10;
            moveu = true;
	    if (p->grid[x][i] == 'F'){
		p->ganhou = true;
	    }
        }
        i+=add;
    }
    return moveu;
}

bool junta_coluna(partida *p, int x, int i, int add){
    int li = i+3*add;
    bool moveu = false;
    while(i != li){
        if(p->grid[i][x] == p->grid[i+1*add][x] && p->grid[i][x] == p->grid[i+2*add][x] && p->grid[i][x] != '-'){
            p->grid[i][x] = p->grid[i][x]+1;
            p->grid[i+1*add][x] = '-';
            p->grid[i+2*add][x] = '-';
            p->pontos += pow(3, (p->grid[i][x] - 'A'))*10;
            moveu = true;
	    if (p->grid[i][x] == 'F'){
		p->ganhou = true;
	    }
        }
        i+=add;
    }
    return moveu;
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
    p->ganhou = 0;
    p->perdeu = 0;
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

int verifica_casas(partida p){
    int i, j, casas = 0;
    for (i = 0; i < 5; i++){
        for (j = 0; j < 5; j++){
            if(p.grid[i][j] == '-'){
                casas++;
            }
        }
    }
    return casas;
}

bool verifica_perdeu(partida p){
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            if(p.grid[i][j] == p.grid[i][j+1] && p.grid[i][j] == p.grid[i][j+2]){
                return false;
            }
            if(p.grid[j][i] == p.grid[j+1][i] && p.grid[j][i] == p.grid[j+2][i]){
                return false;
            }
        }
    }
    return true;
}
