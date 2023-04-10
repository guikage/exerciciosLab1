#include <stdio.h>

int q(int v)
{
  int x;
  x = v*v;
  return x;
}

int menor(int a, int b){ //*
    if (a > b){
        return b;
    }
    return a;
}

int maior(int a, int b){ //**
    if (a < b){
        return b;
    }
    return a;
}

int maior3(int a, int b, int c){ //***
    if(a > b && a > c){
        return a;
    } else if (b > c){
        return b;
    }
    return c;
}

int intermediario3(int a, int b, int c){ //****
    if(a > b){
        if(a > c){
            if(b > c){
                return b;
            }
            return c;
        }
        return a;
    } else if(a > c){
        return a;
    } else if(b > c){
        return c;
    }
    return b;
}

void entre1evalor(int v){ //*****
    int i = 1;
    while(i <= v){
        printf("%d\n", i);
        i++;
    }
}

void pares(int a, int b){ //******
    int i = a+1;
    while(i < b){
        if(!(i%2)){
            printf("%d\n", i);
        }
        i++;
    }
}

int main()
{
    int x;
    int y;
    int z;

    x = 5;
    y = q(x);
    printf("%d %d\n", y, x);

    y = 7;
    z = 6;

    printf("%d\n", menor(x, y));
    printf("%d\n", maior(x, y));
    printf("%d\n", menor(maior(x, y), z));
    printf("%d\n", menor(maior(6, 7), 5));
    printf("%d\n", maior3(x, y, z));
    printf("%d\n", intermediario3(x, y, z));
    entre1evalor(x);
    pares(3, 9);

    return 0;
}

/*
respostas:

1: 25 5
2: *
3: **
4: 6
5: nao, se z for o menor numero
6: ***
7: ****
8: *****
9: ******

*/
