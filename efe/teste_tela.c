#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"tela/tela.h"

#define fucsia tela_cria_cor(1, 0.2, 0.8)
#define TAM_R 64
#define INI_T 32
#define DIST_R 0

void desenha_tabuleiro(void){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            tela_retangulo(INI_T+i*TAM_R+DIST_R, INI_T+j*TAM_R+DIST_R, INI_T+(i+1)*TAM_R, INI_T+(j+1)*TAM_R, 2, branco, preto);
        }
    }
}

int main(){
    int posx, posy;
    tela_inicio(640, 480, "main");
    for(;;){
        desenha_tabuleiro();

        posx = tela_rato_x();
        posy = tela_rato_y();
        tela_texto_dir(8, 8, 16, branco, "oi");
        tela_retangulo(posx-4, posy-4, posx+4, posy+4, 0, vermelho, branco);
        tela_atualiza();
        if(tela_rato_clicado()) break;
    }
    tela_fim();
}

