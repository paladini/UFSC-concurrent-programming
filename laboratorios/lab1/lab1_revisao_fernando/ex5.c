#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#define MAX_THREADS 5
#define ITERATIONS_OVER_THREAD 100

int contador_global = 0;

void *execucaoThread(void *arg) { 
	int i;
	for(i = 0; i < ITERATIONS_OVER_THREAD; i++){
		contador_global++;
	}
	printf("Nova thread criada. TID == %u\n", (unsigned int) pthread_self());
}

int main() {

	// criando threads
	pthread_t vetorThreads[MAX_THREADS];
	int i;
	for(i = 0; i < MAX_THREADS; i++) {
		pthread_create(&vetorThreads[i], NULL, execucaoThread, NULL);
	}

	// sincronizando
	for(i = 0; i < MAX_THREADS; i++) {
		pthread_join(vetorThreads[i], NULL);
	}

	printf("O valor do contador_global eh: %d\n", contador_global);

	// excluindo
	pthread_exit(NULL);

}