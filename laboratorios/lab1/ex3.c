#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

void *imprimirThread(void* arg){
	printf("Nova thread criada. TID == %u \n", pthread_self());
}

void main(){
	pthread_t thread;
	pthread_create(&thread, NULL, imprimirThread, NULL);
	pthread_join(thread, NULL);
	pthread_exit(NULL);
}
