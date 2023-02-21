#include <stdio.h>
#include <string.h>

#define SIZE 10

// Estrutura para guardar a informa��o de um aluno
struct aluno
{
	int numero;
	char nome[80];
};

typedef struct aluno ALUNO;

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

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

// Mostrar os dados de um aluno
void ShowAluno(ALUNO aluno)
{
	printf("Numero: %i\nNome: %s\n\n", aluno.numero, aluno.nome);
	return;
}

void showAll(ALUNO* aluno, int i)
{
	//printf("\nvalores introduzidos = %d\n\n", i);
	if (!(i >= 0)) return printf("\nNao existem alunos para mostrar.\n");
	while (i >= 0)
	{
		printf("Numero: %d\nNome: %s\n\n", aluno[i].numero, aluno[i].nome);
		i--;
	}
}

// Inserir um aluno
void AddAluno(ALUNO *aluno, int *i)
{
	// aluno � o apontador para o vetor de alunos
	// i � o apontador para o �ltimo elemento inserido no vetor
	//
	// para obter o valor a que o apontador i se refere utilizaza-se
	// a *dereferencia��o* na forma (*i),
	// que significa "o valor inteiro que est� no endere�o i"
	//
	// Verifica se o vetor ainda tem slots dispon�veis
	if ((*i) == SIZE)
	{
		printf("N�mero m�ximo de alunos atingido!!\n\n");
		return;
	}
	// Como n�o estamos no �ltimo elemento podemos incrementar o n�mero
	// do �ltimo elemento e inseri-lo
	(*i)++;
	// Recolha do n�mero do novo aluno
	aluno[(*i)].numero = RecolhaInt("Escreva o n�mero do novo aluno: ");
	// Recolha do nome do novo aluno
	printf("Escreva o nome do novo aluno: ");
	scanf("%s", aluno[(*i)].nome);
	getc(stdin);

	printf("Aluno inserido!\n");
	return;
}

// Apagar um aluno
void DelAluno(ALUNO *aluno, int *i, int *n)
{
	// Vamos copiar todos os elementos seguintes do vetor ao elemento a apagar
	// para o elemento anterior e, no final, reduzir o n�mero de elementos
	// do vetor em uma unidade.
	// n � o apontador para o n�mero do vetor a apagar e
	// i � o apontador para o n�mero de elementos do vetor
	// aluno � o apontador para o vetor de dados

	int j; // vari�vel auxiliar para ir de "n" a "i"
	// percorrer o vetor a come�ar no elemento "(*n)" at� ao pen�ltimo (j <(*i)
	// vamos, em cada volta do ciclo, copiar o elemento j+1 para o elemento j
	for (j = (*n); j < (*i); j++)
	{
		// Copiar o nome seguinte para a posi��o corrente
		ft_strcpy(aluno[j].nome, aluno[j + 1].nome);
		// copiar o n�mero seguinte para a posi��o corrente
		aluno[j].numero = aluno[j + 1].numero;
	}
	// dimunuir o n�mero de elementos do vetor em uma unidade
	// dado que i � um apontador para um inteiro, (*i) representa
	//"o valor inteiro que esta�no endere�o i"
	(*i)--;
	// dado que podemos estar a eliminar o �ltimo elemento, o valor de (*n)
	// nunca pode ser superior ao de (*i), pois neste caso estaria
	// a apontar para um elemento n�o existente.
	// Neste caso, se o valor for superior ter� de ser tornado igual
	// Mesmo no caso de supress�o do �ltimo elemento em que (*i)
	// ir� ter o valor de -1, (*n) ter� for�osamente de ser igual
	if ((*n) > (*i))
		(*n) = (*i);
	// Mostrar os dados do aluno corrente, se este existir
	if ((*n) >= 0)
		ShowAluno(aluno[(*n)]);
	return;
}

// Alterar um aluno
void ModAluno(ALUNO *aluno, int n)
{
	// aluno � o apontador para o vetor de alunos
	// Neste caso, dado que n�o h� altera��o nem do n�mero do elemento corrente
	// nem do n�mero de elementos do vetor, o elemento corrente (n)
	//� passado por valor e n�o por refer�ncia (apontador)

	// recolher o novo n�mero de aluno
	aluno[n].numero = RecolhaInt("Escreva o novo n�mero do aluno: ");

	// recolher o novo nome do aluno
	printf("Escreva o novo nome do aluno: ");
	scanf("%s", aluno[n].nome);
	getc(stdin);

	printf("Aluno alterado!\n");
	return;
}

