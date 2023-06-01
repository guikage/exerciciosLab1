#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "tela.h"

#define TMAX 30.0

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

const cor RED = {1, 0, 0};
const cor GREEN = {0, 1, 0};
const cor BLUE = {0, 0, 1};

//funcao auxiliar:
int espera_char(){
    int c;
    do {
	c = tela_le_char();
    } while(c == c_none);
    return c;
}

//gerenciam pontuacao e placar:

void le_arquivo(float vetor[5], char nomes[5][4]){
    FILE *arq = fopen("./placar.txt", "r");
    if (arq == NULL){
	    arq = fopen("./placar.txt", "w");
	    fprintf(arq, "AAA -1\nAAA -1\nAAA -1\nAAA -1\nAAA -1");
	    fclose(arq);
	    arq = fopen("./placar.txt", "r");
    }
    for (int i = 0; i < 5; i++){
        fscanf(arq, "%s %f", nomes[i], &vetor[i]);
    }
    fclose(arq);
}

void grava_arquivo(float vetor[5], char nomes[5][4]){
    FILE *arq = fopen("./placar.txt", "w");
    for(int i = 0; i < 5; i++){
	fprintf(arq, "%s %.1f\n", nomes[i], vetor[i]);
    }
    fclose(arq);
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
    pontos += pontos * 0.05 * (TMAX - tempo);
    return pontos;
}

int gerencia_placar(float pontos, float placar[5], char nomes[5][4]){
    for (int i = 0; i < 5; i++){
        if(pontos > placar[i]){
            for (int j = 4; j > i; j--){
                placar[j] = placar[j-1];
                strcpy(nomes[j], nomes[j-1]);
            }
            placar[i] = pontos;
            grava_arquivo(placar, nomes);
            return (i+1);
        }
    }
    return 0;
}

void aperta_back(int lin, int col, int *i){
    if ((*i) > 0){
	(*i)--;
    }
    tela_lincol(lin, col+(*i));
    for(int j = (*i); j < 3; j++){
	putchar('_');
    }
    tela_lincol(lin, col+(*i));
}

void pega_nome(char nomes[5][4], int pos, int lin, int col){
    int c, i = 0;
    bool enter = false;
    while(i < 4){
        if(!enter){
            c = tela_le_char();
            if (c == c_enter){
                enter = true;
            }
            else if (c == c_back){
		aperta_back(lin, col, &i);
            }
            else if (c > 32 && c < 127){
                nomes[pos][i] = c;
                printf("%c", c);
                i++;
            }
        }
        else{
            nomes[pos][i] = '\0';
            i++;
        }
    }
    nomes[pos][3] = '\0';
}

void gera_posicao(estado partida, float placar[5], char nomes[5][4]){
    int posicao = gerencia_placar(partida.pontos, placar, nomes);
    if (posicao != 0){
        tela_lincol(20, 1);
        printf("VOCE FICOU EM %do LUGAR\nDIGITE SEU NOME: ___", posicao);
        tela_lincol(21, 18);
        pega_nome(nomes, posicao-1, 21, 18);
    }
}

//exibem partida:

void barra(int lin, int col, cor cor, int valor){
    tela_lincol(lin, col);
    for(int i = 0; i < 26; i++){
        if (valor/10 == i) {
            tela_cor_fundo(255, 255, 255); //branco
        }
        else {
            tela_cor_fundo(i*cor.r*10, i*cor.g*10, i*cor.b*10); //cor escolhida
        }
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

void mostra_tela(estado e){
    quadrado(1, 1, e.crand);
    quadrado(7, 1, e.cuser);
    indica_cor(7, 7, e.cor);
    barra(7, 8, RED, e.cuser.r);
    barra(9, 8, GREEN, e.cuser.g);
    barra(11, 8, BLUE, e.cuser.b);
    tela_lincol(1, 7);
    printf("PONTUAÇÃO:\t%03.1f", e.pontos);
    tela_lincol(2, 7);
    printf("TEMPO:\t\t%03.1lf", e.tempo);
}

void imprime_cores_finais(int lin, int col, cor cor, bool user){
    tela_lincol(lin, col);
    if (user) {
        printf("COR DO USUARIO:");
    }
    else {
        printf("COR GERADA:");
    }
    quadrado(lin+2, col, cor);
    barra(lin+2, col+6, RED, cor.r);
    barra(lin+4, col+6, GREEN, cor.g);
    barra(lin+6, col+6, BLUE, cor.b);
}

void mostra_informacoes_finais(estado e){
    tela_limpa();
    imprime_cores_finais(1, 1, e.crand, false);
    imprime_cores_finais(9, 1, e.cuser, true);
    tela_lincol(17,1);
    printf("PONTUACAO:\t%03.1f\nTEMPO:\t\t%03.1lf", e.pontos, e.tempo);
}

void mostra_placar(float placar[5], char nomes[5][4]){
    tela_lincol(0, 0);
    printf("MELHORES PONTUACOES: \n\n");
    for (int i = 0; i < 5; i++){
        if(placar[i] >= 0){
            printf("%3s: %03.1f\n", nomes[i], placar[i]);
        }
    }
    printf("\n\nPRESSIONE QUALQUER TECLA PARA SAIR");
    espera_char();
}

//alteram partida:

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
    if (tecla == c_enter){
        e->fim = true;
    }
    else if(tecla == c_up || tecla == c_down){
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
    mostra_informacoes_finais(*e);
}

int main(){
    srand(time(0));
    tela_cria();
    tela_mostra_cursor(false);
    estado e;
    float placar[5];
    char nomes[5][4];
    int continua = -1000;
    le_arquivo(placar, nomes);
    do{
        partida(&e);
        gera_posicao(e, placar, nomes);
        tela_lincol(23, 1);
        printf("PRESSIONE ENTER PARA JOGAR NOVAMENTE\n(qualquer outro botao sai)");
        continua = espera_char();
	tela_limpa();
    } while(continua == c_enter);
    mostra_placar(placar, nomes);
    tela_destroi();
    return 0;
}
