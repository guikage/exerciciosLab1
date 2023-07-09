#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "tela.h"

#define TMAX 30.0

typedef struct{
    bool fim;
    cor cuser;
    cor crand;
    int cor;
    float pontos;
    double inicio;
    double tempo;
} estado;

typedef struct{
    float pontos[5];
    char nomes[5][4];
} placar;

const cor RED = {255, 0, 0};
const cor GREEN = {0, 255, 0};
const cor BLUE = {0, 0, 255};
const cor YELLOW = {255, 255, 0};
const cor CYAN = {0, 255, 255};
const cor MAGENTA = {255, 0, 255};
const cor WHITE = {255, 255, 255};
const cor GRAY = {127, 127, 127};

//funcoes auxiliares:

void poscursor(int lin, int col){
    posicao pos = {lin, col};
    tela_posiciona(pos);
}

int espera_char(){
    int c;
    do {
	    c = tela_le_char();
    } while(c == c_none || c == c_resize);
    return c;
}

//gerenciam pontuacao e placar:

void le_arquivo(placar *p){
    FILE *arq = fopen("./placar.txt", "r");
    if (arq == NULL){
	    arq = fopen("./placar.txt", "w");
	    fprintf(arq, "AAA -1\nAAA -1\nAAA -1\nAAA -1\nAAA -1");
	    fclose(arq);
	    arq = fopen("./placar.txt", "r");
    }
    for (int i = 0; i < 5; i++){
        fscanf(arq, "%s %f", p->nomes[i], &(p->pontos[i]));
    }
    fclose(arq);
}

