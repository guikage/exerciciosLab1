#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "tela/tela.h"

#include "efe_logica.h"
#include "efe_tela.h"
#include "efe_placar.h"

void aperta_enter(placar *pl, int i, int pos){
    if(i > 0){
        pl->nome[pos][i] = '\0';
    }
    else{
	strcpy(pl->nome[pos], "AAA");
    }
}

void aperta_back(placar *pl, int *i, int pos){
    if(*i > 0){
        (*i)--;
        pl->nome[pos][(*i)] = '\0';
    }
}

void pega_nome(placar *pl, int pos){
    int c, i = 0;
    strcpy(pl->nome[pos], " ");
    for(;;){
        c = tela_tecla();
        if (c == c_enter){
            aperta_enter(pl, i, pos);
            break;
        }
        else if (c == c_back){
            aperta_back(pl, &i, pos);
        }
        else if (c > 32 && c < 127){
	        if(i < 15){
                pl->nome[pos][i] = c;
                pl->nome[pos][i+1] = '\0';
                i++;
	        }
        }
        imprime_nome(*pl, pos);
    }
    pl->nome[pos][15] = '\0';
}

void gera_posicao(partida p, placar *pl){
    char str[30];
    int posicao = gerencia_placar(p.pontos, pl);
    if (posicao != 0){
        grava_arquivo(*pl);
        pega_nome(pl, posicao-1);
    }
}

void pause(partida *p){
    int sair;
    imprime_pause(*p);
    do{
	    sair = tela_tecla();
    }while(sair != c_enter && sair != c_esc);
    if(sair == c_esc){
        p->saiu = true;
        p->pontos = -2;
    }
    p->pausou = false;
}

void fim_de_jogo(partida p, placar *pl){
    int sair;
    imprime_fim_de_jogo(p);
    do{
	    sair = tela_tecla();
    }while(sair != c_enter);
    gera_posicao(p, pl);
}

void loop_jogo(partida *p){
    p->tecla = tela_tecla();
    if(p->tecla != c_none){
        testa_tecla(p);
        if(p->mover){
            p->moveu = desloca_todos(p);
            if(p->moveu){
                adiciona_letra(p);
            }
            p->casas = verifica_casas(*p);
            if(p->casas <= 0){
                p->perdeu = verifica_perdeu(*p);
            }
        }
    }
    if(p->pausou){
        pause(p);
    }
    imprime_matriz(*p);
    imprime_pontuacao(*p);
    tela_atualiza();
}

void ranking(placar pl){
    int sair;
    imprime_placar(pl);
    do{
	    sair = tela_tecla();
    }while(sair != c_enter);
}

void jogo(partida *p, placar *pl){
    inicializa(p);
    imprime_matriz(*p);
    imprime_pontuacao(*p);
    adiciona_letra(p);
    adiciona_letra(p);
    tela_atualiza();
    do{
        loop_jogo(p);
    }while (!(p->perdeu) && !(p->ganhou) && !(p->saiu));
    if(!(p->saiu)){
    	fim_de_jogo(*p, pl);
    }
}

int muda_seletor(int seletor){
    int tecla;
    tecla = tela_tecla();
    if(tecla == c_up){
        if(seletor > 0){
            seletor--;
        }
        else{
            seletor = 2;
        }
    }
    else if(tecla == c_down){
        if(seletor < 2){
            seletor++;
        }
        else{
            seletor = 0;
        }
    }
    else if(tecla == c_enter){
        seletor = -1;
    }
    return seletor;
}

int menu(){
    int seletor = 0, seletor2;
    do{
        tela_texto(320, 160, 64, branco, "EFE");
        tela_texto(320, 300, 32, branco, "JOGAR");
        tela_texto(320, 340, 32, branco, "RANKING");
        tela_texto(320, 380, 32, branco, "SAIR");
        seletor2 = muda_seletor(seletor);
        if(seletor2 != -1){
	    seletor = seletor2;
        }
        if(seletor == 0){
            tela_texto(200, 300, 32, branco, ">");
        }
        else if(seletor == 1){
            tela_texto(200, 340, 32, branco, ">");
        }
        else if(seletor == 2){
            tela_texto(200, 380, 32, branco, ">");
        }
        tela_atualiza();
    }while(seletor2 != -1);
    return seletor;
}

int main(){
    srand(time(0));
    tela_inicio(640, 480, "jogo");
    partida p;
    placar pl;
    le_arquivo(&pl);
    int seletor;
    for(;;){
        seletor = menu();
        if(seletor == 0){
            jogo(&p, &pl);
        }
        else if(seletor == 1){
            ranking(pl);
        }
        else if(seletor == 2){
            break;
        }
    }
    grava_arquivo(pl);
    tela_fim();
}
