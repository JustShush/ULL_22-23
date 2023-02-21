// nota final 20v
#include <stdio.h>
#include <string.h>

#define SIZE 10

struct disciplina
{
	int coddisciplina;
	char nomdisciplina[25];
	int notmax;
	int notmin;
};

typedef struct disciplina DISCIPLINA;

// funcoes auxiliares
char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char fNum(const char *mensagem)
{
	printf("\n%s", mensagem);
	char x;
	scanf("%c", &x);
	// Limpar o buffer
	getc(stdin);
	return x;
}

// Recolher um valor inteiro
int RecolhaInt(const char *mensagem)
{
	printf("\n%s", mensagem);
	int x;
	scanf("%i", &x);
	// Limpar o buffer
	getc(stdin);
	return x;
}

void printl(int j)
{
	while (j >= 0)
	{
		printf("-");
		j--;
	}
	printf("\n");
}
// fim das funcoes auxiliares

// Mostrar os dados de uma disciplina
void showDis(DISCIPLINA disciplina)
{
	printf("Codigo: %i\nNome: %s\nNota max: %d\nNota min: %d\n\n", disciplina.coddisciplina, disciplina.nomdisciplina, disciplina.notmax, disciplina.notmin);
	return;
}

// Apagar uma disciplina
void delDis(DISCIPLINA *disciplina, int *i, int *n)
{

	int j;
	for (j = (*n); j < (*i); j++)
	{

		ft_strcpy(disciplina[j].nomdisciplina, disciplina[j + 1].nomdisciplina);
		disciplina[j].coddisciplina = disciplina[j + 1].coddisciplina;
		disciplina[j].notmax = disciplina[j + 1].notmax;
		disciplina[j].notmin = disciplina[j + 1].notmin;
	}

	(*i)--;

	if ((*n) > (*i))
		(*n) = (*i);
	if ((*n) >= 0)
		showDis(disciplina[(*n)]);
	return;
}

// Alterar uma disciplina
void modDis(DISCIPLINA *disciplina, int n)
{

	disciplina[n].coddisciplina = RecolhaInt("Escreva o novo codigo da disciplina: ");

	printf("\nEscreva o novo nome da disciplina: ");
	scanf("%s", disciplina[n].nomdisciplina);
	getc(stdin);

	disciplina[n].notmax = RecolhaInt("Escreva a nota maxima da disciplina: ");
	disciplina[n].notmin = RecolhaInt("Escreva a nota minima da disciplina: ");

	printf("Disciplina alterada!\n");
	return;
}

// Adicionar uma disciplina
void addDis(DISCIPLINA *disciplina, int *i)
{

	if ((*i) == SIZE)
	{
		printf("Numero maximo de disciplinas atingido!!\n\n");
		return;
	}
	(*i)++;
	// Recolha do n�mero do novo aluno
	disciplina[(*i)].coddisciplina = RecolhaInt("Escreva o codigo da nova disciplina: ");
	// Recolha do nome do novo aluno
	printf("\nEscreva o nome da nova disciplina: ");
	scanf("%s", disciplina[(*i)].nomdisciplina);
	getc(stdin);

	disciplina[(*i)].notmax = RecolhaInt("Escreva a nota maxima da disciplina: ");
	disciplina[(*i)].notmin = RecolhaInt("Escreva a nota minima da disciplina: ");

	printf("Disciplina inserida!\n");
	return;
}

// Importar de ficheiro
void Import(DISCIPLINA *disciplina, int *i, int *n)
{

	int li = -1;

	int num, notmax, notmin;
	char nom[80];

	FILE *f = fopen("disciplinas.txt", "r");
	if (!f)
		printf("Erro ao abrir o ficheiro\n");
	else
	{
		(*i) = -1;
		(*n) = -1;

		while ((fscanf(f, "%i %s %d %d\n", &num, nom, &notmax, &notmin) != EOF) && (li < SIZE))
		{
			li++;
			disciplina[li].coddisciplina = num;
			ft_strcpy(disciplina[li].nomdisciplina, nom);
			disciplina[li].notmax = notmax;
			disciplina[li].notmin = notmin;
		}
		(*i) = li;
		if (li >= 0)
		{
			(*n) = 0;
			showDis(disciplina[0]);
		}
		fclose(f);
	}
	return;
}

// Exportar para um ficheiro
void Export(DISCIPLINA *disciplina, int i)
{

	int n;
	FILE *f = fopen("disciplinas.txt", "w");

	if (!f)
		printf("Erro na criacao do ficheiro\n");
	else
	{
		for (n = 0; n <= i; n++)
			fprintf(f, "%i %s %d %d\n", disciplina[n].coddisciplina, disciplina[n].nomdisciplina, disciplina[n].notmax, disciplina[n].notmin);
		fclose(f);
	}
	return;
}

void menu()
{
	printl(42);
	printf("|		  Menu  		\n");
	printf("|0 - Sair do programa.\n|1 - Adicionar uma disciplina.\n|2 - Alterar uma disciplina.\n|3 - Apagar uma disciplina.\n|4 - Ir para a primeira disciplina.\n|5 - Ir para a disciplina anterior.\n|6 - Ir para a disciplina seguinte.\n|7 - Ir para a ultima disciplina.\n|8 - Exporar disciplinas para ficheiro.\n|9 - Importar disciplinas de ficheiro.\n");
	printl(42);
}

int main()
{

	DISCIPLINA dis[SIZE];

	int i = -1;
	int n = -1;

	int fim = 1;

	do
	{
		menu();
		char op = fNum("Digite uma opcao: ");

		switch (op)
		{
		/* case 'f':
			printf("Fim do programa!\n");
			return 0;
			break; */
		case '0':
			fim = 0;
			break;
		case '1': // Inserir um aluno
			addDis(dis, &i);
			n = i;
			break;
		case '2': // Modificar o elemento n
			if (i >= 0)
				modDis(dis, n);
			else
				printf("Nao ha dissiplinas inseridas\n");
			break;
		case '3': // Apagar o elemento n
			if (i >= 0)
				delDis(dis, &i, &n);
			else
				printf("Nao ha dissiplinas inseridas\n");
			break;
		case '4': // ir para o primeiro elemento
			if (i >= 0)
			{
				n = 0;
				showDis(dis[n]);
			}
			else
				printf("Nao ha dissiplinas inseridas\n");
			break;
		case '5': // ir para o elemento anterior
			if (i >= 0)
			{
				if (n > 0)
				{
					n--;
					showDis(dis[n]);
				}
				else
					printf("Nao pode passar para tras da primeira disciplina\n");
			}
			else
				printf("Nao ha disciplinas inseridas\n");
			break;
		case '6': // ir para o elemento seguinte
			if (i >= 0)
			{
				if (n < i)
				{
					n++;
					showDis(dis[n]);
				}
				else
					printf("Nao pode passar para a frente do �ltimo\n");
			}
			else
				printf("Nao ha disciplinas inseridas\n");
			break;
		case '7': // ir para o ultimo
			if (i >= 0)
			{
				n = i;
				showDis(dis[n]);
			}
			else
				printf("Nao ha disciplinas inseridas\n");
			break;
		case '8': // Exportar para ficheiro
			if (i >= 0)
				Export(dis, i);
			else
				printf("Nao ha disciplinas inseridas\n");
			break;
		case '9': // Importar de ficheiro
			Import(dis, &i, &n);
			break;

		default:
			printf("Escolha uma opcao do menu\n");
			break;
		}

		if (fim != 1)
			printf("Fim do programa!");

	} while (fim == 1);

	return 0;
}