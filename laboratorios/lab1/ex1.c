#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

void main(){
	
	fork();
	printf("Novo processo criado!\n");

}
