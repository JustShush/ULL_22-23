#include <stdio.h>
#include <stdlib.h>

void adicao() {
	int n1, n2, soma;
	printf("Escreva o primeio numero da soma: ");
	scanf("\n%d", &n1);
	printf("Escolha o segundo numero  da soma: ");
	scanf("\n%d", &n2);
	soma = n1 + n2;
	printf("%d + %d = %d", n1, n2, soma);
}

int fFim(const char* msg) {
	int x;
	printf("%s", msg);
	scanf("%i", x);
	getc(stdin);
	return (x);
}

void menu() {
	printf("Calculadora basica!\n\n");
	printf("Escolha uma opcao:\n1 - Adicao\n2 - Subtracao\n3 - Multiplicacao\n4 - Divisao\n");
}

int main() {

	char op;
	int Fim = 1;

	do {

		menu();

		op = getchar();

		switch (op) {
		case 'f':
		case 'F':
			return 0;
			break;
		case '1':
			adicao();
			break;
		case '2':
			printf("fazes tu esta parte agora hahaha");
			break;
		case '3':
			printf("fazes tu esta parte agora hahaha");
			break;
		case '4':
			printf("fazes tu esta parte agora hahaha");
			break;
		default:
			break;
		}

		Fim = fFim("\nContinuar(1) ou acabar(0)?: ");

	} while (Fim != 0);

	return 0;
}