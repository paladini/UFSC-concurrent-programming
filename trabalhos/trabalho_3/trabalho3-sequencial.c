#include <stdio.h>
#include <stdlib.h>

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

	int i, j, somaDosDivisores, intervalo = maximo-minimo;
	double fracaoMutual;
	double *fracoes = (double*) malloc ((intervalo + 1) * sizeof(double));

	for (i = minimo; i <= maximo; i++) {
		double fracaoMutual = (double)calculaSomaDosDivisores(i) / i;
		fracoes[i - minimo] = fracaoMutual;
	}

	for(i = 0; i <= intervalo; i++){
		for (j = i+1; j <= intervalo; j++) {
	    	if(fracoes[i] == fracoes[j]) {
        	    printf("Os numeros %d e %d são mutuamente amigos.\n", (minimo + i), (minimo + j));
    		}
		}
	}

	free(fracoes);
	return 0;
}

