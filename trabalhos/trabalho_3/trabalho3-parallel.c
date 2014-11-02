#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int calculaSomaDosDivisores(int i) {
	int j, soma = i;
	for(j = (int) i / 2; j > 0; j--){
		if(i % j == 0) {
			soma += j;
		}
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
		#pragma omp for schedule(static)
		for (i = minimo; i <= maximo; i++) {
			double fracaoMutual = (double)calculaSomaDosDivisores(i) / i;
			fracoes[i - minimo] = fracaoMutual;
		}
	}
	
	for(i = 0; i <= intervalo; i++){
		#pragma omp parallel
		{
			#pragma omp for schedule(static)
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
