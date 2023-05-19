#include <stdio.h>
#include <stdlib.h>

void preenche(char matriz[7][7]){
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            matriz[i][j] = '.';
            if (i == 0){
                if (j == 0) matriz[i][j] = 'O';
                else if (j == 6) matriz[i][j] = 'X';
            } else if (i == 6){
                if (j == 0) matriz[i][j] = 'X';
                else if (j == 6) matriz[i][j] = 'O';
            }
            else if (i == 1){
                if (j == 1) matriz[i][j] = 'X';
                else if (j == 5) matriz[i][j] = 'O';
            } else if (i == 5){
                if (j == 1) matriz[i][j] = 'O';
                else if (j == 5) matriz[i][j] = 'X';
            } else if ((i == 2 || i == 4) && j == 3) matriz[i][j] = 'O';
            else if (i == 3 && (j == 2 || j == 4)) matriz[i][j] = 'X';
        }
    }
}

void imprime(char matriz[7][7]){
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 7; j++){
            putchar(matriz[i][j]);
        }
        putchar('\n');
    }
}

void girac1(char matriz[7][7]){
    char c = matriz[0][0];
    for (int j = 0; j < 6; j++) matriz[0][j] = matriz[0][j+1];
    for (int i = 0; i < 6; i++) matriz[i][6] = matriz[i+1][6];
    for (int j = 6; j > 0; j--) matriz[6][j] = matriz[6][j-1];
    for (int i = 6; i > 0; i--) matriz[i][0] = matriz[i-1][0];
    matriz[1][0] = c;
};

void girac2(char matriz[7][7]){
    char c = matriz[1][1];
    for (int i = 1; i < 5; i++) matriz[i][1] = matriz[i+1][1];
    for (int j = 1; j < 5; j++) matriz[5][j] = matriz[5][j+1];
    for (int i = 5; i > 1; i--) matriz[i][5] = matriz[i-1][5];
    for (int j = 5; j > 1; j--) matriz[1][j] = matriz[1][j-1];
    matriz[1][2] = c;
};

void girac3(char matriz[7][7]){
    char c = matriz[2][2];
    for (int j = 2; j < 4; j++) matriz[2][j] = matriz[2][j+1];
    for (int i = 2; i < 4; i++) matriz[i][4] = matriz[i+1][4];
    for (int j = 4; j > 2; j--) matriz[4][j] = matriz[4][j-1];
    for (int i = 4; i > 2; i--) matriz[i][2] = matriz[i-1][2];
    matriz[3][2] = c;
};

int x(char matriz[7][7]){
    if((matriz[0][0] == matriz[1][1] && matriz[1][1] == matriz[2][2]) && matriz[0][0] != '.') return 1;
    return 0;
}

int cruz(char matriz[7][7]){
    if((matriz[0][3] == matriz[1][3] && matriz[1][3] == matriz[2][3]) && matriz[0][3] != '.') return 1;
    return 0;
}

int main(){
    char matriz[7][7];
    char c;
    printf("\033[H\033[2J\033[3J");
    preenche(matriz);
    imprime(matriz);
    for(;;){
        scanf(" %c", &c);
        switch(c){
            case '1':
                girac1(matriz);
                break;
            case '2':
                girac2(matriz);
                break;
            case '3':
                girac3(matriz);
                break;
            default:
                break;
        }
        printf("\033[H\033[2J\033[3J");
        imprime(matriz);
        if(cruz(matriz)) printf("CRUZ\n");
        if(x(matriz)) printf("MATRIZ EM X\n");
    }
    return 0;
}
