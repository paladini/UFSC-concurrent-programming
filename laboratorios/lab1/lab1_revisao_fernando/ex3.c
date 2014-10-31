#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>

void *execucaoThread(void *arg) { 
	printf("Nova thread criada. TID == %u\n", (unsigned int) pthread_self());
}

int main() {

	pthread_t thread;
	pthread_create(&thread, NULL, execucaoThread, NULL);
	pthread_join(thread, NULL);
	pthread_exit(NULL);

}