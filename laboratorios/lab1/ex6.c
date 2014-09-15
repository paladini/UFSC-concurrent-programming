#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

#define MAXTHREADS 128
#define ITERATIONS_INSIDE_THREAD 100

int contador_global = 0;
pthread_mutex_t mutex;

void *imprimirThread(void* arg){
	pthread_mutex_lock(&mutex);
	int i = 0;
	for(i; i < ITERATIONS_INSIDE_THREAD; i++){
		contador_global++;
	}
	pthread_mutex_unlock(&mutex);
}

void main(){
		
	// Variaveis
	int i = 0;
	pthread_t vetorThreads[MAXTHREADS];


	// Inicializando mutex
	pthread_mutex_init(&mutex, NULL);

	// Criando threads
	for(i; i < MAXTHREADS; i++){
		pthread_t thread;
		vetorThreads[i] = thread;
		pthread_create(&vetorThreads[i], NULL, imprimirThread, NULL);
	}

	// Aguardando threads finalizar
	for(i = 0; i < MAXTHREADS; i++){
		pthread_join(vetorThreads[i], NULL);
	}
	
	printf("\nPrintando valor do contador global: %d \n", contador_global);	

	// Destroindo mutex e threads
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);
}
