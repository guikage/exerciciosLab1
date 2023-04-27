#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

float calculadora(void){
    float a = 0.0;
    float b = 0.0;
    float c = 0.0;
    char op;

    scanf("%f", &a);
    for(;;){
        op = getchar();
	while(op == ' ') op = getchar();
        if (op == '\n' || op == '='){
	    a = a + c;
	    break;
	}
        scanf("%f", &b);
        switch (op){
	    case '+':
		c = a;
		a = b;
		break;
	    case '-':
		c = a;
		a = -b;
		break;
	    case '*':
		a = a * b;
		a = a + c;
		c = 0;
		break;
	    case '/':
		a = a / b;
		a = a + c;
		c = 0;
		break;
	}
    }
    return a;
}

int main(){
    float res = calculadora();
    printf("\nRESULTADO: %.2f\n", res);
    return 0;
}
