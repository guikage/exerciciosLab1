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

void barra(int lin, int col, char cor, int valor){
    poscursor(lin, col);
    int r = 0, g = 0, b = 0;
    if(cor == 'r') r = 10;
    if(cor == 'g') g = 10;
    if(cor == 'b') b = 10;
    for(int i = 0; i < 26; i++){
        if (valor/10 == i) cfundo(255, 255, 255); //branco
        else cfundo(i*r, i*g, i*b); //cor escolhida
        putchar(' ');
    }
    creset();
    printf("%d", valor);
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

void pegacor(int lin, int col, int *cor){
    poscursor(lin, col);
    scanf("%d", cor);
    if (*cor > 255) *cor = 255;
    if (*cor < 0) *cor = 0;
}

int pontuacao(int randr, int randg, int randb, int r, int g, int b){
    int difr = r - randr;
    if (difr < 0) difr *= -1;
    int difg = g - randg;
    if (difg < 0) difg *= -1;
    int difb = b - randb;
    if (difb < 0) difb *= -1;

    int difmaxr = randr, difmaxg = randg, difmaxb = randb;
    if (randr < 128) difmaxr = 255 - randr;
    if (randg < 128) difmaxg = 255 - randg;
    if (randb < 128) difmaxb = 255 - randb;

    float finalr = (float)difr / difmaxr * 100;
    float finalg = (float)difg / difmaxg * 100;
    float finalb = (float)difb / difmaxb * 100;

    float pontos = 100 - (finalr + finalg + finalb)/3;
    return (int)pontos;
}

int gerenciaplacar(int placar[5], int pontos, char nomes[][4]){
    for (int i = 0; i < 5; i++){
        if(pontos > placar[i]){
            for (int j = 4; j > i; j--){
                placar[j] = placar[j-1];
                strcpy(nomes[j], nomes[j-1]);
            }
            placar[i] = pontos;
            return (i+1);
        }
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
            poscursor(7, 1);
            printf("R:\nG:\nB:");
            pegacor(7, 3, &r);
            pegacor(8, 3, &g);
            pegacor(9, 3, &b);

            limpatela();
            quadrado(1, 1, randr, randg, randb);
            quadrado(1, 7, r, g, b);
            barra(1, 13, 'r', r);
            barra(3, 13, 'g', g);
            barra(5, 13, 'b', b);
        }
        limpatela();

        pontos = pontuacao(randr, randg, randb, r, g, b);
        posicaoplacar = gerenciaplacar(placar, pontos, nomes);
        poscursor(1, 1);
        printf("PONTUACAO: %d ", pontos);
        if (posicaoplacar != 0) printf("(%do lugar)", posicaoplacar);

        //imprime cor gerada
        poscursor(3, 1);
        printf("COR GERADA:");
        quadrado(5, 1, randr, randg, randb);
        barra(5, 7, 'r', randr);
        barra(7, 7, 'g', randg);
        barra(9, 7, 'b', randb);
        
        //imprime cor do usuario
        poscursor(11, 1);
        printf("COR DO USUARIO:");
        quadrado(13, 1, r, g, b);
        barra(13, 7, 'r', r);
        barra(15, 7, 'g', g);
        barra(17, 7, 'b', b);

        //pega o nome se estiver no placar
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
        if(placar[i] != 0) printf("%3s: %03d\n", nomes[i], placar[i]); //imprime todas as pontuacoes maiores do que 0 (pq 0 eh triste)
    }
    poscursor(10, 1);
    printf("PRESSIONE ENTER PARA SAIR");
    getchar();
    getchar();

    return 0;
}
