#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "tela/tela.h"

#include "efe_logica.h"
#include "efe_tela.h"
#include "efe_placar.h"

void pega_nome(placar *p, int pos){
    int c, i = 0;
    while(i < 7){
        c = tela_tecla();
        if (c == c_enter && i > 0){
            p->nome[pos][i] = '\0';
            break;
        }
        else if (c == c_back){
            p->nome[pos][i] = '\0';
            if(i > 0){
                i--;
            }
        }
        else if (c > 32 && c < 127){
            p->nome[pos][i] = c;
            i++;
        }
        if (c != c_none){
            tela_texto(320, 180, 32, branco, p->nome[pos]);
            tela_atualiza();
        }
    }
    p->nome[pos][6] = '\0';
}

void gera_posicao(partida p, placar *pl){
    char str[30];
    int posicao = gerencia_placar(p.pontos, pl);
    if (posicao != 0){
        grava_arquivo(*pl);
        sprintf(str, "VOCE FICOU EM %do LUGAR!", posicao);
        tela_texto(320, 120, 32, branco, str);
        pega_nome(pl, posicao-1);
    }
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
    bool moveu;
    p->tecla = tela_tecla();
    if(p->tecla != c_none){
        testa_tecla(p);
        p->moveu = false;
        for(int i = 0; i < 5; i++){
            moveu = desloca(p, i);
	    p->moveu = p->moveu || moveu;
        }
        if(p->moveu){
            adiciona_letra(p);
        }
        p->casas = verifica_casas(*p);
        if(p->casas <= 0){
            p->perdeu = verifica_perdeu(*p);
        }
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
    }while (!(p->perdeu) && !(p->ganhou));
    fim_de_jogo(*p, pl);
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
    int seletor = 0, seletor2, coord;
    do{
        tela_texto(320, 160, 64, branco, "EFE");
        tela_texto(320, 300, 32, branco, "JOGAR");
        tela_texto(320, 340, 32, branco, "RANKING");
        tela_texto(320, 380, 32, branco, "SAIR");
        seletor2 = muda_seletor(seletor);
        if(seletor2 != -1){
	    seletor = seletor2;
        }
        switch(seletor){
	    case 0:
                coord = 300;
                break;
	    case 1:
                coord = 340;
                break;
       	    case 2:
                coord = 380;
                break;
        }
        tela_texto(200, coord, 32, branco, "-");
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
    bool sair = false;
    while(!sair){
        seletor = menu();
        switch(seletor){
            case 0:
                jogo(&p, &pl);
                break;
            case 1:
                ranking(pl);
                break;
            case 2:
                sair = true;
                break;
            default:
                break;
        }
    }
    tela_fim();
}
