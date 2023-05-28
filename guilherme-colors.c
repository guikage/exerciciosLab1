#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

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
    printf("\033[H\033[2J\033[3J");
}

void barras(int lin, int col, int r, int g, int b){
    poscursor(lin, col);
/// 3x quase o mesmo código, faz uma função!
    for(int i = 0; i < 26; i++){
        if (r/10 == i) cfundo(255, 255, 255); //branco
        else cfundo(i*10, 0, 0); //vermelho
        putchar(' ');
    }
    poscursor(lin+2, col);
    for(int i = 0; i < 26; i++){
        if (g/10 == i) cfundo(255, 255, 255); //branco
        else cfundo(0, i*10, 0); //verde
        putchar(' ');
    }
    poscursor(lin+4, col);
    for(int i = 0; i < 26; i++){
        if (b/10 == i) cfundo(255, 255, 255); //branco
        else cfundo(0, 0, i*10); //azul
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
/// Que tal assim:
///   pega1('R', lin+0, col, r);
///   pega1('G', lin+1, col, g);
///   pega1('B', lin+2, col, b);
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
/// 7.65?
/// era para ser relativo à pior pontuação possível para os rand
    int pontos = soma / 7.65;
    return (100 - pontos);
}

int gerenciaplacar(int placar[5], int pontos, char nomes[][4]){
    char cnome[4];
/// o placar já tá ordenado, não precisa uma função de ordenação completa
    if (pontos > placar[4]) placar[4] = pontos;
    for (int i = 0; i < 5; i++){
        for (int j = i; j < 5; j++){
            if (placar[i] < placar[j]){
                int c = placar[i];
                placar[i] = placar[j];
                placar[j] = c;
                strcpy(cnome, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], cnome);
            }
        }
    }
    for (int i = 0; i < 5; i++){
        if(pontos >= placar[i]) return (i+1);
    }
    return 0;
}

void flushstdin(){ 
    int ch;
    while((ch = fgetc(stdin)) != EOF && ch != '\n'){} 
}

int main(){
    srand(time(0));
    int r = 0, g = 0, b = 0;
    int randr, randg, randb;
    int pontos, posicaoplacar;
    int placar[5] = {0, 0, 0, 0, 0};
    char nomes[5][4] = {"AAA", "AAA", "AAA", "AAA", "AAA"};
    char continuar;
    do{
        limpatudo();

        randr = rand()%255;
        randg = rand()%255;
        randb = rand()%255;
        quadrado(1, 1, randr, randg, randb);

        for(int i = 0; i < 5; i++){
            pegargb(7, 1, &r, &g, &b);
            limpatela();
            quadrado(1, 1, randr, randg, randb);
            quadrado(1, 7, r, g, b);
            barras(1, 13, r, g, b);
        }
        limpatela();

/// ali em cima tá bem mais limpo..
        pontos = pontuacao(randr, randg, randb, r, g, b);
        poscursor(1, 1);
        posicaoplacar = gerenciaplacar(placar, pontos, nomes);
        printf("PONTUACAO: %d ", pontos);
        if (posicaoplacar != 0) printf("(%do lugar)", posicaoplacar);

        poscursor(3, 1);
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

        if(posicaoplacar != 0){
            poscursor(19, 1);
            printf("DIGITE SEU NOME: ___");
            getchar();
            poscursor(19, 18);
            fgets(nomes[posicaoplacar-1], 4, stdin);
            flushstdin();
        }

        poscursor(21, 1);
        printf("CONTINUAR? (s/n) ");
        scanf(" %c", &continuar);
        
        creset();
    }while(continuar != 'n');
    limpatela();
    poscursor(1, 1);
    printf("MELHORES PONTUACOES:");
    poscursor(3, 1);
    for(int i = 0; i < 5; i++){
        if(placar[i] != 0) printf("%3s: %03d\n", nomes[i], placar[i]);
    }
    poscursor(10, 1);
    printf("PRESSIONE ENTER PARA SAIR");
    getchar();
    getchar();

    return 0;
}
