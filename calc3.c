#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

float opera(float a, float b, char op){
    switch (op){
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            return a/b;
        default:
            return a+b;
    }
}

int main(){
    float total = 0.0;
    float resto = 1.0;
    float valor = 0.0;
    char op;
    char op2;

    scanf("%f", &total);
    op = getchar();
    if(op == '*' || op == '/'){
        resto = total;
        total = 0;
    } else {
        resto = 0;
        op2 = op;
    }
    for(;;){
        if (op == '\n'){
            total = opera(total, resto, op2);
            break;
        }
        scanf("%f", &valor);
        if (op == '*' || op == '/'){
            resto = opera(resto, valor, op);
        } else if (op == '+' || op == '-'){
            total = opera(total, resto, op2);
            resto = valor;
            op2 = op;
        }
        op = getchar();
    }

    printf("RESULTADO: %.2f\n", total);

    return 0;
}
