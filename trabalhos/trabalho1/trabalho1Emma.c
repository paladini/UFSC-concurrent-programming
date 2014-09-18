#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#define VECSIZE 16
#define NTHREADS 4

int valoresA[VECSIZE], valoresB[VECSIZE];
int separacao;
int sum = 0;
pthread_mutex_t mutex;

int calcularFinal(int threadAtual, int inicio){
	if(threadAtual == NTHREADS - 1){
		int maiorFinalPossivel = NTHREADS * separacao;
		if(maiorFinalPossivel < VECSIZE){
			return VECSIZE;
		}
	}
	return inicio + separacao;
}

void *calculo(void *arg){
	long int classificacaoThread = (long int) arg;
	int inicio = (classificacaoThread * separacao);
	int final = calcularFinal(classificacaoThread, inicio);
	if(final <= VECSIZE){
		int i, somaParcial = 0;
		for(i = inicio; i < final; i++){
			somaParcial += valoresA[i] * valoresB[i];
		}
		printf("Soma parcial da Thread[%d].. entre %d e %d eh igual a = %d\n", classificacaoThread, inicio, (final-1) ,somaParcial);
		pthread_mutex_lock(&mutex);
		sum += somaParcial;
		pthread_mutex_unlock(&mutex);
		pthread_exit(NULL);
	}
}

void criarEpopularVetores(){
	int i;
	for(i = 0; i < VECSIZE; i++){
		valoresA[i] = rand()%10;
		valoresB[i] = rand()%10;
	}
	separacao = VECSIZE/NTHREADS;
}

void aguardarTerminoDeThreads(pthread_t thread[]){
	int i;
	for(i = 0; i < NTHREADS; i++){
		pthread_join(thread[i], NULL);
	}
}

void printarVetores(){
	int i;
	printf("Valores de A = ");
	for(i = 0; i < VECSIZE; i++){
		if(i == (VECSIZE - 1)){
			printf("%d", valoresA[i]);
		}else{
			printf("%d, ", valoresA[i]);
		}
	}
	printf("\n");
	printf("Valores de B = ");
	for(i = 0; i < VECSIZE; i++){
		if(i == (VECSIZE - 1)){
			printf("%d", valoresB[i]);
		}else{
			printf("%d, ", valoresB[i]);
		}
	}
	printf("\n");
}

int main(){
	int *numeroThread, i;
	srand(time(NULL));
	pthread_mutex_init(&mutex, NULL); 
	pthread_t vetorThreads[NTHREADS];

	criarEpopularVetores();
	printarVetores();

	if((VECSIZE >= NTHREADS) || separacao != 0){
		for(i = 0; i < NTHREADS; i++){
			long int numeroThread = i;
			pthread_create(&vetorThreads[i], NULL, calculo, (void *)numeroThread);
		}
	} else {
		printf("O número de threads é maior que o vetor!");
		return -1;
	}
	pthread_mutex_destroy(&mutex);
	aguardarTerminoDeThreads(vetorThreads);
	printf("Soma total = %d\n", sum);
	pthread_exit(NULL);
}
