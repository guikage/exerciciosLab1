#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct{
    char grid[5][5];
    bool cresc, coluna;
    int pontos;
    char tecla;
} partida;

void inicializa(partida *p);
void desloca(partida *p, int x);
void imprime_matriz(partida p);
void adiciona_letra(partida *p);
void testa_tecla(partida *p);

int main(){
    srand(time(0));
    partida p;
    inicializa(&p);
    adiciona_letra(&p);
    imprime_matriz(p);
    for(;;){
        p.tecla = getchar();
        if(p.tecla == 'a' || p.tecla == 'd' || p.tecla == 'w' || p.tecla == 's'){
            testa_tecla(&p);
            for(int i = 0; i < 5; i++){
                desloca(&p, i);
            }
            adiciona_letra(&p);
            imprime_matriz(p);
        }
    }
}

void desloca_linha(partida *p, int x, int i, int li, int lj, int add);
void desloca_coluna(partida *p, int x, int i, int li, int lj, int add);
void junta_linha(partida *p, int x, int i, int add);
void junta_coluna(partida *p, int x, int i, int add);

void desloca_linha(partida *p, int x, int i, int li, int lj, int add){
    char aux;
    int i2 = i;
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
    int i2 = i;
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
    char aux;
    int i, j, li, lj, add;
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
            putchar(p.grid[i][j]);
        }
        putchar('\n');
    }
    printf("PONTUACAO: %d\n", p.pontos);
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
        p->coluna = false;
        if (p->tecla == 'a'){
            p->cresc = true;
        }
        else if (p->tecla == 'd'){
            p->cresc = false;
        }
    }
    else {
        p->coluna = true;
        if (p->tecla == 'w'){
            p->cresc = true;
        }
        else if (p->tecla == 's'){
            p->cresc = false;
        }
    }
}
