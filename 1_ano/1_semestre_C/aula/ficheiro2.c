#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[]) {

	setlocale(LC_ALL,"Portuguese");
	char s[80];

	if (argc < 3) {
		printf("Utilização: %s <fich orig> <fich dest>\n", argv[0]);
		return 0;
	}

	FILE *f = fopen(argv[1], "r");
	FILE *g = fopen(argv[2], "W");
	while (fscanf(f, "%s", s) != EOF) {
		printf("%s\n", s);
		fprintf(g, "%s\n", s);
	}

	printf("\nCópia executada!\n");
	
	return 0;
}