#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    float a = 0.0;
    float b = 0.0;
    char op;

    scanf("%f", &a);
    for(;;){
        op = getchar();
        if (op == '\n') break;
        scanf("%f", &b);
        if (op == '+') a = a + b;
        else if (op == '-') a = a - b;
        else if (op == '*') a = a * b;
        else if (op == '/') a = a / b; 
    }

    printf("RESULTADO: %.2f\n", a);

    return 0;
}
