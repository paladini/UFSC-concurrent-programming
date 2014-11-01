#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int isDivisor(int numero, int divisorPotencial) {
	if(numero % divisorPotencial == 0) {
			return divisorPotencial;
	}
	return 0;
}

int calculaSomaDosDivisores(int i) {
	int j, soma = i;
	for(j = (int) i / 2; j > 0; j--){
			soma += isDivisor(i, j);
	}
	return soma;
}

int main(int argc, char **argv) {
	int minimo = atoi(argv[1]);
	int maximo = atoi(argv[2]);
	int threads = atoi(argv[3]);
	
	int i, j;
	int intervalo = maximo-minimo;
	double *fracoes = (double*) malloc ((intervalo + 1) * sizeof(double));
	omp_set_num_threads(threads);

	#pragma omp parallel
	{
		#pragma omp for schedule(dynamic, intervalo/threads)
		for (i = 0; i <= intervalo; i++) {
			int somaDosDivisores = calculaSomaDosDivisores(minimo + i);
			double fracaoMutual = (double)somaDosDivisores / (minimo + i);
			fracoes[i] = fracaoMutual;
		}
	}
	
	for(i = 0; i <= intervalo; i++){
		#pragma omp parallel
		{
			#pragma omp for schedule(dynamic, intervalo/threads)
			for (j = i+1; j <= intervalo; j++) {
				if(fracoes[i] == fracoes[j]) {
					printf("Os numeros %d e %d são mutuamente amigos.\n", (minimo + i), (minimo + j));
				}
			}
		}
	}
	
	free(fracoes);
	return 0;
}
