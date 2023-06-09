#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 2048


typedef struct data_st {
    int day;
    int month;
    int year;
} data_t;
typedef struct covid_st {
    data_t date;
    int confirmados; // (coluna 3)
    int confirmados_arsnorte; // (coluna 4)
    int confirmados_arscentro; // (coluna 5)
    int confirmados_arslvt; // (coluna 6)
    int confirmados_arsalentejo; // (coluna 7)
    int confirmados_arsalgarve; // (coluna 8)
    int confirmados_acores; // (coluna 9)
    int confirmados_madeira; // (coluna 10)
} covid_t;

typedef struct dl_node_st {
    covid_t *data;
    int diff_total;
    struct dl_node_st *next;
    struct dl_node_st *prev;
} dl_node_t;

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
        NULL
};

int add_to_list(dl_node_t **lista, covid_t *new_record) {

    dl_node_t *new_node = (dl_node_t*)malloc(sizeof(dl_node_t));
    if (new_node == NULL) return 0; // Cannot allocate memory, maybe scream an error here
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->data = new_record;
    new_node->diff_total = 0;
    if (*lista == NULL) {   // List was empty, new node becomes the list
        *lista = new_node;
        return 1;
    }
    dl_node_t *it = *lista;
    while (it->next != NULL) it = it->next;
    it->next = new_node;
    new_node->prev = it;
    return 1;
}

int parse_file(FILE *csv_file, dl_node_t **lista) {
    // Already opened the file
    char line[MAX_LINE_LENGTH] = {0};
    fgets(line, MAX_LINE_LENGTH, csv_file); // Skip first line
    int num_records = 0;
    covid_t tmp_newrecord = {0};    // Use a temp covid record to be able to check the new input
    while(fgets(line, MAX_LINE_LENGTH, csv_file) != NULL) {
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
                   &(tmp_newrecord.confirmados_madeira)) == 11) {
            // Valid record, allocate space for one more record
            // Usa a tmp_records, because otherwise you might lose the old allocation
            covid_t *new_record = (covid_t*)malloc(sizeof(covid_t));
            *new_record = tmp_newrecord;
            add_to_list(lista, new_record);
        }
    }
    return num_records;
}

void traverse(dl_node_t *lista) {
    if (lista == NULL) return;  // If list is empty, we're done
    if (lista->next == NULL) return; // If list has 1 element, we're done
    for (dl_node_t *it = lista->next; it != NULL; it = it->next) {
        it->diff_total = it->data->confirmados - it->prev->data->confirmados;
    }
}

void bubble_sort(dl_node_t *lista) {
    if (lista == NULL) return;  // If list is empty, we're done
    if (lista->next == NULL) return; // If list has 1 element, we're done
    int size = 1;
    for (dl_node_t *it = lista; it != NULL; it = it->next) {
        size++;
    }
    int swap = 0;
    dl_node_t *it = NULL;

    while (size > 1) {
        swap = 0;
        it = lista;
        for (int i = 0; (i < size) && (it->next != NULL); i++) {
            if (it->next->diff_total > it->diff_total) {    // swap
                covid_t *tmp_d = it->data;
                it->data = it->next->data;
                it->next->data = tmp_d;
                int tmp_i = it->diff_total;
                it->diff_total = it->next->diff_total;
                it->next->diff_total = tmp_i;
                swap++;
            }
            it = it->next;
        }
        if (swap == 0) return;
        size--;
    }
}

void display(dl_node_t *lista, int records) {
    if (lista == NULL) return;  // If list is empty, we're done
    dl_node_t *it = lista;
    for (int i = 0; i < records; i++) {
        if (it == NULL) break;
        printf("%02d-%02d-%04d Diff: %d\n", it->data->date.day, it->data->date.month, it->data->date.year, it->diff_total);
        it = it->next;
    }
}

void release(dl_node_t **lista) {
    while ((*lista) != NULL) {
        dl_node_t *next = (*lista)->next;
        free((*lista)->data);
        free(*lista);
        *lista = next;
    }
    *lista = NULL;
}

int calc_diff(covid_t *record1, covid_t *record2, const char *column) {
    if (record1 == NULL) return 0;
    if (strcasecmp(column, "arsnorte") == 0) {
        return record2->confirmados_arsnorte - record1->confirmados_arsnorte;
    }
    if (strcasecmp(column, "arscentro") == 0) {
        return record2->confirmados_arscentro - record1->confirmados_arscentro;
    }
    if (strcasecmp(column, "arslvt") == 0) {
        return record2->confirmados_arslvt - record1->confirmados_arslvt;
    }
    if (strcasecmp(column, "arsalentejo") == 0) {
        return record2->confirmados_arsalentejo - record1->confirmados_arsalentejo;
    }
    if (strcasecmp(column, "arsalgarve") == 0) {
        return record2->confirmados_arsalgarve - record1->confirmados_arsalgarve;
    }
    if (strcasecmp(column, "acores") == 0) {
        return record2->confirmados_acores - record1->confirmados_acores;
    }
    if (strcasecmp(column, "madeira") == 0) {
        return record2->confirmados_madeira - record1->confirmados_madeira;
    }
    if (strcasecmp(column, "total") != 0) {
        printf("Unknown column, using total");
    }
    return record2->confirmados - record1->confirmados;
}

int peak_day(covid_t *records, int num_records, const char *column) {
    if (num_records == 0) {
        printf("No records available.\n");
        return -1;
    }
    // We have no max value yet, so the first is the maximum value
    int peak_idx = 0;
    // So start from the second
    int peak_diff = 0;
    int diff;
    for (int i = 1; i < num_records; i++) {
        diff = calc_diff(&records[i-1], &records[i], column);
        if ( peak_diff < diff) {
            peak_diff = diff;
            peak_idx = i;
        }
    }
    return peak_idx;
}

void peak_day_results(covid_t *records, int peak_idx, const char *column) {
    covid_t *record1 = NULL;
    if (peak_idx > 0) {
        record1 = &records[peak_idx-1];
    }
    covid_t *record2 = &records[peak_idx];
    int peak_diff = calc_diff(record1, record2, column);
    printf("[%02d-%02d-%04d] Peak %s: %d\n",
           records[peak_idx].date.day,
           records[peak_idx].date.month,
           records[peak_idx].date.year,
           column,
           peak_diff);
}

void release_covid_data(covid_t **records) {
    free(*records);
    *records = NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Use like: %s <csv-file>\n", argv[0]);
        return 0;
    }
    printf("Using file %s\n", argv[1]);
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Cannot open file %s\n", argv[1]);
        return 0;
    }
    // We can open the file
    dl_node_t *lista = NULL;
    int num_records = parse_file(input, &lista);
    traverse(lista);
    bubble_sort(lista);
    display(lista, 10);
    release(&lista);
    // TODO: More here

    return 0;
}