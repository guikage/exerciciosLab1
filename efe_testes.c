#include <stdio.h>
#include <string.h>

void desloca_esq(char linha[5]);
void desloca_dir(char linha[5]);
void desloca_linha(char linha[5]);
void imprime_matriz(char grid[7][5]);
void junta_letras(char linha[5]);

int main(){
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
        getchar();
        for(int i = 0; i < 7; i++){
            desloca_linha(grid[i]);
        }
        imprime_matriz(grid);
    }
}

void desloca_linha(char linha[5]){
    char aux;
    for(int i = 0; i < 5; i++){
        aux = linha[i];
        int j = i-1;
        while(linha[j] == '-' && j>-1){
            linha[j+1] = linha[j];
            j--;
        }
        linha[j+1] = aux;
    }
}

void junta_letras(char linha[5]){
    desloca_linha(linha);
    for(int i = 0; i < 3; i++){
        if(linha[i] == linha[i+1] && linha[i] == linha[i+2] && linha[i] != '-'){
            linha[i] = linha[i]+1;
            linha[i+1] = '-';
            linha[i+2] = '-';
        }
    }
    desloca_linha(linha);
}

void imprime_matriz(char grid[7][5]){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 5; j++){
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
}
