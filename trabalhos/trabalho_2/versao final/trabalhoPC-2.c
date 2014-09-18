#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "queue.h"
#include <time.h>
#define CADEIRAS 4
#define TOTAL_CLIENTES 10
#define TOTAL_FUNCIONARIOS 2
queue_t fila;
sem_t lockBinarioFuncionario;//este lock funcinará, também, para que o printf não "printe" o valor errado de length!
sem_t lockCheio;
sem_t lockVazio;
sem_t lockBinarioTeste;
sem_t semaphore[TOTAL_CLIENTES];
pthread_t funcionarios[TOTAL_FUNCIONARIOS];
pthread_t clientes[TOTAL_CLIENTES];
void *t_funcionarios(void *argumento){
	long int id_thread = (long int)argumento;
	while(1){
		sem_wait(&lockVazio);
		sem_wait(&lockBinarioFuncionario);
		long int id_cliente = dequeue(&fila);
		 printf("Funcionario %d: atendendo cliente %ld (%d/%d lugares ocupados)\n", (unsigned int)id_thread, id_cliente, length(&fila), CADEIRAS);
		sem_post(&lockBinarioFuncionario);
		sleep(5 + rand()%6);
		sem_wait(&lockBinarioFuncionario);
		printf("Funcionario %d: terminou de atender cliente %ld (%d/%d lugares ocupados)\n", (unsigned int)id_thread, id_cliente, length(&fila), CADEIRAS);
		sem_post(&lockBinarioFuncionario);
		sem_post(&lockCheio);
		sem_post(&semaphore[id_cliente]);
	}
}
void *t_clientes(void *argumento){
	long int id_thread = (long int)argumento;
	while(1){
		sem_wait(&lockBinarioTeste);
		if(length(&fila) < CADEIRAS){
			sem_wait(&lockBinarioFuncionario);
			enqueue(&fila, id_thread);
			printf("Cliente %d: chegou (%d/%d lugares ocupados)\n", (unsigned int)id_thread, length(&fila), CADEIRAS);
			sem_post(&lockBinarioFuncionario);
			sem_post(&lockBinarioTeste);
			sem_wait(&lockCheio);
			sem_post(&lockVazio);
			sem_wait(&semaphore[id_thread]);
		} else {
			sem_wait(&lockBinarioFuncionario);
			printf("Cliente %d: cartorio lotado, saindo para dar uma volta (%d/%d lugares ocupados)\n", (unsigned int)id_thread, length(&fila), CADEIRAS);
			sem_post(&lockBinarioFuncionario);
			sem_post(&lockBinarioTeste);
		}
		sleep(10);
	}
}
void criarThreads(){
	int i;
	for(i = 0; i < TOTAL_CLIENTES; i++){
		long int id_Cliente = i;
		sem_init(&semaphore[i], 0, 0);
		pthread_create(&clientes[i], NULL, t_clientes, (void*)id_Cliente);
	}
	for(i = 0; i < TOTAL_FUNCIONARIOS; i++){
		long int id_Funcionario = i;
		pthread_create(&funcionarios[i], NULL, t_funcionarios, (void*)id_Funcionario);
	}
}
void esperarThreads(){
	int i;
	for(i = 0; i < TOTAL_CLIENTES; i++){
		pthread_join(clientes[i], NULL);
	}
	for(i = 0; i < TOTAL_FUNCIONARIOS; i++){
		pthread_join(funcionarios[i], NULL);
	}
}
void destroySemaphore(){
	int i;
	for(i = 0; i < TOTAL_CLIENTES; i++){
		sem_destroy(&semaphore[i]);
	}
        sem_destroy(&lockVazio);
        sem_destroy(&lockCheio);
        sem_destroy(&lockBinarioTeste);
        sem_destroy(&lockBinarioFuncionario);

}
int main(int argc, char **argv){
	init_queue(&fila);
	sem_init(&lockBinarioTeste, 0, 1);
	sem_init(&lockBinarioFuncionario, 0, 1);
	sem_init(&lockCheio, 0, TOTAL_FUNCIONARIOS);
	sem_init(&lockVazio,0,0);
	criarThreads();
	esperarThreads();
	destroySemaphore();
	pthread_exit(NULL);
}
