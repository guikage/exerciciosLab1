#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void ctexto(int r, int g, int b){
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void cfundo(int r, int g, int b){
    printf("\033[48;2;%d;%d;%dm", r, g, b);
}

void creset(void){
    printf("\033[m");
}

void poscursor(int lin, int col){
    printf("\033[%d;%dH", lin, col);
}

void limpatela(void){
    printf("\033[2J");
}

void limpatudo(void){
    printf("\033[2J\033[3J");
}

void barras(int lin, int col, int r, int g, int b){
    poscursor(lin, col);
    for(int i = 0; i < 26; i++){
        if (r/10 == i){
            cfundo(255, 255, 255); //branco
        } else {
            cfundo(i*10, 0, 0); //vermelho
        }
        putchar(' ');
    }
    
    poscursor(lin+2, col);
    for(int i = 0; i < 26; i++){
        if (g/10 == i){
            cfundo(255, 255, 255); //branco
        } else {
            cfundo(0, i*10, 0); //verde
        }
        putchar(' ');
    }
    
    poscursor(lin+4, col);
    for(int i = 0; i < 26; i++){
        if (b/10 == i){
            cfundo(255, 255, 255); //branco
        } else {
            cfundo(0, 0, i*10); //azul
        }
        putchar(' ');
    }

    creset();
}

void quadrado(int lin, int col, int r, int g, int b){
    cfundo(r, g, b);
    for(int i = 0; i < 5; i++){
        poscursor(lin+i, col);
        for(int j = 0; j < 5; j++){
            putchar(' ');
        }
    }

    creset();
}

void pegargb(int lin, int col, int *r, int *g, int *b){
    poscursor(lin, col);
    printf("R: ");
    poscursor(lin+1, col);
    printf("G: ");
    poscursor(lin+2, col);
    printf("B: ");
    poscursor(lin, col+3);
    scanf("%d", r);
    poscursor(lin+1, col+3);
    scanf("%d", g);
    poscursor(lin+2, col+3);
    scanf("%d", b);
    if (*r > 255) *r = 255;
    if (*g > 255) *g = 255;
    if (*b > 255) *b = 255;
    if (*r < 0) *r = 0;
    if (*g < 0) *g = 0;
    if (*b < 0) *b = 0;
}

int pontuacao(int randr, int randg, int randb, int r, int g, int b){
    int difr = r - randr;
    if (difr < 0) difr *= -1;
    int difg = g - randg;
    if (difg < 0) difg *= -1;
    int difb = b - randb;
    if (difb < 0) difb *= -1;

    int soma = difr + difg + difb;
    int pontos = soma / 7.65;
    return (100 - pontos);
}

int main(){
    srand(time(0));
    int r = 0, g = 0, b = 0, linha = 1;
    int tentativas = 3, pontos;
    int randr, randg, randb;
    limpatudo();

    randr = rand()%255;
    randg = rand()%255;
    randb = rand()%255;
    quadrado(linha, 1, randr, randg, randb);
    linha += 6;

    for(int i = 0; i < tentativas; i++){
        pegargb(linha, 1, &r, &g, &b);
        linha += 4;
        quadrado(linha, 1, randr, randg, randb);
        quadrado(linha, 7, r, g, b);
        barras(linha, 13, r, g, b);
        linha += 6;
    }
    limpatela();

    pontos = pontuacao(randr, randg, randb, r, g, b);
    poscursor(1, 1);
    printf("PONTUACAO: %d\n\n", pontos);
    
    printf("COR ALEATORIA:");
    quadrado(5, 1, randr, randg, randb);
    barras(5, 7, randr, randg, randb);
    poscursor(5, 33);
    printf("%d", randr);
    poscursor(7, 33);
    printf("%d", randg);
    poscursor(9, 33);
    printf("%d", randb);
    poscursor(11, 1);
    
    printf("COR DO USUARIO:");
    quadrado(13, 1, r, g, b);
    barras(13, 7, r, g, b);
    poscursor(13, 33);
    printf("%d", r);
    poscursor(15, 33);
    printf("%d", g);
    poscursor(17, 33);
    printf("%d", b);
    
    creset();
    getchar();
    getchar();
    limpatudo();
    return 0;
}
