// nota final 18.5v
#include <stdio.h>
#include <stdlib.h>

// O valor de 2 elevado a "n"
int f3(int n)
{

	if (!(n > 0))
	{
		printf("!!O NUMERO TEM DE SER MAIOR QUE ZERO!!");
		return;
	}

	if (n == 1)
		return 2;

	return 2 * f3(n - 1);
}

// O "n" numero impar, com n > 0
void f2(int n)
{
	int i, c;

	if (!(n > 0))
	{
		printf("!!O NUMERO TEM DE SER MAIOR QUE ZERO!!");
		return;
	}

	i = 0;
	c = 0;
	while (i < n)
	{
		if (!(i % 2 == 0)) // ser primo
		{
			if (i == n)
				printf("%d, ", i);
			c++;
		}
	}
	printf("\n");
}

// numeros impares
void F3(int n)
{
	int c = 0;
	int i = 1;
	if (!(n > 0))
	{
		printf("!!O NUMERO TEM DE SER MAIOR QUE ZERO!!");
		return;
	}
	while (c < n)
	{
		if ((i % 2) == 1)
		{
			c++;
			if (c == n)
				printf("%i", i);
		}
		i++;
	}
	printf("\n");
}

// Os "n" primeiros primos, com n > 0
void f1(int n)
{
	int a = 0, b, c, d;
	if (!(n > 0))
	{
		printf("!!O NUMERO TEM DE SER MAIOR QUE ZERO!!");
		return;
	}
	d = n * (-1);
	printf("Os primeiros %i numeros primos sao:\n", n);
	do
	{
		a++;
		c = 0;
		for (b = 1; b < a; b++)
			if (a % b == 0)
				c++;
		if (c == 1)
		{
			/* 			if (a == b)
						{
							printf("%i", a);
							return;
						}
						printf("%i, ", a); */
			printf("%i\n", a); // números primos
			d++;
		}
	} while (d); // Repete enquanto d for diferente de zero 0.
}

// recolhe um numero
int fNum(const char *msg)
{
	int x;
	printf("%s", msg);
	scanf("%i", &x);
	// limpar o buffer por causa do ultimo getchar()
	getc(stdin);
	return (x);
}

void menu()
{
	printf("Ecolha uma opcao:\n1 - Os \"n\" primeiros numeros primos.\n2 - O \"n\" numeros impar.\n3 - O valor de 2 elevado a \"n\".\n");
}

int main()
{

	int n;
	char op;
	int Fim = 1;

	do
	{
		menu();
		op = getchar();

		if (op < 48 || op > 51) // 0 e 3
			printf("Invalid input.\nNot a valid option!");
		switch (op)
		{
		case 'f':
		case 'F':
		case '0':
			Fim = 0;
			break;
		case '1':
			n = fNum("Quantos numeros primos pretende exibir? ");
			f1(n);
			break;
		case '2':
			n = fNum("Digite o numero que deseja ver se e par ou impar: ");
			F3(n);
			break;
		case '3':
			n = fNum("Digite o numero para elevar ao 2: ");
			printf("%d", f3(n));
			break;
		default:
			break;
		}

		if (Fim != 0)
		{
			Fim = fNum("\nContinuar(1) ou acabar(0)?: ");
		}
		if (Fim == 0)
		{
			printf("Fim do programa!");
		}

	} while (Fim != 0);

	return 0;
}
