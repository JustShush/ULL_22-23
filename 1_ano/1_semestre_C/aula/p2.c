#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	
	int i = 5;
	
	if (i > 3) {
		printf("O valor de %i � maior que 3.\n", i);
	} else {
		printf("O valor de %i � manor que 3.1n", i);
	}
	
	switch (i) {
		case 0:
			printf("O valor � zero!\n");
			break;
		case 1:
		case 2:
			printf("O valor � 1 ou 2.\n");
			break;
		case 3:
		case 4:
			printf("O valor � 3 ou 4.\n");
			break;
		case 5:
			printf("O valor � 5.\n");
			break;
		default:
			printf("O valor � maior que 5!\n");
			break;		
			
	}

	int j;
	for (j = 0; j <= 5; j++) {
		printf("J: %i\n", j);
	}
	
	return 0;
}
