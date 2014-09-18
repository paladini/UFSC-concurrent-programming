#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "queue.h"
#define CADEIRAS 4
#define TOTAL_CLIENTES 10
#define TOTAL_FUNCIONARIOS 2
queue_t fila;
sem_t lockFuncionario;
sem_t lockCliente;
sem_t lock;
sem_t espera;
sem_t cliente;
pthread_t funcionarios[TOTAL_FUNCIONARIOS];
pthread_t clientes[TOTAL_CLIENTES];
void *t_funcionarios(void *argumento){
	long int id_thread = (long int)argumento;
	while(1){
		
		sem_wait(&lockFuncionario);
		long int id_cliente = dequeue(&fila);
		 printf("Funcionario %d: atendendo cliente %ld (%d/%d lugares ocupados)\n", (unsigned int)id_thread, id_cliente, length(&fila), CADEIRAS);
		//sem_post(&cliente);
		sem_post(&espera);
		sem_post(&lockFuncionario);
		sleep(5 + rand()%6);
		sem_post(&espera);
		printf("Funcionario %d: terminou de atender cliente %ld (%d/%d lugares ocupados)\n", (unsigned int)id_thread, id_cliente, length(&fila), CADEIRAS);
	}
}
int tamanho(){
	sem_wait(&lock);
	return length(&fila);
	sem_wait(&lock);
}
void *t_clientes(void *argumento){
	int id_thread = (int)argumento;
	while(1){
		if(length(&fila) < CADEIRAS){
			//sem_wait(&cliente);
			sem_wait(&lockCliente);
			enqueue(&fila, id_thread);
			printf("Cliente %d: chegou (%d/%d lugares ocupados)\n", (unsigned int)id_thread, length(&fila), CADEIRAS);
			//sem_post(&espera);
			sem_post(&lockCliente);
			sem_wait(&espera);
		} else {
			printf("Cliente %d: cartorio lotado, saindo para dar uma volta (%d/%d lugares ocupados)\n", (unsigned int)id_thread, length(&fila), CADEIRAS);
			
		}
		sleep(10);
	}
}
void criarThreads(){
	int i;
	for(i = 0; i < TOTAL_CLIENTES; i++){
		long int id_thread = i;
		pthread_create(&clientes[i], NULL, t_clientes, (void*)id_thread);
	}
	for(i = 0; i < TOTAL_FUNCIONARIOS; i++){
		long int id_thread = i;
		pthread_create(&funcionarios[i], NULL, t_funcionarios, (void*)id_thread);
	}
}
void esperarThreads(){
	int i;
	for(i = 0; i < TOTAL_FUNCIONARIOS; i++){
		pthread_join(clientes[i], NULL);
	}
	for(i = 0; i < TOTAL_CLIENTES; i++){
		pthread_join(funcionarios[i], NULL);
	}
}
int main(){
	init_queue(&fila);
	sem_init(&cliente, 0, CADEIRAS);
	sem_init(&espera, 0, 0);
	sem_init(&lock, 0, 0);
	sem_init(&lockFuncionario, 0, 1);
	sem_init(&lockCliente, 0, 1);
	criarThreads();
	esperarThreads();
	sem_destroy(&lockFuncionario);
	sem_destroy(&lockCliente);
	sem_destroy(&espera);
	sem_destroy(&cliente);
	pthread_exit(NULL);
}
