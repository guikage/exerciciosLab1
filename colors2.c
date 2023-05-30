#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "tela.h"

void barra(int lin, int col, char cor, int valor){
    tela_lincol(lin, col);
    int r = 0, g = 0, b = 0;
    if(cor == 'r') r = 10;
    if(cor == 'g') g = 10;
    if(cor == 'b') b = 10;
    for(int i = 0; i < 26; i++){
        if (valor/10 == i) tela_cor_fundo(255, 255, 255); //branco
        else tela_cor_fundo(i*r, i*g, i*b); //cor escolhida
        putchar(' ');
    }
    tela_cor_normal();
    printf("%03d", valor);
}

void quadrado(int lin, int col, int r, int g, int b){
    tela_cor_fundo(r, g, b);
    for(int i = 0; i < 5; i++){
        tela_lincol(lin+i, col);
        for(int j = 0; j < 5; j++){
            putchar(' ');
        }
    }
    tela_cor_normal();
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

void muda_valor(int *cor, int tecla){
    switch (tecla){
        case c_left:
            if (*cor > 0) (*cor)--;
            break;
        case c_right:
            if (*cor < 255) (*cor)++;
            break;
        case 'a':
            if (*cor > 0) (*cor)--;
            break;
        case 'd':
            if (*cor < 255) (*cor)++;
            break;
        case 'D':
            if (*cor > 9) *cor-=10;
            else *cor = 0;
            break;
        case 'C':
            if (*cor < 246) *cor+=10;
            else *cor = 255;
            break;
    }
    return;
}

int main(){
    srand(time(0));
    tela_mostra_cursor(false);
    int r = 0, g = 0, b = 0;
    int randr, randg, randb;
    int pontos, posicaoplacar, tecla, cor = 0;
    double tempo, inicio;
    int placar[5] = {0, 0, 0, 0, 0};
    char nomes[5][4] = {"AAA", "AAA", "AAA", "AAA", "AAA"};
    char continuar;
    do{
        flushstdin();
        tela_cria();
        tela_limpa();

        randr = rand()%255;
        randg = rand()%255;
        randb = rand()%255;
        r = 0;
        g = 0;
        b = 0;
        quadrado(1, 1, randr, randg, randb);
        quadrado(1, 7, r, g, b);
        barra(1, 13, 'r', r);
        barra(3, 13, 'g', g);
        barra(5, 13, 'b', b);

        inicio = tela_relogio();
        do{
            tempo = tela_relogio() - inicio;
            tecla = tela_le_char();
            if (tecla == c_up || tecla == 'w'){
                if (cor > 0) cor--;
            } else if (tecla == c_down || tecla == 's'){
                if (cor < 2) cor++;
            } else {
                switch (cor){
                    case 0:
                        muda_valor(&r, tecla);
                        barra(1, 13, 'r', r);
                        break;
                    case 1:
                        muda_valor(&g, tecla);
                        barra(3, 13, 'g', g);
                        break;
                    case 2:
                        muda_valor(&b, tecla);
                        barra(5, 13, 'b', b);
                        break;
                }
            }

            quadrado(1, 7, r, g, b);
            pontos = pontuacao(randr, randg, randb, r, g, b);
            tela_lincol(7, 1);
            printf("PONTUACAO: %03d", pontos);
            tela_lincol(1, 1);
            printf("%d", cor);
        }while(tempo <= 10);
        tela_destroi();
        tela_limpa();

        pontos = pontuacao(randr, randg, randb, r, g, b);
        posicaoplacar = gerenciaplacar(placar, pontos, nomes);
        tela_lincol(1, 1);
        printf("PONTUACAO: %d ", pontos);
        if (posicaoplacar != 0) printf("(%do lugar)", posicaoplacar);

        //imprime cor gerada
        tela_lincol(3, 1);
        printf("COR GERADA:");
        quadrado(5, 1, randr, randg, randb);
        barra(5, 7, 'r', randr);
        barra(7, 7, 'g', randg);
        barra(9, 7, 'b', randb);
        
        //imprime cor do usuario
        tela_lincol(11, 1);
        printf("COR DO USUARIO:");
        quadrado(13, 1, r, g, b);
        barra(13, 7, 'r', r);
        barra(15, 7, 'g', g);
        barra(17, 7, 'b', b);

        //pega o nome se estiver no placar
        if(posicaoplacar != 0){
            tela_lincol(19, 1);
            printf("DIGITE SEU NOME: ___");
            tela_lincol(19, 18);
            fgets(nomes[posicaoplacar-1], 4, stdin);
            flushstdin();
        }

        tela_lincol(21, 1);
        printf("CONTINUAR? (s/n) ");
        scanf(" %c", &continuar);
        
        tela_cor_normal();
    }while(continuar == 's');
    tela_limpa();

    tela_lincol(1, 1);
    printf("MELHORES PONTUACOES:");
    tela_lincol(3, 1);
    for(int i = 0; i < 5; i++){
        if(placar[i] != 0) printf("%3s: %03d\n", nomes[i], placar[i]); //imprime todas as pontuacoes maiores do que 0 (pq 0 eh triste)
    }
    tela_lincol(10, 1);
    printf("PRESSIONE ENTER PARA SAIR");
    getchar();
    getchar();

    return 0;
}
