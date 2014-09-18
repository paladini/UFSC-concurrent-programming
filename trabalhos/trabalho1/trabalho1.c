#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#define VECSIZE 16
#define NTHREADS 4

pthread_mutex_t mutex;
int valoresA[VECSIZE], valoresB[VECSIZE], separacao = VECSIZE / NTHREADS, indiceFim;
int indiceInicio = 0, sum = 0, i = 0;

void *calculo(void *arg){
	
	pthread_mutex_lock(&mutex);
	long int numeroThread = (long int)arg;
	int indiceFim = indiceInicio + separacao;
	if(indiceFim <= VECSIZE){

		int somaParcial = 0;
		for(indiceInicio; indiceInicio < indiceFim; indiceInicio++){
			somaParcial += valoresA[indiceInicio] * valoresB[indiceInicio];
		}
		indiceInicio = indiceFim;
		printf("Thread %ld calculou de %d a %d: produto escalar parcial = %d\n", numeroThread, indiceFim - separacao, indiceFim - 1, somaParcial);

		sum += somaParcial;
	}

	pthread_mutex_unlock(&mutex);
}

void criarEPopularVetores(){
	for(i = 0; i < VECSIZE; i++){
		valoresA[i] = rand()%10;
		valoresB[i] = rand()%10;
	}
}

void aguardarTerminoDeThreads(pthread_t thread[]){
	for(i = 0; i < NTHREADS; i++){
		pthread_join(thread[i], NULL);
	}
}

void imprimirVetores(){
	printf("\t\tA = ");
	for(i = 0; i < VECSIZE; i++){
		printf("%d,", valoresA[i]);
	}
	printf("\n");

	printf("\t\tB = ");
	for(i = 0; i < VECSIZE; i++){
		printf("%d,", valoresB[i]);
	}
	printf("\n");
}

int main(){

	srand(time(NULL));
	pthread_mutex_init(&mutex, NULL);
	
	criarEPopularVetores();
	imprimirVetores();

	pthread_t vetorThreads[NTHREADS];
	if(!(VECSIZE < NTHREADS)){
		for(i = 0; i < NTHREADS; i++){
			long int numeroThread = (long int)i;
			pthread_create(&vetorThreads[i], NULL, calculo, (void*)numeroThread);

		}
	} else {
		printf("O número de threads é maior que o vetor!");
		return -1;
	}
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);

	aguardarTerminoDeThreads(vetorThreads);
	printf("Produto escalar = %d\n", sum);
	return 0;
}
