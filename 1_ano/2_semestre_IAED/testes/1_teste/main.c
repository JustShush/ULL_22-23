#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 2048

typedef struct covid_date_s
{
	int dia;
	int mes;
	int ano;
} covid_date_t;

typedef struct covid_data_t
{
	covid_date_t data;
	int confirmados;
	int confirmados_arsnorte;
	int confirmados_arscentro;
	int confirmados_arslvt;
	int confirmados_arsalentejo;
	int confirmados_arsalgarve;
	int confirmados_acores;
	int confirmados_madeira;
} covid_data_t;

void red() {
	printf("\033[1;91m");
}

void yellow() {
	printf("\033[1;33m");
}

void blue() {
	printf("\033[0;34m");
}

void white() {
	printf("\033[0;37m");
}

void info() {
	printf("\033[0;36m");
}

void reset() {
	printf("\033[0m");
}

int parse_covid_data(const char *filename, covid_data_t **covid_data_lst[], int *num_cases)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		red();
		printf("Erro na abertura do arquivo.\nPor favor verificar se o nome do ficheiro esta correto.\n");
		reset();
		exit(0);
	}

	char linha[MAX_LINE] = {0};
	covid_data_t *new_list;
	int days_w_cases = 0;

	// skip first line
	fgets(linha, MAX_LINE, fp);

	while (fgets(linha, MAX_LINE, fp) != NULL)
	{
		new_list = (covid_data_t *)malloc(sizeof(covid_data_t));
		sscanf(linha, "%d-%d-%d,%*[^,],%d,%d,%d,%d,%d,%d,%d,%d,%*[^\n]\n",
			   &(new_list->data.dia),
			   &(new_list->data.mes),
			   &(new_list->data.ano),
			   &(new_list->confirmados),
			   &(new_list->confirmados_arsnorte),
			   &(new_list->confirmados_arscentro),
			   &(new_list->confirmados_arslvt),
			   &(new_list->confirmados_arsalentejo),
			   &(new_list->confirmados_arsalgarve),
			   &(new_list->confirmados_acores),
			   &(new_list->confirmados_madeira));
		*covid_data_lst = realloc(*covid_data_lst, sizeof(covid_data_t *) * (days_w_cases + 1));
		(*covid_data_lst)[days_w_cases] = new_list;
		new_list = NULL;
		days_w_cases++;
	}
	*covid_data_lst = realloc(*covid_data_lst, sizeof(covid_data_t *) * (days_w_cases + 1));
	(*covid_data_lst)[days_w_cases] = NULL;
	*num_cases = days_w_cases;
	return 0;
}

int peak_day(covid_data_t *covid_data_lst[], int cases, int *max_day, int *max_month, int *max_year, int *max_cases_covid, int idx)
{
	int ant_peak_day = 0;

	switch (idx)
	{
	case 1:
	{
		for (int i = 1; i < cases; ++i)
		{
			int peak_day = covid_data_lst[i]->confirmados - covid_data_lst[i - 1]->confirmados;
			if (peak_day > ant_peak_day && i > 0)
			{
				ant_peak_day = peak_day;
				*max_day = covid_data_lst[i]->data.dia;
				*max_month = covid_data_lst[i]->data.mes;
				*max_year = covid_data_lst[i]->data.ano;
				*max_cases_covid = covid_data_lst[i]->confirmados - covid_data_lst[i - 1]->confirmados;
			}
		}
		break;
	}
	case 2:
	{
		for (int i = 1; i < cases; ++i)
		{
			int peak_day = covid_data_lst[i]->confirmados_arsnorte - covid_data_lst[i - 1]->confirmados_arsnorte;
			if (peak_day > ant_peak_day && i > 0)
			{
				ant_peak_day = peak_day;
				*max_day = covid_data_lst[i]->data.dia;
				*max_month = covid_data_lst[i]->data.mes;
				*max_year = covid_data_lst[i]->data.ano;
				*max_cases_covid = covid_data_lst[i]->confirmados_arsnorte - covid_data_lst[i - 1]->confirmados_arsnorte;
			}
		}
		break;
	}
	case 3:
	{
		for (int i = 1; i < cases; ++i)
		{
			int peak_day = covid_data_lst[i]->confirmados_arscentro - covid_data_lst[i - 1]->confirmados_arscentro;
			if (peak_day > ant_peak_day && i > 0)
			{
				ant_peak_day = peak_day;
				*max_day = covid_data_lst[i]->data.dia;
				*max_month = covid_data_lst[i]->data.mes;
				*max_year = covid_data_lst[i]->data.ano;
				*max_cases_covid = covid_data_lst[i]->confirmados_arscentro - covid_data_lst[i - 1]->confirmados_arscentro;
			}
		}
		break;
	}
	case 4:
	{
		for (int i = 1; i < cases; ++i)
		{
			int peak_day = covid_data_lst[i]->confirmados_arslvt - covid_data_lst[i - 1]->confirmados_arslvt;
			if (peak_day > ant_peak_day && i > 0)
			{
				ant_peak_day = peak_day;
				*max_day = covid_data_lst[i]->data.dia;
				*max_month = covid_data_lst[i]->data.mes;
				*max_year = covid_data_lst[i]->data.ano;
				*max_cases_covid = covid_data_lst[i]->confirmados_arslvt - covid_data_lst[i - 1]->confirmados_arslvt;
			}
		}
		break;
	}
	case 5:
	{
		for (int i = 1; i < cases; ++i)
		{
			int peak_day = covid_data_lst[i]->confirmados_arsalentejo - covid_data_lst[i - 1]->confirmados_arsalentejo;
			if (peak_day > ant_peak_day && i > 0)
			{
				ant_peak_day = peak_day;
				*max_day = covid_data_lst[i]->data.dia;
				*max_month = covid_data_lst[i]->data.mes;
				*max_year = covid_data_lst[i]->data.ano;
				*max_cases_covid = covid_data_lst[i]->confirmados_arsalentejo - covid_data_lst[i - 1]->confirmados_arsalentejo;
			}
		}
		break;
	}
	case 6:
	{
		for (int i = 1; i < cases; ++i)
		{
			int peak_day = covid_data_lst[i]->confirmados_arsalgarve - covid_data_lst[i - 1]->confirmados_arsalgarve;
			if (peak_day > ant_peak_day && i > 0)
			{
				ant_peak_day = peak_day;
				*max_day = covid_data_lst[i]->data.dia;
				*max_month = covid_data_lst[i]->data.mes;
				*max_year = covid_data_lst[i]->data.ano;
				*max_cases_covid = covid_data_lst[i]->confirmados_arsalgarve - covid_data_lst[i - 1]->confirmados_arsalgarve;
			}
		}
		break;
	}
	case 7:
	{
		for (int i = 1; i < cases; ++i)
		{
			int peak_day = covid_data_lst[i]->confirmados_acores - covid_data_lst[i - 1]->confirmados_acores;
			if (peak_day > ant_peak_day && i > 0)
			{
				ant_peak_day = peak_day;
				*max_day = covid_data_lst[i]->data.dia;
				*max_month = covid_data_lst[i]->data.mes;
				*max_year = covid_data_lst[i]->data.ano;
				*max_cases_covid = covid_data_lst[i]->confirmados_acores - covid_data_lst[i - 1]->confirmados_acores;
			}
		}
		break;
	}
	case 8:
	{
		for (int i = 1; i < cases; ++i)
		{
			int peak_day = covid_data_lst[i]->confirmados_madeira - covid_data_lst[i - 1]->confirmados_madeira;
			if (peak_day > ant_peak_day && i > 0)
			{
				ant_peak_day = peak_day;
				*max_day = covid_data_lst[i]->data.dia;
				*max_month = covid_data_lst[i]->data.mes;
				*max_year = covid_data_lst[i]->data.ano;
				*max_cases_covid = covid_data_lst[i]->confirmados_madeira - covid_data_lst[i - 1]->confirmados_madeira;
			}
		}
		break;
	}
	}
	return 0;
}

