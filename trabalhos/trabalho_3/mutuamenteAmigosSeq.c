#include <stdio.h>
#include <stdlib.h>

/** Método que realiza a soma de todos os divisores de um número dado. 
* Recebe um número que se será o que número que terá a soma de todos os seus divisores. 
* Um laço é realizado para checar todos os possíveis divisores desse número (a partir de i/2), onde
* o teste de possível divisor é i % j == 0. Caso o número da iteração seja um divisor do número dado,
* é adicionado no resultado da variável "soma", que será retornada no fim do método.
*
* @param [int] i O número que será testado em busca de divisores. Todos os divisores desse número serão somados e este será o valor retornado do método. 
* @return A soma de todos os divisores do número dado.
*/
int calculaSomaDosDivisores(int i) {
	int j, soma = i;
	for(j = (int) i / 2; j > 0; j--){
		if(i % j == 0) {
			soma += j;
		}
	}
	return soma;
}

/** Método principal de um programa que resolve o problema dos números mutuamente amigos.
*
* Recebe dois argumentos: "minimo" e "maximo" ("./meuPrograma <minimo> <maximo>"), que é o 
* intervalo que os números mutuamente amigos serão calculados por esse programa. 
*
* O programa tenta alocar memória para um array de double's e caso não consiga, encerra o programa
* com uma mensagem de erro e o código "-1". Caso seja possível alocar a memória para esse array,
* o programa entra em seu ciclo de execução normal. A execução é divida em duas etapas:
*
* 	1) Calcula as "frações mutuais" (soma de todos os divisores dividido pelo próprio número) de 
*      todos os números do intervalo. Cada uma das frações é armazena no array de double's "fracoes".
*
*	2) Após realizar todos os cálculos é necessário checar quais números são de fato mutuamente amigos.
* 	   Para isso são utilizados dois laços que percorrem o vetor em busca de números que tem a mesma "fracaoMutual".
*
* Após essas etapas, a memória ocupada pelo array de double's "fracoes" é liberada e o programa é finalizado com o código "0" (sem erro).
*
*/
int main(int argc, char **argv) {

	int minimo = atoi(argv[1]);
	int maximo = atoi(argv[2]);

	int i, j, intervalo = maximo-minimo;
	double fracaoMutual;
	double *fracoes = (double*) malloc ((intervalo + 1) * sizeof(double));

	if(fracoes != NULL) {
		for (i = minimo; i <= maximo; i++) {
			fracaoMutual = (double)calculaSomaDosDivisores(i) / i;
			fracoes[i - minimo] = fracaoMutual;
		}

		for(i = 0; i <= intervalo; i++){
			for (j = i+1; j <= intervalo; j++) {
		    	if(fracoes[i] == fracoes[j]) {
	        	    //printf("Os numeros %d e %d são mutuamente amigos.\n", (minimo + i), (minimo + j));
	    		}
			}
		}

		free(fracoes);
		return 0;
	}

	printf("Não foi possível alocar memória.");
	return -1;
}

