#include <stdio.h>
#include <locale.h>
#include <strings.h>

enum semana
{
	domingo = 0,
	segunda = 1,
	terca = 2,
	quarta = 3,
	quinta = 4,
	sexta = 5,
	sabado = 6
};

struct dia
{
	int d;
	char descricao[20];
};

int RecolhaInt(const char *mensagem)
{
	int x;
	printf("\n%s", mensagem);
	scanf("%i", &x);
	// limpar o buffer por causa do �ltimo getchar()
	getc(stdin);
	return x;
}

int main()
{

	setlocale(LC_ALL, "Portuguese");

	struct dia dias[7];
	int i, j;

	for (i = 0; i < 7; i++)
	{
		j = RecolhaInt("Digite o n�mero do dia da semana: ");
		printf("Digite a descri��o do dia: ");
		scanf("%s", dias[i].descricao);
		switch (j)
		{
		case 0:
			dias[i].d = domingo;
			break;
		case 1:
			dias[i].d = segunda;
			break;
		case 2:
			dias[i].d = terca;
			break;
		case 3:
			dias[i].d = quarta;
			break;
		case 4:
			dias[i].d = quinta;
			break;
		case 5:
			dias[i].d = sexta;
			break;
		case 6:
			dias[i].d = sabado;
			break;
		default:
			dias[i].d = domingo;
			break;
		}
	}

	printf("\n\n");

	for (i = 0; i < 7; i++)
	{
		printf("Dia %i: %s\n", dias[i].d, dias[i].descricao);
	}

	return 0;
}
