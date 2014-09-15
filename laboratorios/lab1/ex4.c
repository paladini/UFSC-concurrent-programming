#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#define MAXTHREADS 5
#define ITERATIONS_INSIDE_THREAD 100

int contador_global = 0;

void *imprimirThread(void* arg){
	int i = 0;
	for(i; i < ITERATIONS_INSIDE_THREAD; i++){
		contador_global++;
	}
}

void main(){

	// Criando threads
	pthread_t vetorThreads[MAXTHREADS];
	int i = 0;
	for(i; i < MAXTHREADS; i++){
		pthread_t thread;
		vetorThreads[i] = thread;
		pthread_create(&vetorThreads[i], NULL, imprimirThread, NULL);
	}
	printf("Printando valor do contador global: %d", contador_global);	

	// Aguardando threads finalizar
	i = 0;
	for(i; i < MAXTHREADS; i++){
		pthread_join(vetorThreads[i], NULL);
	}

	// Destroindo threads
	pthread_exit(NULL);
}