int peak_day_results(const int *max_day, const int *max_month, const int *max_year, const int *max_cases_covid, const int idx)
{
	white();
	switch (idx)
	{
	case 1:
	{
		printf("%d/%d/%d\t %d\t\t Nacional\n", *max_day, *max_month, *max_year, *max_cases_covid);
		break;
	}
	case 2:
	{
		printf("%d/%d/%d\t %d\t\t Norte\n", *max_day, *max_month, *max_year, *max_cases_covid);
		break;
	}
	case 3:
	{
		printf("%d/%d/%d\t %d\t\t Centro\n", *max_day, *max_month, *max_year, *max_cases_covid);
		break;
	}
	case 4:
	{
		printf("%d/%d/%d\t %d\t\t Lisboa e vale do Tejo\n", *max_day, *max_month, *max_year, *max_cases_covid);
		break;
	}
	case 5:
	{
		printf("%d/%d/%d\t %d\t\t Alentejo\n", *max_day, *max_month, *max_year, *max_cases_covid);
		break;
	}
	case 6:
	{
		printf("%d/%d/%d\t %d\t\t Algarve\n", *max_day, *max_month, *max_year, *max_cases_covid);
		break;
	}
	case 7:
	{
		printf("%d/%d/%d\t %d\t\t Acores\n", *max_day, *max_month, *max_year, *max_cases_covid);
		break;
	}
	case 8:
	{
		printf("%d/%d/%d\t %d\t\t Madeira", *max_day, *max_month, *max_year, *max_cases_covid);
		break;
	}
	}
	reset();
	return 0;
}

void release_covid_data(covid_data_t **covid_data_lst[])
{
	int i = 0;
	while ((*covid_data_lst)[i] != NULL)
	{
		free((*covid_data_lst)[i]);
		i++;
	}
	free(*covid_data_lst);
	*covid_data_lst = NULL;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		info();
		printf("Como usar: %s <nome do ficheiro>\n", argv[0]);
		reset();
		return 1;
	}
	char *filename = argv[1];

	int max_day = 0, max_month = 0, max_year = 0, max_cases = 0;

	int tam_covid_lst = 0;

	covid_data_t **covid_data_lst = NULL;
	parse_covid_data(filename, &covid_data_lst, &tam_covid_lst);
	blue();
	printf("DATA:\t\t cases:\t\t REGIAO:\n");
	reset();
	int indice = 1;
	for (int i = 0; i < 8; ++i)
	{
		peak_day(covid_data_lst, tam_covid_lst, &max_day, &max_month, &max_year, &max_cases, indice);
		peak_day_results(&max_day, &max_month, &max_year, &max_cases, indice);
		indice++;
	}
	printf("\n");
	release_covid_data(&covid_data_lst);
	return 0;
}