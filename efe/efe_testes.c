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
    imprime_matriz(*p);
    imprime_pontuacao(*p);
    adiciona_letra(p);
    adiciona_letra(p);
    tela_atualiza();
    bool moveu;
    char debug[20];
    do{
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
        sprintf(debug, "%d", p->casas);
        tela_texto_dir(400, 400, 16, branco, debug);
        tela_atualiza();
    }while (!(p->perdeu) && !(p->ganhou));
}

int main(){
    srand(time(0));
    tela_inicio(640, 480, "jogo");
    partida p;
    jogo(&p);
    tela_fim();
}
