#include <stdio.h>

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
            return a;
    }
}

int main(){
    float total = 0.0;
    float resto = 0.0;
    float valor = 0.0;
    char op = ' ';
    char op2 = '+';

    scanf("%f", &total);
    op = getchar();
    while (op == ' ') op = getchar(); //enquanto receber ' ' repete
    if(op == '*' || op == '/'){ //se for mult ou div passa total pro resto pra efetuar op
        resto = total;
        total = 0;
    } else { //se for adc ou sub salva a op como op2
        op2 = op;
    }
    for(;;){
        if (op == '\n' || op == '='){ //para o codigo
            total = opera(total, resto, op2); //confere se tem resto no resto
            break;
        }
        scanf("%f", &valor);
        if (op == '*' || op == '/'){
            resto = opera(resto, valor, op); //opera o resto com o valor
        } else if (op == '+' || op == '-'){
            total = opera(total, resto, op2); //opera o total com o resto usando op2
            resto = valor; //valor recebido se torna o resto
            op2 = op; //op recebido se torna op2
        }
        op = getchar();
        while (op == ' ') op = getchar();
    }

    printf("RESULTADO: %.2f\n", total);

    return 0;
}
