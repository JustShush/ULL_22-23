#include <stdio.h>
#include <locale.h>

//Recolher um inteiro da consola
int RecolhaInt(const char* mensagem) {
	printf("\n%s",mensagem);
	int x;
	scanf("%i",&x);
	//Limpar o buffer
	getc(stdin);
	return x;
}

// Mostrar os n primeiros primos
void MostraPrimos(int n){
	int count=0;
	int i=1;
	int j;
	int m=0;
	while (count < n){
		for (j=2;j<i;j++){
			if((i % j) == 0)
				m=1;
		}
		if (m==0){
			printf("%i, ",i);
			count++;
		}
		i++;
		m=0;
	}
	if (count > 0)
		printf("\n");
	else
		printf("Não existem primos para mostrar\n");
}

// Mostar o n-ésimo impar
void MostraImpar(int n) {
	int count = 0;
	int i=0;
	while (count < n ){
		i++;
		if ((i % 2) == 1) {
			count++;
		}
	}
	// i = (n*2-1);
	if (n>0)
		printf("n-ésimo impar: %i\n",i);
	else
		printf("Não existem %i impares...\n",n);
}

// Calcular e mostrar 2^n
void Potencia2(int n){
//solução iterativa
	int j;
	int res=1;
	for (j=1;j<=n;j++)
		res = res * 2;
//		res *= 2;
	printf("O valor de 2^%i é: %i\n",n,res);
}

int Potencia2Rec(int n) {
	//solução recursiva
	if (n==0)
		return 1;
	else
		return 2 * Potencia2Rec(n-1);
}

int ValidaN(int n){
	int res = 0;
	if (n>=0 && n<=16)
		res=1;
	return res;
}

int main(){
	
	setlocale(LC_ALL,"Portuguese");
	
	int fim = 0;
	int op = 0;
	int n;
	
	do {
		printf("0 - Sair\n");
		printf("1 - N primeiros primos\n");
		printf("2 - n-ésimo impar\n");
		printf("3 - cálculo de 2^n\n");
		op = RecolhaInt("Digite uma opção entre 0 e 3: ");
		switch (op) {
			case 0:
				fim=1;
				break;
			case 1:
				n=RecolhaInt("Digite o valor de n: ");
				if (ValidaN(n)==1){
					MostraPrimos(n);
				} else {
					printf("O valor de n é negativo ou maior que 16\n");
				}
				break;
			case 2:
				n=RecolhaInt("Digite o valor de n: ");
				if (ValidaN(n)==1){
					MostraImpar(n);
				} else {
					printf("O valor de n é negativo ou maior que 16\n");
				}
				break;
			case 3:
				n=RecolhaInt("Digite o valor de n: ");
				if (ValidaN(n)==1){
					printf("Solução iterativa:\n");
					Potencia2(n);
					printf("Solução recursiva:\n");
					printf("O valor de 2^%i é %i\n",n,Potencia2Rec(n));
				} else {
					printf("O valor de n é negativo ou maior que 16\n");
				}
				break;
			default:
				printf("A opção tem de ser entre 0 e 3\n");
				break;
		}
		
	} while (fim==0);
	
	return 0;
}
