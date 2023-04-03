#include "stdio.h"
# include <stdlib.h>
#include <stdint.h> // this is for the uint64_t

#define MAX_RECORDS 1000
#define MAX_LINE_LENGTH 2048

typedef struct data_st
{
	int day;
	int month;
	int year;
} data_t;

typedef struct covid_st
{
	data_t date;
	int confirmados;			 // (coluna 3)
	int confirmados_arsnorte;	 // (coluna 4)
	int confirmados_arscentro;	 // (coluna 5)
	int confirmados_arslvt;		 // (coluna 6)
	int confirmados_arsalentejo; // (coluna 7)
	int confirmados_arsalgarve;	 // (coluna 8)
	int confirmados_acores;		 // (coluna 9)
	int confirmados_madeira;	 // (coluna 10)
} covid_t;

int parse_file(FILE *csv_file, covid_t *records)
{
	// Already opened the file
	char line[MAX_LINE_LENGTH] = {0};
	fgets(line, MAX_LINE_LENGTH, csv_file); // Skip first line
	int num_records = 0;
	while (fgets(line, MAX_LINE_LENGTH, csv_file) != NULL)
	{
		if (sscanf(line, "%d-%d-%d,%*[^,],%d,%d,%d,%d,%d,%d,%d,%d,%*[^\n]\n",
				   &(records[num_records].date.day),
				   &(records[num_records].date.month),
				   &(records[num_records].date.year),
				   &(records[num_records].confirmados),
				   &(records[num_records].confirmados_arsnorte),
				   &(records[num_records].confirmados_arscentro),
				   &(records[num_records].confirmados_arslvt),
				   &(records[num_records].confirmados_arsalentejo),
				   &(records[num_records].confirmados_arsalgarve),
				   &(records[num_records].confirmados_acores),
				   &(records[num_records].confirmados_madeira)) == 11)
		{
			num_records++;
			if (num_records > MAX_RECORDS)
			{
				printf("Too many records, not storing the remaining part.\n");
				return MAX_RECORDS;
			}
		}
	}
	return num_records;
}
void display(covid_t *records, int num_records)
{
	for (int i = 0; i < num_records; i++)
	{
		printf("[%02d-%02d-%04d] Confirmados: %d\n",
			   records[i].date.day,
			   records[i].date.month,
			   records[i].date.year,
			   records[i].confirmados);
	}
}
void print_peak_day(covid_t *records, int num_records)
{
	int peak_idx = 0;
	int lowest = 0;
	int real = 0;
	for (int i = 0; i < num_records; i++)
	{
		if (records[peak_idx].confirmados < records[i].confirmados)
		{
			lowest = records[i].confirmados - records[peak_idx].confirmados;
			if(lowest > real) {
				real = lowest;
				//printf("lowest: %d\n", real);
			}
			peak_idx = i;
		}
	}

	printf("[%02d-%02d-%04d] Confirmados: %d\nIncrease: %d\n",
		   records[peak_idx].date.day,
		   records[peak_idx].date.month,
		   records[peak_idx].date.year,
		   records[peak_idx].confirmados,
		   real);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <csv-file>\n", argv[0]);
		return 0;
	}
	printf("Using file %s\n", argv[1]);
	FILE *input = fopen(argv[1], "r");
	if (input == NULL)
	{
		printf("Cannot open file %s\n", argv[1]);
		return 0;
	}
	// We can open the file
	int num_records = 0;
	covid_t data[MAX_RECORDS] = {0};
	num_records = parse_file(input, data);
	// display(data, num_records);
	print_peak_day(data, num_records);
	return 0;
}