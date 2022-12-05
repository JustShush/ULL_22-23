#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8

struct produto
{
	char nome[20];
	int qtd;
	float valor;
};

typedef struct produto PRODUTO;
typedef PRODUTO *PPRODUTO;

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

int ft_strcmp(char *s1, char *s2)
{
	unsigned int i;
	unsigned char a;
	unsigned char b;

	i = 0;
	a = s1[i];
	b = s2[i];
	while (s1[i] != '\0' && (s1[i] == s2[i]))
	{
		i++;
		a = s1[i];
		b = s2[i];
	}
	return (a - b);
}

void ft_printl()
{
	printf("------------------------------------------------\n");
}

void ler_dados(PPRODUTO prods)
{
	FILE *fp = fopen("produtos2.txt", "r");
	int i = 0;
	if (!fp)
		printf("Nao foi possivel abrir o ficheiro.\n");
	else
	{
		while (fscanf(fp, "%s%d%f", prods[i].nome, &prods[i].qtd, &prods[i].valor) != EOF)
			i++;
		fclose(fp);
	}
}

void resultados(PPRODUTO prods)
{
	int soma = 0;
	int n = 0;
	float total = 0.0;
	float totval = 0.0;
	int i;
	ft_printl();
	printf("|		Lista de produtos		\n");
	for (i = 0; i < SIZE; i++)
		if (ft_strcmp(prods[i].nome, "") != 0)
		{
			n++;
			soma += prods[i].qtd;
			totval += prods[i].valor;
			total += prods[i].qtd * prods[i].valor;
			printf("|Produto: %s, qtd: %d, valor: %f€\n", prods[i].nome, prods[i].qtd, prods[i].valor);
		}
	if (n > 0)
	{
		ft_printl();
		printf("|Total dos produtos: %d€\n", soma);
		printf("|Media do valor: %f€\n", totval / n);
		printf("|Total dos valores: %f€\n", total);
		ft_printl();
	}
	else
		printf("O ficheiro nao tem dados.(AKA esta vaziu)\n");
}

int main()
{
	PRODUTO prd[SIZE];
	int i;
	for (i = 0; i < SIZE; i++)
	{
		ft_strcpy(prd[i].nome, "");
		prd[i].qtd = 0;
		prd[i].valor = 0.0;
	}

	ler_dados(prd);
	resultados(prd);

	return 0;
}