// Importar de ficheiro
void Import(ALUNO *aluno, int *i, int *n)
{
	// Ler os dados de alunos num ficheiro de texto com o formato
	//<num�ro> <nome>
	// em cada linha.
	// Os valores de i e de n s�o passados por refer�ncia (apontadores)
	// dado que o vetor ir� ser inicializado com os dados do ficheiro
	// perdendo-se tudo o que no vetor poderia existir

	int li = -1; // vari�vel auxiliar para contar linhas lidas no ficheiro

	// vari�veis auxiliares para leitaura do ficheiro
	int num;
	char nom[80];

	// abrir o ficheiro contendo os dados para leitura ("r")
	FILE *f = fopen("alunos.txt", "r");
	// verificar se a opera��o de abertura foi efetuada com sucesso,
	// caso contr�rio abandonar a rotina sem altera��es ao vator
	if (!f)
	{
		// Inicializar os valores de (*i) e de (*n) para "vetor vazio" (ambos a -1)
		(*i) = -1;
		(*n) = -1;

		// Ler as linhas do ficheiro, no formato especificado at� ao fim do ficheiro (EOF),
		// ou at� ao n�mero limite de dados (SIZE)
		while ((fscanf(f, "%i %s\n", &num, nom) != EOF) && (li < SIZE))
		{
			// incrementar o n�mero de linhas [alunos] lidos
			li++;
			// Copiar o n�mero lido para o elemento li do vetor
			aluno[li].numero = num;
			// Copiar o nome lido para o elemento li do vetor
			ft_strcpy(aluno[li].nome, nom);
		}
		// atribuir � dimens�o do vetor o n�mero de linhas lidas
		(*i) = li;
		// Se houver linhas lidas, atribuir 0 (zero) ao elemento corrente e mostrar
		// os respetivos dados
		if (li >= 0)
		{
			(*n) = 0;
			// dado que (*n) � 0, podemos obviar e mostrar aluno[0] em vez
			// de aluno[(*n)], (que � a mesma coisa), mas sem o tempo da opera��o
			// de dereferencia��o
			ShowAluno(aluno[0]);
		}
		//**IMPORTANTE**
		// Fechar o ficheiro aberto para obter os dados
		fclose(f);
	}
	else
		printf("Erro ao abrir o ficheiro\n");
	return;
}

// Exportar para ficheiro
void Export(ALUNO *aluno, int i)
{
	// Gravar os dados de todos os alunos do vetor com o formato
	//<numero> <nome>
	// em cada linha
	// Dado que apenas vamos gravar os dados em ficheiro e n�o vai ser alterada
	// nem a posi��o corrente, nem o n�mero de elementos do vetor,
	// a dimens�o do vetor � passada por valor e n�o por refer�ncia (apontador)

	int n; // vari�vel auxiliar para precorrer o vetor
	// abrir o ficheiro para escrita. Se o ficheiro existir � apagado e criado um novo, vazio ("w")
	FILE *f = fopen("alunos.txt", "w");
	// verificar se a opera��o de abertura foi efetuada com sucesso,
	if (!f)
	{
		// percorrer o vetor desde o elemento 0 at� ao elemento i (inclusiv�)
		// e gravar cada aluno numa linha
		for (n = 0; n <= i; n++)
			// escrever o aluno n no ficheiro
			fprintf(f, "%i %s\n", aluno[n].numero, aluno[n].nome);
		fclose(f);
	}
	else
		printf("Erro na cria��o do ficheiro\n");
	return;
}


void menu()
{
	printf("|---------------------------------------|\n|		   Menu   		|\n");
	printf("|0 - Sair ------------------------------|\n");
	printf("|1 - Inserir Aluno ---------------------|\n");
	printf("|2 - Alterar Aluno ---------------------|\n");
	printf("|3 - Apagar Aluno ----------------------|\n");
	printf("|4 - Ir para o primeiro ----------------|\n");
	printf("|5 - Ir para o anterior ----------------|\n");
	printf("|6 - Ir para o seguinte ----------------|\n");
	printf("|7 - Ir para o ultimo ------------------|\n");
	printf("|8 - Exportar alunos para ficheiro -----|\n");
	printf("|9 - Importar alunos de ficheiro -------|\n");
	printf("|---------------------------------------|");
}

