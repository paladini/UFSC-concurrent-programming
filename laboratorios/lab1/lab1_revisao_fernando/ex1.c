#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

int main(){

	fork();
	printf("Novo processo criado!\n");

}