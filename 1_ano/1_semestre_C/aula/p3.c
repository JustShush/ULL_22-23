#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int recolheInt (const char* mensagem) {
	int x;
	printf("\n%s", mensagem);
	scanf("%i", &x);
	// limpar o buffer por causa do ultimo getchar()
	getc(stdin);
	return (x);
}

long fatorial(int n) {
	int j;
	long k = 1;
	for(j = n; j > 1; j--) {
		k *= j;  // k = k * j;
		
	}
	return(k);
}

long permutacoes(int n) {
	return fatorial(n);
}

long arranjos(int n, int p) {
	long arr;
	arr = fatorial(n) / fatorial(n - p);
	
	return (arr);
}

long combinacoes(int n, int p) {
	long comb;
	comb = fatorial(n) / (fatorial(p) * fatorial(n -p));
	
	return (comb);
}

int main(void) {
	setlocale(LC_ALL, "Portuguese");

	char op;
	int n,p;
	do {
		printf("Escolha uma op��o:\n\n");
		printf("1 - Permuta��es\n");
		printf("2 - Arranjos\n");
		printf("3 - Combina��es\n");
		printf("f - Fim\n");
		printf("Digite uma op��o: ");
		op = getchar();
		switch (op) {
			case '1':
				// pedir o valor de n e escrever o valor da fun��o permuta��es
				n = recolheInt("Digite o valor de n: ");
				printf("As permuta��es de %i s�o %i\n", n, permutacoes(n));
				break;
			case '2':
				// pedir os valores de n e p e escrever o valor da fun��o arranjos
				n = recolheInt("Digite o valor de n: ");
				p = recolheInt("Digite o valor de p: ");
				printf("Os arranjos de %i, %i a %i s�o %i\n", n, p, p, arranjos(n,p));
				break;
			case '3':
				// pedir os valores de n e p e escrever o valor da fun��o combina�oes
				n = recolheInt("Digite o valor de n: ");
				p = recolheInt("Digite o valor de p: ");
				printf("As combina��es de %i, %i a %i s�o %i\n", n, p, p, combinacoes(n,p));
				break;
			case 'f':
			case 'F':
				printf("Fim do programa!\n");
				return 0;
		}
	} while (op != 'f' || op != 'F');
	
	return 0;
	
}
