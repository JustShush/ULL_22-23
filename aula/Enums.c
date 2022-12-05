#include <stdio.h>
#include <locale.h>
#include <strings.h>

enum Estado {
	Recolha = 0,
	Mostra = 1
};

int RecolhaInt(const char* mensagem)
{
	int x;
	printf("\n%s",mensagem);
	scanf("%i", &x);
	//limpar o buffer por causa do ultimo getchar()
	getc(stdin);
	return x;
}

void DisplayEstado( enum Estado est)
{
	switch(est) {
		case Recolha:
			printf("Em recolha.\n");
			break;
		case Mostra:
			printf("Em exibicao.\n");
			break;
	}
}

int main() {
	
	setlocale(LC_ALL,"Portuguese");
	
	enum Estado est;
	est = Recolha;
	int i;
	int v[5];
	DisplayEstado(est);
	for (i=0; i< 5 ; i++)
	{
		printf("v[%i]",i);
		v[i] = RecolhaInt("Digite o valor:");
	}
	est = Mostra;
	DisplayEstado(est);
	
	for (i=0; i< 5;i++)
		printf("v[%i]: %i\n",i,v[i]);
	
	return 0;
	
}
