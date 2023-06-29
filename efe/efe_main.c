#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "tela/tela.h"

#include "efe_logica.h"
#include "efe_tela.h"

void fim_de_jogo(partida p){
    int sair;
    imprime_matriz(p);
    imprime_pontuacao(p);
    tela_retangulo(180, 200, 460, 280, 4, branco, preto); 
    if(p.ganhou){
        tela_texto(320, 240, 32, branco, "VOCE GANHOU!");
    }
    else if(p.perdeu){
        tela_texto(320, 240, 32, branco, "VOCE PERDEU!");
    }
    tela_atualiza();
    do{
	sair = tela_tecla();
    }while(sair != c_enter);
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

void jogo(partida *p){
    inicializa(p);
    imprime_matriz(*p);
    imprime_pontuacao(*p);
    adiciona_letra(p);
    adiciona_letra(p);
    tela_atualiza();
    bool moveu;
    do{
	loop_jogo(p);
    }while (!(p->perdeu) && !(p->ganhou));
    fim_de_jogo(*p);
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
    }else if(tecla == c_down){
	if(seletor < 2){
            seletor++;
	}
	else{
            seletor = 0;
	}
    }else if(tecla == c_enter){
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
    int seletor;
    for(;;){
	seletor = menu();
	switch(seletor){
	    case 0:
		jogo(&p);
		break;
	    case 1:
		break;
	    case 2:
		exit(0);
	    default:
		break;
	}
    }
    tela_fim();
}
