#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void desloca_linha(char grid[5][5], int x, int i, int li, int lj, int add);
void desloca_coluna(char grid[5][5], int x, int i, int li, int lj, int add);
void desloca(char grid[5][5], int x, bool coluna, bool cresc);
void imprime_matriz(char grid[5][5]);
void junta_linha(char grid[5][5], int x, int i, int add);
void junta_coluna(char grid[5][5], int x, int i, int add);
void adiciona_letra(char grid[5][5]);

int main(){
    srand(time(0));
    char tecla;
    bool coluna, cresc;
    char grid[5][5] = {
        {'-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-'}
    };
    adiciona_letra(grid);
    imprime_matriz(grid);
    for(;;){
        tecla = getchar();
        if(tecla == 'a' || tecla == 'd' || tecla == 'w' || tecla == 's'){
            if(tecla == 'a' || tecla == 'd'){
                coluna = false;
                if (tecla == 'a'){
                    cresc = true;
                }
                else if (tecla == 'd'){
                    cresc = false;
                }
            }
            else {
                coluna = true;
                if (tecla == 'w'){
                    cresc = true;
                }
                else if (tecla == 's'){
                    cresc = false;
                }
            }
            for(int i = 0; i < 5; i++){
                desloca(grid, i, coluna, cresc);
            }
            adiciona_letra(grid);
            imprime_matriz(grid);
        }
    }
}

void desloca_linha(char grid[5][5], int x, int i, int li, int lj, int add){
    char aux;
    while(i != li){
        aux = grid[x][i];
        int j = i-add;
        while(grid[x][j] == '-' && j!=lj){
            grid[x][j+add] = grid[x][j];
            j -= add;
        }
        grid[x][j+add] = aux;
        i += add;
    }
}

void desloca_coluna(char grid[5][5], int x, int i, int li, int lj, int add){
    char aux;
    while(i != li){
        aux = grid[i][x];
        int j = i-add;
        while(grid[j][x] == '-' && j!=lj){
            grid[j+add][x] = grid[j][x];
            j -= add;
        }
        grid[j+add][x] = aux;
        i += add;
    }
}

void desloca(char grid[5][5], int x, bool coluna, bool cresc){
    char aux;
    int i, j, li, lj, add;
    if(cresc){
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
    if(coluna){
        junta_coluna(grid, x, i, add);
        desloca_coluna(grid, x, i, li, lj, add);
        junta_coluna(grid, x, i, add);
        desloca_coluna(grid, x, i, li, lj, add);
    }
    else{
        junta_linha(grid, x, i, add);
        desloca_linha(grid, x, i, li, lj, add);
        junta_linha(grid, x, i, add);
        desloca_linha(grid, x, i, li, lj, add);
    }
}


void junta_linha(char grid[5][5], int x, int i, int add){
    int li = i+3*add;
    while(i != li){
        if(grid[x][i] == grid[x][i+1*add] && grid[x][i] == grid[x][i+2*add] && grid[x][i] != '-'){
            grid[x][i] = grid[x][i]+1;
            grid[x][i+1*add] = '-';
            grid[x][i+2*add] = '-';
        }
        i+=add;
    }
}

void junta_coluna(char grid[5][5], int x, int i, int add){
    int li = i+3*add;
    while(i != li){
        if(grid[i][x] == grid[i+1*add][x] && grid[i][x] == grid[i+2*add][x] && grid[i][x] != '-'){
            grid[i][x] = grid[i][x]+1;
            grid[i+1*add][x] = '-';
            grid[i+2*add][x] = '-';
        }
        i+=add;
    }
}

void imprime_matriz(char grid[5][5]){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
}

void adiciona_letra(char grid[5][5]){
    int l, c;
    l = rand()%5;
    c = rand()%5;
    if(grid[l][c] != '-'){
        adiciona_letra(grid);
    }
    else{
        grid[l][c] = 'A';
    }
}
