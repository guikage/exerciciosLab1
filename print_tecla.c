#include <stdio.h>
#include "tela.h"

int main(){
	tela_cria();
	int tecla;
	for(;;){
		tecla = tela_le_char();
		if (tecla != -1000) printf("%d\n", tecla);
	}
	return 0;
}
