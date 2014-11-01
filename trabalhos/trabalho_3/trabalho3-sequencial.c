#include <stdio.h>
#include <stdlib.h>

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

	int i, j, somaDosDivisores, intervalo = maximo-minimo;
	double fracaoMutual;
	double *fracoes = (double*) malloc (intervalo * sizeof(double));

	for (i = 0; i <= intervalo; i++) {
		somaDosDivisores = calculaSomaDosDivisores(minimo + i);
		fracaoMutual = (double)somaDosDivisores / (minimo + i);
		fracoes[i] = fracaoMutual;
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

