#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "tela.h"

#define T_MAX 30

typedef struct{
    int r;
    int g;
    int b;
} cor;

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

void quadrado(int lin, int col, cor cor){
    tela_cor_fundo(cor.r, cor.g, cor.b);
    for(int i = 0; i < 5; i++){
        tela_lincol(lin+i, col);
        for(int j = 0; j < 5; j++){
            putchar(' ');
        }
    }
    tela_cor_normal();
}

void indica_cor(int lin, int col, int cor){
    for(int i = 0; i < 3; i++){
	tela_lincol(lin+i*2, col);
	if (i == cor) tela_cor_fundo(0, 255, 0);
	else tela_cor_fundo(127, 127, 127);
	putchar(' ');
    }
    tela_cor_normal();
}

int pontuacao(cor c_rand, cor c_user, double tempo){
    int difr = c_user.r - c_rand.r;
    if (difr < 0) difr *= -1;
    int difg = c_user.g - c_rand.g;
    if (difg < 0) difg *= -1;
    int difb = c_user.b - c_rand.b;
    if (difb < 0) difb *= -1;

    int difmaxr = c_rand.r, difmaxg = c_rand.g, difmaxb = c_rand.b;
    if (c_rand.r < 128) difmaxr = 255 - c_rand.r;
    if (c_rand.g < 128) difmaxg = 255 - c_rand.g;
    if (c_rand.b < 128) difmaxb = 255 - c_rand.b;

    float finalr = (float)difr / difmaxr * 100;
    float finalg = (float)difg / difmaxg * 100;
    float finalb = (float)difb / difmaxb * 100;

    float pontos = 100 - (finalr + finalg + finalb)/3 + 2*(T_MAX - tempo);
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
    }
    return;
}

void le_arquivo(int vetor[5], char nomes[5][4]){
    FILE *arq = fopen("./placar.txt", "r");
    if (arq == NULL){
	    arq = fopen("./placar.txt", "w");
	    fprintf(arq, "AAA 0\nAAA 0\nAAA 0\nAAA 0\nAAA 0");
	    fclose(arq);
	    arq = fopen("./placar.txt", "r");
    }
    for (int i = 0; i < 5; i++){
        fscanf(arq, "%s %d", nomes[i], &vetor[i]);
    }
    fclose(arq);
}

void escreve_arquivo(int vetor[5], char nomes[5][4]){
    FILE *arq = fopen("./placar.txt", "w");
    for(int i = 0; i < 5; i++){
	fprintf(arq, "%s %d\n", nomes[i], vetor[i]);
    }
    fclose(arq);
}

int main(){
    srand(time(0));
    tela_mostra_cursor(false);
    cor c_user;
    cor c_rand;
    int pontos, posicaoplacar, tecla, cor;
    double tempo, inicio;
    int placar[5] = {0, 0, 0, 0, 0};
    char nomes[5][4] = {"AAA", "AAA", "AAA", "AAA", "AAA"};
    char continuar;
    le_arquivo(placar, nomes);
    do{
        flushstdin();
        tela_cria();
        tela_limpa();

        c_rand.r = rand()%255;
        c_rand.g = rand()%255;
        c_rand.b = rand()%255;
	c_user.r = 0;
	c_user.g = 0;
	c_user.b = 0;
	cor = 0;
        quadrado(1, 1, c_rand);
        quadrado(1, 7, c_user);
        barra(1, 14, 'r', c_user.r);
        barra(3, 14, 'g', c_user.g);
        barra(5, 14, 'b', c_user.b);
	indica_cor(1, 13, cor);

        inicio = tela_relogio();
        do{
            tempo = tela_relogio() - inicio;
            tecla = tela_le_char();
	    if (tecla == c_enter) break;
	    else if (tecla == c_up || tecla == 'w'){
                if (cor > 0) cor--;
		else cor = 2;
            } else if (tecla == c_down || tecla == 's'){
                if (cor < 2) cor++;
		else cor = 0;
            } else {
                switch (cor){
                    case 0:
                        muda_valor(&(c_user.r), tecla);
                        barra(1, 14, 'r', c_user.r);
                        break;
                    case 1:
                        muda_valor(&(c_user.g), tecla);
                        barra(3, 14, 'g', c_user.g);
                        break;
                    case 2:
                        muda_valor(&(c_user.b), tecla);
                        barra(5, 14, 'b', c_user.b);
                        break;
                }
            }

            quadrado(1, 7, c_user);
            pontos = pontuacao(c_rand, c_user, T_MAX);
            tela_lincol(7, 1);
            printf("PONTUACAO: %03d", pontos);
	    tela_lincol(9, 1);
	    printf("TEMPO: %.1lf", tempo);
	    indica_cor(1, 13, cor);
        }while(tempo <= T_MAX);
        tela_destroi();
        tela_limpa();

        pontos = pontuacao(c_rand, c_user, tempo);
        posicaoplacar = gerenciaplacar(placar, pontos, nomes);
        tela_lincol(1, 1);
        printf("PONTUACAO: %d ", pontos);
        if (posicaoplacar != 0) printf("(%do lugar)", posicaoplacar);

        //imprime cor gerada
        tela_lincol(3, 1);
        printf("COR GERADA:");
        quadrado(5, 1, c_rand);
        barra(5, 7, 'r', c_rand.r);
        barra(7, 7, 'g', c_rand.g);
        barra(9, 7, 'b', c_rand.b);
        
        //imprime cor do usuario
        tela_lincol(11, 1);
        printf("COR DO USUARIO:");
        quadrado(13, 1, c_user);
        barra(13, 7, 'r', c_user.r);
        barra(15, 7, 'g', c_user.g);
        barra(17, 7, 'b', c_user.b);

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

    escreve_arquivo(placar, nomes);

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
