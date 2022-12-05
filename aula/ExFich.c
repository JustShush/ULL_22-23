#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

char str[10][80];
FILE *f;
int ix;

// Ler do teclado um valor e grav�-lo no vetor str[ix][80]
void RecolheString(const char* mensagem)
{
	if (ix < 10) {
		printf("\n%s", mensagem);
		//scanf("%s",str[ix++]);
		scanf("%s", str[ix]);
		ix++;
		//limpar o buffer
		getc(stdin);
	}
	else
		printf("Limite de strings atingido!\n");
}

// Gravar as ix strings no ficheiro
int gravarStr() {
	f = fopen("strings.txt", "w");
	if ( f == NULL) {
		return (-1);
	}
	int j;
	for (j = 0; j < ix; j++) {
		fprintf("%s\n", str[j]);
	}
	fclose(f);
	return (0);
}

// ler as strings do ficheiro e grav�-las no vetor str[][80]
int LerStrings()
{
	ix = 0;
	char s[80];
	f = fopen("strings.txt", "r");
	if (f == NULL) {
		return -1;
	}
	
	while (fscanf(f, "%s", s) != EOF && ix < 10) {
		//strcpy(str[ix++], s);
		strcpy(str[ix], s);
		ix++;
	}
	
	fclose(f);
	return 0;
}

// Mostrar as strings
void mostrarStr() {
	int i;
	for (i = 0; i < ix; i++) {
		printf("%s\n", str[ix]);
	}
}


int fFim (const char* msg) {
	int x;
	printf("%s", msg);
	scanf("%i", &x);
	// limpar o buffer por causa do ultimo getchar()
	getc(stdin);
	return (x);
}

void menu() {
	printf("Escolha uma opção: \n\n0 - Sair do programa.\n1 - Recolher uma string.\n2 - Ler strings de ficheiro.\n3 - Escrever as strings em ficheiro.\n4 - Listar as strings.\n");
}

int main() {
	setlocale(LC_ALL,"Portuguese");

	FILE *f;

	f = fopen("nomes.txt", "r");
	
	//menu para escolha de op��es
	// 0 - Sair
	// 1 - Recolher uma string
	// 2 - Ler strings de ficheiro
	// 3 - Escrever as strings em ficheiro
	// 4 - Listar as strings
	
	char op;
	int Fim = 1;

	do {

		menu();

		op = getchar();

		switch (op) {
			case 'f':
			case 'F':
			case '0':
				printf("Fim do programa!");
				return 0;
			case '1':
			// 1 - Recolher uma string
			
				break;
			case '2':
			// 2 - Ler strings de ficheiro

				break;
			case '3':
			// 3 - Escrever as strings em ficheiro

				break;
			case '4':
			// 4 - Listar as strings
				mostrarStr();
				break;
		}

		Fim = fFim("Continuar(1) ou acabar(0): ");

	} while (Fim != 0);

	return 0;
}
