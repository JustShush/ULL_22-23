#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 25

typedef struct biblioteca
{
	int codlivro;
	char titulo[30];
	int estante;
	char local;
} BIBLIOTECA;

// funcoes auxiliares
char	*ft_strcpy(char *dest, char *src)
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

char	fNum(const char *mensagem)
{
	printf("\n%s", mensagem);
	char x;
	scanf("%c", &x);
	// Limpar o buffer
	getc(stdin);
	return (x);
}

// Recolher um valor inteiro
int	RecolhaInt(const char *mensagem)
{
	printf("\n%s", mensagem);
	int x;
	scanf("%i", &x);
	// Limpar o buffer
	getc(stdin);
	return (x);
}

void	printl(int j)
{
	while (j >= 0)
	{
		printf("-");
		j--;
	}
	printf("\n");
}
// fim das funcoes auxiliares

// Mostrar os dados de uma BIBLIOTECA
void	showLivro(BIBLIOTECA livro)
{
	printf("Codigo: %i\nNome: %s\nEstante do livro: %d\nPrateleira do livro:
			%c\n\n", livro.codlivro, livro.titulo, livro.estante, livro.local);
	return ;
}

void	lisLivro(BIBLIOTECA *livro, int n)
{
	printf("n tem valor = %d\n", n);
	int i, x;
	x = 0;
	for (i = -1; i < n; i++)
	{
		printf("Codigo: %i\nNome: %s\nNumero da estante:
				%d\nLetra da preteleira: %c\n", livro[x].codlivro,
				livro[x].titulo, livro[x].estante, livro[x].local);
		x++;
	}
}

// Apagar uma BIBLIOTECA
void	delLivro(BIBLIOTECA *livro, int *i, int *n)
{
	int j;
	for (j = (*n); j < (*i); j++)
	{
		ft_strcpy(livro[j].titulo, livro[j + 1].titulo);
		livro[j].codlivro = livro[j + 1].codlivro;
		livro[j].estante = livro[j + 1].estante;
		livro[j].local = livro[j + 1].local;
	}

	(*i)--;

	if ((*n) > (*i))
		(*n) = (*i);
	if ((*n) >= 0)
		showLivro(livro[(*n)]);
	return ;
}

// Alterar uma BIBLIOTECA
void	modLivro(BIBLIOTECA *livro, int n)
{
	livro[n].codlivro = RecolhaInt("Escreva o novo codigo da disciplina: ");

	printf("\nEscreva o novo nome da disciplina: ");
	scanf("%s", livro[n].titulo);
	getc(stdin);

	livro[n].estante = RecolhaInt("Escreva a estante do livro: ");
	livro[n].local = fNum("Escreva a prateleira do livro: ");

	printf("livro alterada!\n");
	return ;
}

// Adicionar uma BIBLIOTECA
void	addLivro(BIBLIOTECA *livro, int *i)
{
	if ((*i) == SIZE)
	{
		printf("Numero maximo de livros atingido!!\n\n");
		return ;
	}
	(*i)++;
	// Recolha do numero do novo aluno
	livro[(*i)].codlivro = RecolhaInt("Escreva o codigo do novo livro: ");
	// Recolha do nome do novo aluno
	printf("\nEscreva o nome do novo livro: ");
	scanf("%s", livro[(*i)].titulo);
	getc(stdin);

	livro[(*i)].estante = RecolhaInt("Escreva a estante do livro: ");
	livro[(*i)].local = fNum("Escreva a prateleira do livro: ");

	printf("livro inserida!\n");
	return ;
}

// Importar de ficheiro
void	Import(BIBLIOTECA *livro, int *i, int *n)
{
	int li = -1;

	int num, estante;
	char local;
	char nom[30];

	FILE *f = fopen("f11104222.txt", "r");
	if (!f)
		printf("Erro ao abrir o ficheiro\n");
	else
	{
		(*i) = -1;
		(*n) = -1;

		while ((fscanf(f, "%i %s %d %c\n", &num, nom, &estante, &local) != EOF)
			&& (li < SIZE))
		{
			li++;
			livro[li].codlivro = num;
			ft_strcpy(livro[li].titulo, nom);
			livro[li].estante = estante;
			//ft_strcpy(livro[li].local, local);
			livro[li].local = local;
		}
		(*i) = li;
		if (li >= 0)
		{
			(*n) = 0;
			showLivro(livro[0]);
		}
		fclose(f);
	}
	return ;
}

// Exportar para um ficheiro
void	Export(BIBLIOTECA *livro, int i)
{
	int n;
	FILE *f = fopen("f11104222.txt", "w");

	if (!f)
		printf("Erro na criacao do ficheiro\n");
	else
	{
		for (n = 0; n <= i; n++)
			fprintf(f, "%i %s %d %c\n", livro[n].codlivro, livro[n].titulo,
					livro[n].estante, livro[n].local);
		fclose(f);
	}
	return ;
}

void	menu(void)
{
	printl(42);
	printf("|			Menu  		\n");
	printf("|0 - Inserir novo livro.\n|1 - Remover um livro.\n|2
			- Alterar dados do livro.\n|3 - Listar todos os livros.\n|4
			- Mostrar primeiro livro.\n|5 - Mostrar proximo livro.\n|6
			- Mostrar livro anterior.\n|7 - Mostrar ultimo livro.\n|8
			- Exportar para ficheiro.\n|9 - Importar de ficheiro.\n|f
			- Sair do progrma.\n");
	printl(42);
}

int	main(void)
{
	BIBLIOTECA Livro[SIZE];

	int i = -1;
	int n = -1;

	int fim = 1;

	do
	{
		menu();
		char op = fNum("Digite uma opcao: ");

		switch (op)
		{
		case 'f':
			printf("Fim do programa!\n");
			return (0);
			break ;
		case 'q':
			fim = 0;
			break ;
		case '0': // Inserir um livro
			addLivro(Livro, &i);
			n = i;
			break ;
		case '1': // Apagar o elemento n
			if (i >= 0)
				delLivro(Livro, &i, &n);
			else
				printf("Nao ha livros inseridas\n");
			break ;
		case '2': // Modificar o elemento n
			if (i >= 0)
				modLivro(Livro, n);
			else
				printf("Nao ha livros inseridas\n");
			break ;
		case '3': // listar todos os livros
			lisLivro(Livro, i);
			//MostrarAluno()
			break ;
		case '4': // ir para o primeiro elemento
			if (i >= 0)
			{
				n = 0;
				showLivro(Livro[n]);
			}
			else
				printf("Nao ha livros inseridas\n");
			break ;
		case '5': // ir para o elemento seguinte
			if (i >= 0)
			{
				if (n < i)
				{
					n++;
					showLivro(Livro[n]);
				}
				else
					printf("Nao pode passar para a frente do ultimo livro\n");
			}
			else
				printf("Nao ha livros inseridas\n");
			break ;
		case '6': // ir para o elemento enterior
			if (i >= 0)
			{
				if (!(n > 0))
					printf("Nao pode passar para tras do primeiro livro\n");
				n--;
				showLivro(Livro[n]);
			}
			else
				printf("Nao ha livros inseridas\n");
			break ;
		case '7': // ir para o ultimo
			if (i >= 0)
			{
				n = i;
				showLivro(Livro[n]);
			}
			else
				printf("Nao ha livros inseridas\n");
			break ;
		case '8': // Exportar para ficheiro
			if (i >= 0)
				Export(Livro, i);
			else
				printf("Nao ha livros inseridas\n");
			break ;
		case '9': // Importar de ficheiro
			Import(Livro, &i, &n);
			break ;

		default:
			printf("Escolha uma opcao do menu\n");
			break ;
		}

		if (fim != 1)
			printf("Fim do programa!");

	} while (fim == 1);

	return (0);
}
