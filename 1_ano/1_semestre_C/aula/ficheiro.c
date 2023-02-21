#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(void) {

	setlocale(LC_ALL,"Portuguese");
	FILE *f;
	char s[20];

	printf("Leitura de um ficheiro de texto\n\n");

	f = fopen("nomes.txt", "r");
	while (fscanf(f, "%s", s) != EOF) {
		printf("%s\n", s);
	}

	return 0;
}