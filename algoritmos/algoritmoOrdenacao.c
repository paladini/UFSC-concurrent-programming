#include <stdio.h>

void test(){
		
	
}

void print(int vetor[]){
	printf("[ ");
	int i = 0;
	for(i; i < 6; i++){
		printf("%d  ", vetor[i]);
	}
	printf("]\n");
}

void main(){
	
	int vetor[6] = { 6, 4, 5, 0, 8, 9};
	print(vetor); 
	
	// codigo concebido com Threads
}
