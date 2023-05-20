#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct sl_node_st
{
	covid_t *data;
	int diff_total;
	struct sl_node_st *prev;
	struct sl_node_st *next;
} sl_node_t;

void red(){ printf("\033[1;91m"); }

void yellow(){ printf("\033[1;33m"); }

void blue(){ printf("\033[0;34m"); }

void green(){ printf("\033[0;32m"); }

void white(){ printf("\033[0;37m"); }

void info(){ printf("\033[0;36m"); }

void reset(){ printf("\033[0m"); }

// Create an array of the columns, allowing to print them all in a loop
const char *columns[] = {
	"total",
	"arsnorte",
	"arscentro",
	"arslvt",
	"arsalentejo",
	"arsalgarve",
	"acores",
	"madeira",
	NULL};

int add_to_list(sl_node_t **lista, covid_t *new_record)
{
	sl_node_t *new_node = (sl_node_t *)malloc(sizeof(sl_node_t));
	if (new_node == NULL)
		return 0; // Cannot allocate memory, maybe scream an error here
	new_node->next = NULL;
	new_node->data = new_record;
	new_node->diff_total = 0;
	if (*lista == NULL)
	{ // List was empty, new node becomes the list
		*lista = new_node;
		return 1;
	}
	sl_node_t *it = *lista;
	while (it->next != NULL)
		it = it->next;
	it->next = new_node;
	new_node->prev = it;
	return 1;
}

int parse_file(FILE *csv_file, sl_node_t **lista)
{
	// Already opened the file
	char line[MAX_LINE_LENGTH] = {0};
	fgets(line, MAX_LINE_LENGTH, csv_file); // Skip first line
	int num_records = 0;
	covid_t tmp_newrecord = {0}; // Use a temp covid record to be able to check the new input
	while (fgets(line, MAX_LINE_LENGTH, csv_file) != NULL)
	{
		if (sscanf(line, "%d-%d-%d,%*[^,],%d,%d,%d,%d,%d,%d,%d,%d,%*[^\n]\n",
				   &(tmp_newrecord.date.day),
				   &(tmp_newrecord.date.month),
				   &(tmp_newrecord.date.year),
				   &(tmp_newrecord.confirmados),
				   &(tmp_newrecord.confirmados_arsnorte),
				   &(tmp_newrecord.confirmados_arscentro),
				   &(tmp_newrecord.confirmados_arslvt),
				   &(tmp_newrecord.confirmados_arsalentejo),
				   &(tmp_newrecord.confirmados_arsalgarve),
				   &(tmp_newrecord.confirmados_acores),
				   &(tmp_newrecord.confirmados_madeira)) == 11)
		{
			// Valid record, allocate space for one more record
			// Usa a tmp_records, because otherwise you might lose the old allocation
			covid_t *new_record = (covid_t *)malloc(sizeof(covid_t));
			*new_record = tmp_newrecord;
			add_to_list(lista, new_record);
			num_records++;
		}
	}
	return num_records;
}

int calc_diff(covid_t *record1, covid_t *record2, const char *column)
{
	if (record1 == NULL)
		return 0;
	if (strcasecmp(column, "arsnorte") == 0)
	{
		return record2->confirmados_arsnorte - record1->confirmados_arsnorte;
	}
	if (strcasecmp(column, "arscentro") == 0)
	{
		return record2->confirmados_arscentro - record1->confirmados_arscentro;
	}
	if (strcasecmp(column, "arslvt") == 0)
	{
		return record2->confirmados_arslvt - record1->confirmados_arslvt;
	}
	if (strcasecmp(column, "arsalentejo") == 0)
	{
		return record2->confirmados_arsalentejo - record1->confirmados_arsalentejo;
	}
	if (strcasecmp(column, "arsalgarve") == 0)
	{
		return record2->confirmados_arsalgarve - record1->confirmados_arsalgarve;
	}
	if (strcasecmp(column, "acores") == 0)
	{
		return record2->confirmados_acores - record1->confirmados_acores;
	}
	if (strcasecmp(column, "madeira") == 0)
	{
		return record2->confirmados_madeira - record1->confirmados_madeira;
	}
	if (strcasecmp(column, "total") != 0)
	{
		printf("Unknown column, using total");
	}
	return record2->confirmados - record1->confirmados;
}

