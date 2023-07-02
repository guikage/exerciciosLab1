#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "efe_logica.h"
#include "efe_placar.h"
#include "tela/tela.h"

void le_arquivo(placar *p);
void grava_arquivo(placar p);
int gerencia_placar(int pontos, placar *p);

void le_arquivo(placar *p){
    FILE *arq = fopen("./placar.txt", "r");
    if (arq == NULL){
	    arq = fopen("./placar.txt", "w");
	    fprintf(arq, "A -1\nA -1\nA -1\nA -1\nA -1");
	    fclose(arq);
	    arq = fopen("./placar.txt", "r");
    }
    for (int i = 0; i < 5; i++){
        fscanf(arq, "%s %d", p->nome[i], &(p->pontos[i]));
    }
    fclose(arq);
}

void grava_arquivo(placar p){
    FILE *arq = fopen("./placar.txt", "w");
    for(int i = 0; i < 5; i++){
	    fprintf(arq, "%s %d\n", p.nome[i], p.pontos[i]);
    }
    fclose(arq);
}

int gerencia_placar(int pontos, placar *p){
    for (int i = 0; i < 5; i++){
        if(pontos > p->pontos[i]){
            for (int j = 4; j > i; j--){
                p->pontos[j] = p->pontos[j-1];
                strcpy(p->nome[j], p->nome[j-1]);
            }
            p->pontos[i] = pontos;
            return (i+1);
        }
    }
    return 0;
}
