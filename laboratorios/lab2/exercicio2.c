#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#define NUMERO_PRODUTORES 10
#define NUMERO_CONSUMIDORES 2
#define TAMANHO_BUFFER 40

// Variáveis globais
pthread_t vetorProdutores[NUMERO_PRODUTORES];
pthread_t vetorConsumidores[NUMERO_CONSUMIDORES];
sem_t vazio;
sem_t cheio;
sem_t lockProdutor;
sem_t lockConsumidor;

// Buffer
int buffer[TAMANHO_BUFFER], i = 0, f = 0, tamanhoLoop = 1000;

void *produtor(void *arg) {
	while (tamanhoLoop != 0) {
		sem_wait(&vazio);
		sem_wait(&lockProdutor);
		int temp = (f + 1) % TAMANHO_BUFFER;
		buffer[temp] = 1;
		printf("Produzido 1 elemento em %d\n", temp);
		f++;
		tamanhoLoop--;
		sem_post(&lockProdutor);
		sem_post(&cheio);
	}
}

void *consumidor(void *arg) {
	while (tamanhoLoop != 0) {
		sem_wait(&cheio);
		sem_wait(&lockConsumidor);
		int temp = (i + 1) % TAMANHO_BUFFER;
		buffer[temp] = 0;
		printf("Consumido elemento em %d\n", temp);
		i--;
		sem_post(&lockConsumidor);
		sem_post(&vazio);	
	}
}

void distinguirAcaoThread(pthread_t t, int isConsumidor, int desejaCriarThreads) {
	if (desejaCriarThreads == 1) {
		if (isConsumidor == 1) {
			pthread_create(&t, NULL, consumidor, NULL);
		} else {
			pthread_create(&t, NULL, produtor, NULL);
		}
	} else {
		pthread_join(t, NULL);
	}
}

void criarEsperarThreads(int desejaCriarThreads){
	// Consumidores
	for(i = 0; i < NUMERO_CONSUMIDORES; i++) {
		distinguirAcaoThread(vetorConsumidores[i], 1, desejaCriarThreads);
	}

	// Produtores
	for(i = 0; i < NUMERO_PRODUTORES; i++) {
		distinguirAcaoThread(vetorProdutores[i], 0, desejaCriarThreads);
	}
}

void imprimirBuffer(){
	int i;
	printf("[");
	for (i = 0; i < TAMANHO_BUFFER; i++) {
		printf(" %d ", i);
	}
	printf("]");
}

int main() {
	// Criando semáforos
	sem_init(&vazio, 0, TAMANHO_BUFFER);
	sem_init(&cheio, 0, 0);
	sem_init(&lockConsumidor, 0, 1);
	sem_init(&lockProdutor, 0, 1);

	// Criando e esperando threads
	criarEsperarThreads(1);
	criarEsperarThreads(0);

	// Imprimindo buffer para ver resultado
	imprimirBuffer();

	// Destruindo semáforos
	sem_destroy(&cheio);
	sem_destroy(&vazio);
	sem_destroy(&lockProdutor);
	sem_destroy(&lockConsumidor);
	return 0;

}