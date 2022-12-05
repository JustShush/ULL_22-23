#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX 10

struct matriz {
	int m[MAX][MAX];
	int h;
	int w;
};

int RecolhaInt(const char* mensagem) {
	int x;
	printf("\n%s",mensagem);
	scanf("%i", &x);
	//limpar o buffer por causa do ?ltimo getchar()
	getc(stdin);
	return x;
}


int RecolheDim(const char* mensagem) {
	int res = 0;
	do {
		res = RecolhaInt(mensagem);
	} while (res <= 0 || res > MAX);
}

struct matriz RecolhaMatriz(const char* mensagem) {
	struct matriz res;
	char msg[40];
	int i;
	int j;
	
	printf("\n%s",mensagem);
	sprintf(msg,"Indique a altura da matriz [1..%i]: ", MAX);
	res.h = RecolheDim(msg);
	sprintf(msg,"Indique a largura da matriz [1..%i]: ", MAX);
	res.w = RecolhaInt(msg);

	for (i = 0;i < res.h; i++) {
		for (j = 0;j < res.w; j++) {

			sprintf(msg, "Indique o elemento da linha %i, coluna %i: [%i][%i] da matriz: ", i + 1, j + 1, i, j);
			res.m[i][j] = RecolhaInt(msg);
		}
	}
	return res;
}

struct matriz Multiplicar(struct matriz m1, struct matriz m2) {
	struct matriz res;
	res.h = 0;
	res.w = 0;
	int i1;
	int j1;
	int j2;
	if (m1.h == m2.w){
		res.h = m2.h;
		res.w = m1.w;
		for (i1 = 0;i1 < m1.w; i1++) {
			for(j2 = 0;j2 < m2.h; j2++){
				res.m[j2][i1] = 0;
				for(j1 = 0;j1 < m1.h; j1++) {
					res.m[j2][i1] = res.m[j2][i1] + m1.m[j1][i1] * m2.m[j2][j1];
				}
			}
		}
	}
	return res;
}


void MostrarMatriz(struct matriz m) {
	int i;
	int j;
	printf("Mostrar uma matriz de %i por %i\n", m.h, m.w);
	for (i = 0; i < m.h; i++){
		for(j = 0; j < m.w; j++)
			printf("%i, ", m.m[i][j]);
		printf("\n");
	}
}


int main(int argc, char* argv[]) {
	
	setlocale(LC_ALL,"Portuguese");
	struct matriz m1;
	struct matriz m2;
	struct matriz mr;
	int fim = 0;
	
	do {
		// criar a matriz m1
		m1 = RecolhaMatriz("Defina a matriz 1");
		//criar a matriz m2
		m2 = RecolhaMatriz("Defina a matriz 2");
		
		//Multiplicar as matrizes
		mr = Multiplicar(m1, m2);
		
		//mostrar o resultado
		if (mr.h == 0)
			printf("Matrizes nao compativeis\n");
		else
			MostrarMatriz(mr);
			
		fim = RecolhaInt("Continuar? (0) ou Acabar? (1): ");
	
	} while (fim == 0);
	
	return 0;
}

