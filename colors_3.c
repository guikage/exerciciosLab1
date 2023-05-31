#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "tela.h"

#define TMAX 20.0

typedef struct{
    int r;
    int g;
    int b;
} cor;

typedef struct{
    bool fim;
    cor cuser;
    cor crand;
    int cor;
    float pontos;
    double inicio;
    double tempo;
} estado;

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

void muda_valor(int *valor, int tecla){
    switch (tecla){
        case c_left:
            if (*valor > 0){
                (*valor)--;
            }
            break;
        case c_right:
            if (*valor < 255){
                (*valor)++;
            };
            break;
        default:
            break;
    }
    return;
}

void muda_cor(int *cor, int tecla){
    switch (tecla){
        case c_up:
            if (*cor > 0){
                (*cor)--;
            }
            else {
                *cor = 2;
            }
            break;
        case c_down:
            if (*cor < 2){
                (*cor)++;
            }
            else {
                *cor = 0;
            }
            break;
        default:
            break;
    }
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

float pontuacao_cor(int cor_rand, int cor_user){
    int dif_cor, dif_max;
    float pontos;
    dif_cor = abs(cor_user - cor_rand);
    if(cor_rand < 128){
        dif_max = 255 - cor_rand;
    }
    else {
        dif_max = cor_rand;
    }
    pontos = ((float)dif_cor / dif_max) * 100;
    return pontos;
}

float pontuacao(cor crand, cor cuser, double tempo){
    float pontos_r, pontos_g, pontos_b, pontos;
    pontos_r = pontuacao_cor(crand.r, cuser.r);
    pontos_g = pontuacao_cor(crand.g, cuser.g);
    pontos_b = pontuacao_cor(crand.b, cuser.b);
    pontos = 100 - (pontos_r + pontos_g + pontos_b)/3;
    pontos += pontos / 0.05 * (TMAX - tempo);
    return pontos;
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

void inicializa(estado *e){
    e->inicio = tela_relogio();
    e->crand.r = rand()%256;
    e->crand.g = rand()%256;
    e->crand.b = rand()%256;
    e->cuser.r = 0;
    e->cuser.g = 0;
    e->cuser.b = 0;
    e->cor = 0;
    e->fim = false;
}

void le_tecla(estado *e){
    int tecla;
    tecla = tela_le_char();
    if(tecla == c_up || tecla == c_down){
        muda_cor(&(e->cor), tecla);
    }
    else{
        switch (e->cor){
            case 0:
                muda_valor(&(e->cuser.r), tecla);
                break;
            case 1:
                muda_valor(&(e->cuser.g), tecla);
                break;
            case 2:
                muda_valor(&(e->cuser.b), tecla);
                break;
        }
    }
}

void altera_estado(estado *e){
    le_tecla(e);
    e->pontos = pontuacao(e->crand, e->cuser, TMAX);
    e->tempo = tela_relogio() - e->inicio;
    if (e->tempo >= TMAX){
        e->fim = true;
    }
}

void mostra_tela(estado e){
    quadrado(1, 1, e.crand);
    quadrado(7, 1, e.cuser);
    indica_cor(7, 7, e.cor);
    barra(7, 8, 'r', e.cuser.r);
    barra(9, 8, 'g', e.cuser.g);
    barra(11, 8, 'b', e.cuser.b);
    tela_lincol(1, 7);
    printf("PONTUAÇÃO:\t%03.1f", e.pontos);
    tela_lincol(2, 7);
    printf("TEMPO:\t%03.1lf", e.tempo);
}

void termina(estado *e){
    e->pontos = pontuacao(e->crand, e->cuser, e->tempo);
}

void partida(estado *e){
    inicializa(e);
    while(!e->fim){
        altera_estado(e);
        mostra_tela(*e);
    }
    termina(e);
}

int main(){
    srand(time(0));
    tela_cria();
    tela_mostra_cursor(false);
    estado e;
    partida(&e);
    tela_destroi();
    return 0;
}
