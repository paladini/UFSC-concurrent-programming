#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#define MAX_THREADS 5

void *execucaoThread(void *arg) { 
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

	// excluindo
	pthread_exit(NULL);

}