void grava_arquivo(placar p){
    FILE *arq = fopen("./placar.txt", "w");
    for(int i = 0; i < 5; i++){
	    fprintf(arq, "%s %.1f\n", p.nomes[i], p.pontos[i]);
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
    pontos_r = pontuacao_cor(crand.vermelho, cuser.vermelho);
    pontos_g = pontuacao_cor(crand.verde, cuser.verde);
    pontos_b = pontuacao_cor(crand.azul, cuser.azul);
    pontos = 100 - (pontos_r + pontos_g + pontos_b)/3;
    pontos += pontos * 0.05 * (TMAX - tempo);
    return pontos;
}

int gerencia_placar(float pontos, placar *p){
    for (int i = 0; i < 5; i++){
        if(pontos > p->pontos[i]){
            for (int j = 4; j > i; j--){
                p->pontos[j] = p->pontos[j-1];
                strcpy(p->nomes[j], p->nomes[j-1]);
            }
            p->pontos[i] = pontos;
            return (i+1);
        }
    }
    return 0;
}

void aperta_back(int lin, int col, int *i){
    if ((*i) > 0){
	    (*i)--;
    }
    poscursor(lin, col+(*i));
    for(int j = (*i); j < 3; j++){
	    putchar('_');
    }
    poscursor(lin, col+(*i));
}

void pega_nome(placar *p, int pos, int lin, int col){
    int c, i = 0;
    bool enter = false;
    while(i < 4){
        c = tela_le_char();
        if (c == c_enter && i > 0){
            p->nomes[pos][i] = '\0';
            break;
        }
        else if (c == c_back){
            aperta_back(lin, col, &i);
        }
        else if (c > 32 && c < 127){
            p->nomes[pos][i] = c;
            putchar(c);
            i++;
        }
    }
    p->nomes[pos][3] = '\0';
}

void gera_posicao(estado partida, placar *p){
    int posicao = gerencia_placar(partida.pontos, p);
    if (posicao != 0){
        poscursor(18, 1);
        printf("VOCE FICOU EM %do LUGAR\nDIGITE SEU NOME: ___", posicao);
        poscursor(19, 18);
        pega_nome(p, posicao-1, 19, 18);
        grava_arquivo(*p);
    }
}

//exibem partida:

void barra(int lin, int col, cor c1, int valor){
    poscursor(lin, col);
    for(int i = 0; i < 26; i++){
        if (valor/10 == i) {
            tela_cor_fundo(WHITE); //branco
        }
        else {
            cor c2 = {i*c1.vermelho/255*10, i*c1.verde/255*10, i*c1.azul/255*10};
            tela_cor_fundo(c2); //cor escolhida
        }
        putchar(' ');
    }
    tela_cor_normal();
    printf("%03d", valor);
}

void quadrado(int lin, int col, cor cor){
    tela_cor_fundo(cor);
    for(int i = 0; i < 5; i++){
        poscursor(lin+i, col);
        for(int j = 0; j < 5; j++){
            putchar(' ');
        }
    }
    tela_cor_normal();
}

void indica_cor(int lin, int col, int cor){
    for(int i = 0; i < 3; i++){
	    poscursor(lin+i*2, col);
	    if (i == cor){
            tela_cor_fundo(GREEN);
        }
	    else{
            tela_cor_fundo(GRAY);
        }
	    putchar(' ');
    }
    tela_cor_normal();
}

void mostra_tela(estado e){
    quadrado(1, 1, e.crand);
    quadrado(7, 1, e.cuser);
    indica_cor(7, 7, e.cor);
    barra(7, 8, RED, e.cuser.vermelho);
    barra(9, 8, GREEN, e.cuser.verde);
    barra(11, 8, BLUE, e.cuser.azul);
    poscursor(1, 7);
    printf("PONTUAÇÃO:\t%03.1f", e.pontos);
    poscursor(2, 7);
    printf("TEMPO:\t\t%03.1lf", e.tempo);
}

void imprime_cores_finais(int lin, int col, cor cor, bool user){
    poscursor(lin, col);
    if (user) {
        printf("COR DO USUARIO:");
    }
    else {
        printf("COR GERADA:");
    }
    quadrado(lin+1, col, cor);
    barra(lin+1, col+6, RED, cor.vermelho);
    barra(lin+3, col+6, GREEN, cor.verde);
    barra(lin+5, col+6, BLUE, cor.azul);
}

void mostra_informacoes_finais(estado e){
    tela_limpa();
    imprime_cores_finais(1, 1, e.crand, false);
    imprime_cores_finais(8, 1, e.cuser, true);
    poscursor(15,1);
    printf("PONTUACAO:\t%03.1f\nTEMPO:\t\t%03.1lf", e.pontos, e.tempo);
}

void mostra_placar(int lin, int col, placar p){
    poscursor(lin, col);
    printf("MELHORES PONTUACOES:");
    for (int i = 0; i < 5; i++){
        if(p.pontos[i] >= 0){
            poscursor(lin+2+i, col);
            printf("%3s: %03.1f", p.nomes[i], p.pontos[i]);
        }
    }
}

//alteram partida:

void muda_valor(cor *c1, int c2, int tecla){
    int *cores[3];
    cores[0] = &c1->vermelho;
    cores[1] = &c1->verde;
    cores[2] = &c1->azul;
    switch (tecla){
        case c_left:
            if (*cores[c2] > 0){
                (*cores[c2])--;
            }
            break;
        case c_right:
            if (*cores[c2] < 255){
                (*cores[c2])++;
            }
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
    e->crand.vermelho = rand()%256;
    e->crand.verde = rand()%256;
    e->crand.azul = rand()%256;
    e->cuser.vermelho = 0;
    e->cuser.verde = 0;
    e->cuser.azul = 0;
    if(e->crand.vermelho < 128){
        e->cuser.vermelho = 255;
    }
    if(e->crand.verde < 128){
        e->cuser.verde = 255;
    }
    if(e->crand.azul < 128){
        e->cuser.azul = 255;
    }
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
    muda_valor(&(e->cuser), e->cor, tecla);
    }
}

void altera_estado(estado *e){
    le_tecla(e);
    e->pontos = pontuacao(e->crand, e->cuser, TMAX);
    e->tempo = tela_relogio() - e->inicio;
    if (e->tempo >= TMAX){
/// faz e-tempo = TMAX, ou pode dar bônus negativo (ou testa no cálculo do bônus)      
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

//tela de titulo:

void title_screen(placar p){
    poscursor(1, 18);
    tela_cor_letra(RED);
    putchar('C');
    tela_cor_letra(YELLOW);
    putchar('O');
    tela_cor_letra(GREEN);
    putchar('L');
    tela_cor_letra(CYAN);
    putchar('O');
    tela_cor_letra(BLUE);
    putchar('R');
    tela_cor_letra(MAGENTA);
    putchar('S');
    tela_cor_normal();
    mostra_placar(3, 1, p);
    poscursor(21, 1);
    printf("PRESSIONE QUALQUER TECLA PARA JOGAR");
    espera_char();
}

//o jogo (perdi)

void jogo(estado *e, placar *p){
    int continua;
    do{
        tela_limpa();
        partida(e);
        gera_posicao(*e, p);
        mostra_placar(1, 40, *p);
        poscursor(21, 0);
        printf("PRESSIONE ENTER PRA CONTINUAR\nOU BACKSPACE PARA SAIR");
        do{
            continua = espera_char();
        }while (continua != c_enter && continua != c_back);
    } while(continua == c_enter);
}

//a poderosa main:

int main(){
    srand(time(0));
    tela_cria();
    tela_mostra_cursor(false);
    estado e;
    placar p;
    le_arquivo(&p);
    title_screen(p);
    jogo(&e, &p);
    tela_destroi();
    printf("tchau");
    return 0;
}