int main()
{
	// vetor a tratar
	ALUNO alunos[SIZE];
	// indicador de localiza��o do vetor
	int i = -1; // dimens�o de elementos v�lidos no vetor
	int n = -1; // elemento corrente do vetor

	char op;	 // seletor de op��es
	int fim = 1; // indica��o de fim de execu��o

	// ciclo principal de op��es
	//*NOTA*
	// Dada a natureza dos testes feitos nas op��es, a primeira op��o v�lida s� poder� ser
	// ou adicionar elementos, ler de ficheiro ou terminar o programa
	do
	{
		// mostrar menu de op��es
		menu();
		// recolher op��o
		op = fNum("Digite uma op��o: ");
		// de acordo com a op��o efetuar uma das opera��es
		// descritas acima
		switch (op)
		{
		case 'f':
		case 'F':
			// fim = 1;
			printf("Fim do programa!\n");
			return 0;
			break;
		case '0': // fim do programa
			// assinala o fim
			// fim = 2;
			// Termina o switch
			showAll(alunos, i);
			break;
		case '1': // Inserir um aluno
			// Evoca a adi��o de alunos passando por refer�ncia
			// o vetor e o n�mero de elementos v�lidos
			AddAluno(alunos, &i);
			// atribui ao n�mero do elemento corrente
			// o n�mero do elemento inserido
			n = i;
			// Termina o switch
			break;
		case '2': // Modificar o elemento n
			// se o vetor tiver alunos
			if (i >= 0)
				// evoca a rotina de modifica��o do aluno corrente
				ModAluno(alunos, n);
			else
				printf("N�o h� alunos inseridos\n");
			// Termina o switch
			break;
		case '3': // Apagar o elemento n
			// se o vetor tiver alunos
			if (i >= 0)
				// evoca a rotina de elimina��o de um elemento
				DelAluno(alunos, &i, &n);
			else
				printf("N�o h� alunos inseridos\n");
			break;
		case '4': // ir para o primeiro elemento
			// se o vetor tiver alunos
			if (i >= 0)
			{
				// atribuir 0 ao valor corrente e mostrar os dados do aluno
				n = 0;
				ShowAluno(alunos[n]);
			}
			else
			{
				printf("N�o h� alunos inseridos\n");
			}
			break;
		case '5': // ir para o elemento anterior
			// se o vetor tiver alunos
			if (i >= 0)
			{
				// e se n�o estou no primeiro
				if (n > 0)
				{
					// diminuir o n�mero corrente numa unidade e mostrar os dados do aluno
					n--;
					ShowAluno(alunos[n]);
				}
				else
				{
					printf("N�o pode passar para tr�s do primeiro\n");
				}
			}
			else
			{
				printf("N�o h� alunos inseridos\n");
			}
			// Termina o switch
			break;
		case '6': // ir para o elemento seguinte
			// se o vetor tiver elementos
			if (i >= 0)
			{
				// e se n�o estou no �ltimo (n = i)
				if (n < i)
				{
					// aumentar o n�mero corrente numa unidade e mostrar os dados do aluno
					n++;
					ShowAluno(alunos[n]);
				}
				else
				{
					printf("Nao pode passar para a frente do �ltimo\n");
				}
			}
			else
			{
				printf("Nao ha alunos inseridos\n");
			}
			// Terminar o switch
			break;
		case '7': // ir para o �ltimo
			// se o vetor tiver alunos
			if (i >= 0)
			{
				// atribuir a n o n�mero de elementos v�lidos do vetor e mostrar os dados do aluno
				n = i;
				ShowAluno(alunos[n]);
			}
			else
			{
				printf("Nao ha alunos inseridos\n");
			}
			// Terminar o switch
			break;
		case '8': // Exportar para ficheiro
			// Se o vetor tiver alunos
			if (i >= 0)
				// evocar a rotina de exporta��o para ficheiro
				Export(alunos, i);
			else
				printf("Nao ha alunos inseridos\n");
			// Terminar o switch
			break;
		case '9': // Importar de ficheiro
			// Evocar a rotina de importa��o dos dados de alunos a partir de ficheiro
			// NOTA: os valores de i e de n ir�o ser atualizados em fun��o do n�mero
			// de elementos lidos do ficheiro
			Import(alunos, &i, &n);
			// Terminar o switch
			break;
		default:
			// Indica��o de op��o errada
			printf("Escolha uma opcao do menu\n");
			// Terminar o switch
			break;
		}

		fim = RecolhaInt("Continuar?(1) ou Acabar?(2): ");
		if (fim == 2)
			printf("Fim do programa!\n");

	} while (fim == 1); // Repetir o ciclo enquanto a vari�vel fim contiver o valor "n"

	// fim do programa com indica��o de sucesso no retorno ao sistema de explora��o
	return 0;
}
