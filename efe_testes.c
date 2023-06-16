#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void desloca_linha(char linha[5], bool cresc);
void imprime_matriz(char grid[7][5]);
void junta_letras(char linha[5], bool cresc);

int main(){
    char tecla;
    bool cresc;
    char grid[7][5] = {
        {'-', 'A', '-', '-', '-'},
        {'-', '-', 'B', '-', 'A'},
        {'A', '-', 'A', 'A', '-'},
        {'C', 'C', 'B', 'C', '-'},
        {'B', 'C', 'C', 'C', 'C'},
        {'A', 'A', 'A', 'B', 'B'},
        {'B', 'B', 'A', 'A', 'A'}
    };
    imprime_matriz(grid);
    for(;;){
        tecla = getchar();
        if(tecla == 'a' || tecla == 'd'){
            if (tecla == 'a') cresc = true;
            else if (tecla == 'd') cresc = false;
            for(int i = 0; i < 7; i++){
                junta_letras(grid[i], cresc);
                desloca_linha(grid[i], cresc);
            }
            imprime_matriz(grid);
        }
    }
}

void desloca_linha(char linha[5], bool cresc){
    char aux;
    int i, j, li, lj, add;
    if(cresc){
        i = 1; li = 5; lj = -1; add = 1;
    } else {
        i = 3; li = -1; lj = 5; add = -1;
    }
    while(i != li){
        aux = linha[i];
        int j = i-add;
        while(linha[j] == '-' && j!=lj){
            linha[j+add] = linha[j];
            j -= add;
        }
        linha[j+add] = aux;
        i += add;
    }
}

void junta_letras(char linha[5], bool cresc){
    int i, li, add;
    if(cresc){
        i = 0; li = 3; add = 1;
    } else {
        i = 4; li = 1; add = -1;
    }
    while(i != li){
        if(linha[i] == linha[i+add] && linha[i] == linha[i+2*add] && linha[i] != '-'){
            linha[i] = linha[i]+1;
            linha[i+add] = '-';
            linha[i+2*add] = '-';
        }
        i += add;
    }
}

void imprime_matriz(char grid[7][5]){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 5; j++){
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
}
