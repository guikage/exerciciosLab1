#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int strtam(char *s){
    int i = 0;
    for(;;){
        if(s[i] == '\0') break;
        i++;
    }
    return i;
}

void strcopy(char *s1, char *s2, int tam2){
    int i, tam1;
    tam1 = strtam(s1)+1;
    if (tam2 < tam1) return;
    for(i = 0; i < tam1; i++){
        s2[i] = s1[i];
    }
}

void strconcat(char *s1, int tam1, char *s2){
    int i, tams1, tams2;
    tams1 = strtam(s1);
    tams2 = strtam(s2);
    if (tam1 < tams1 + tams2 + 1) return;
    for(i = tams1; i < (tams1 + tams2 + 1); i++){
        s1[i] = s2[i-tams1];
    }
}

bool palindromo(char *s){
    int tam = strtam(s);
    bool p = true;
    for (int i = 0; i < tam/2; i++){
        if(s[i] != s[tam-i-1]) p = false;
    }
    return p;
}

int vogais(char *s){
    int tam = strtam(s);
    char vogais[] = "aeiouAEIOU";
    int nvogais = 0;
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < 10; j++){
            if(s[i] == vogais[j]) nvogais++;
        }
    }
    return nvogais;
}

void remove_vogal(char *s){
    int i = 0, tam = strtam(s);
    char vogais[] = "aeiouAEIOU";
    for(;;){
        if (s[i] == '\0') break;
        for(int j = 0; j < 10; j++){
            if(s[i] == vogais[j]){
                for(int k = i; k <= tam; k++){
                    s[k] = s[k+1];
                }
                tam--;
            }
        }
        i++;
    }
}

int poschar(char *s, char c){
    for(int i = 0; i < strtam(s); i++){
        if(s[i] == c) return i;
    }
    return -1;
}

void remove_espaco(char *s){
    int i = 0, j;
    for(;;){
        if (s[i] == '\0') break;
        if (s[i] == ' ' && (s[i+1] == ' ' || s[i+1] == '\0')){
            j = i;
            for(;;){
                s[j] = s[j+1];
                if(s[j] == '\0') break;
                j++;
            }
        }
        else i++;
    }
}

int compara(char s1[], char s2[]){
    int i;
    for(;;){
        if(s1[i] == s2[i]){
            if(s1[i] == '\0') return 0;
        } else {
            if(s1[i] == '\0') return (0-s2[i]);
            else if(s1[i] == '\0') return (s1[i]);
            else return (s1[i] - s2[i]);
        }
        i++;
    }
    return 0;
}

int main(){
    char str1[] = "excesso";
    char str2[] = "excecao";
    int comp;
    comp = compara(str1, str2);
    printf("%d\n", comp);
    comp = compara(str2, str1);
    printf("%d\n", comp);
    comp = compara(str1, str1);
    printf("%d\n", comp);

    return 0;
}
