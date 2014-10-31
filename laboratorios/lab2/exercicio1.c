#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>

#define MAXTHREADS 128
#define ITERATIONS_INSIDE_THREAD 100

int contador_global = 0;
sem_t sem;

void *imprimirThread(void* arg){
	sem_wait(&sem);
	int i = 0;
	for(i; i < ITERATIONS_INSIDE_THREAD; i++){
		contador_global++;
	}
	sem_post(&sem);
}

void main(){
		
	// Variaveis
	int i = 0;
	pthread_t vetorThreads[MAXTHREADS];

	// Inicializando semáforo binário
	sem_init(&sem, 0, 1);

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
	
	printf("Printando valor do contador global: %d \n", contador_global);	

	// Destroindo mutex, semáforos e threads
	sem_destroy(&sem);
	pthread_exit(NULL);
}