/* int peak_day(covid_t *records, int num_records, const char *column)
{
	if (num_records == 0)
	{
		printf("No records available.\n");
		return -1;
	}
	// We have no max value yet, so the first is the maximum value
	int peak_idx = 0;
	// So start from the second
	int peak_diff = 0;
	int diff;
	for (int i = 1; i < num_records; i++)
	{
		diff = calc_diff(&records[i - 1], &records[i], column);
		if (peak_diff < diff)
		{
			peak_diff = diff;
			peak_idx = i;
		}
	}
	return peak_idx;
}

void peak_day_results(covid_t *records, int peak_idx, const char *column)
{
	covid_t *record1 = NULL;
	if (peak_idx > 0)
	{
		record1 = &records[peak_idx - 1];
	}
	covid_t *record2 = &records[peak_idx];
	int peak_diff = calc_diff(record1, record2, column);
	printf("[%02d-%02d-%04d] Peak %s: %d\n",
		   records[peak_idx].date.day,
		   records[peak_idx].date.month,
		   records[peak_idx].date.year,
		   column,
		   peak_diff);
} */

void swap_nodes(sl_node_t *node1, sl_node_t *node2)
{
	covid_t *temp_data = node1->data;
	int temp_diff = node1->diff_total;
	node1->data = node2->data;
	node1->diff_total = node2->diff_total;
	node2->data = temp_data;
	node2->diff_total = temp_diff;
}

// Step 3: Sort the linked list by diff_total in descending order
void bubble_sort(sl_node_t **lista)
{
	if (*lista == NULL || (*lista)->next == NULL)
		return;

	int swapped;
	sl_node_t *current;
	sl_node_t *last = NULL;

	do
	{
		swapped = 0;
		current = *lista;

		while (current->next != last)
		{
			if (current->diff_total < current->next->diff_total)
			{
				swap_nodes(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		last = current;
	} while (swapped);
}

// Step 4: Print the top 10 elements
void print_top_10(sl_node_t *lista)
{
	blue();
	printf("Top 10 elements:\n");
	int count = 0;
	sl_node_t *current = lista;
	printf("----------------------\n");
	reset();
	while (current != NULL && count < 10)
	{
		white();
		printf("Date: [%02d-%02d-%04d]\n",
			   current->data->date.day,
			   current->data->date.month,
			   current->data->date.year);
		printf("Diff Total: %d\n", current->diff_total);
		reset();
		blue();
		printf("----------------------\n");
		reset();
		current = current->next;
		count++;
	}
}

// Step 5: Free the linked list
void release_covid_data(sl_node_t **lista)
{
	sl_node_t *current = *lista;
	while (current != NULL)
	{
		sl_node_t *next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	*lista = NULL;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		info();
		printf("Use like: %s <csv-file>\n", argv[0]);
		reset();
		return 0;
	}
	FILE *input = fopen(argv[1], "r");
	if (input == NULL)
	{
		red();
		printf("Cannot open file %s\n", argv[1]);
		reset();
		return 0;
	}
	green();
	printf("Using file %s\n", argv[1]);
	reset();
	// We can open the file
	sl_node_t *lista = NULL;
	parse_file(input, &lista);

	// Step 2: Calculate the difference and update diff_total in the nodes
	sl_node_t *current = lista;
	while (current != NULL)
	{
		sl_node_t *next = current->next;
		if (next != NULL)
		{
			const char *column = columns[0]; // Using "total" column
			current->diff_total = calc_diff(current->data, next->data, column);
		}
		current = next;
	}

	// Step 3: Sort the linked list by diff_total in descending order
	bubble_sort(&lista);

	// Step 4: Print the top 10 elements
	print_top_10(lista);

	// Step 5: Free the linked list
	release_covid_data(&lista);

	return 0;
}
