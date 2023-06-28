#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "tela/tela.h"

#include "efe_logica.h"
#include "efe_tela.h"

void jogo(partida *p){
    inicializa(p);
    adiciona_letra(p);
    imprime_matriz(*p);
    imprime_pontuacao(*p);
    tela_atualiza();
    bool moveu;
    for(;;){
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
        }
        imprime_matriz(*p);
        imprime_pontuacao(*p);
        tela_atualiza();
    }
}

int main(){
    srand(time(0));
    tela_inicio(640, 480, "jogo");
    partida p;
    jogo(&p);
    tela_fim();
}
