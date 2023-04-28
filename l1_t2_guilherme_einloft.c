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
    float a = 0.0;
    float b = 0.0;
    char op;

    scanf("%f", &a);
    for(;;){
        op = getchar();
        if (op == '\n') break;
        scanf("%f", &b);
        a = opera(a, b, op);
    }

    printf("RESULTADO: %.2f\n", a);

    return 0;
}
