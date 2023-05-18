#include<stdio.h>
#include<stdlib.h>

int main(){
	int *batata = (int*)malloc(sizeof(int));
	int buffer;
	int i = 0;
	int j = 0;

	for(;;){
		scanf("%d", &buffer);
		if(buffer != 0){
			batata = realloc(batata, (i+1)*sizeof(int));
			batata[i] = buffer;
			i++;
			printf("%d %d\n", i, buffer);
		} else break;
	}
	for(j = 0; j < i; j++){
		printf("%d ", batata[j]);
	}
	return 0;
}
