#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The define below if 0, adds some ugly code, which is faster though */
#define READABLE 1

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

int parse_file(FILE *csv_file, covid_t **records) {
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
            covid_t *tmp_records = realloc(*records, (num_records + 1) * sizeof(covid_t));
            if (tmp_records == NULL) {
                printf("Cannot allocate more memory, returning the first %d records.\n", num_records);
                return num_records;
            }
            // We were able to allocate, so set the newly allocated array to records and copy the data
            *records = tmp_records;
            // We now have 1 more record
            (*records)[num_records] = tmp_newrecord;
            num_records++;
        }
    }
    return num_records;
}

// This functiom was here to check if we read the file correctly, not used anymore
/*
void display(covid_t *records, int num_records) {
    for (int i = 0; i < num_records; i++) {
        printf("[%02d-%02d-%04d] Confirmados: %d\n",
               records[i].date.day,
               records[i].date.month,
               records[i].date.year,
               records[i].confirmados);
    }
}
*/

#if READABLE
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

#else
/*
 * The ugly version calculates the pointer offset in the covid_t struct for the wanted column.
 * Since this is the same for all the records, it can be done once.
 * Hence it is faster (you would probably notice it on millions of records only)
 */


size_t column_offset(const char *column) {
    /*
     * Since the covid_st struct starts with a date-struct, the first (total) is at offset sizeof(date_t).
     * Each next column is an integer, thus has an aditional i*sizeof(int) offset
     */
    for (int i = 0; columns[i] != NULL; i++) {
        if (strcasecmp(columns[i], column) == 0) {
            return sizeof(data_t) + i*sizeof(int);
        }
    }
    return -1;
}

// Overcomplicated code, but really short
int calc_diff(covid_t *record1, covid_t *record2, const char *column) {
    // We know the covid_t starts with a date-struct, followed by integers
    size_t offset = column_offset(column);
    if (offset < 0) {
        printf("Unknown column, using total");
        offset = 0;
    }
    // In order to be able to use an offset, we need to convert the record to a char pointer (byte pointer),
    //       (char *)record
    // then we add the offset
    //       (char *)record + offset
    // then we cast it to an integer pointer beginning at offset address
    //       (int *) ((char*)record + offset)
    // then we dereference to get the value of the integer
    //      *((int *) ((char*)record2 + offset))
    if (record1 == NULL) {
        return *((int *) ((char*)record2 + offset));
    }
    // Here we do it twice in a single line
    return *((int *) ((char*)record2 + offset)) - *((int *) ((char*)record1 + offset));
}

// Same ugly stuff as above, but we don't call the diff-function, as the offset is always the same
int peak_day(covid_t *records, int num_records, const char *column) {
    if (num_records == 0) {
        printf("No records available.\n");
        return -1;
    }
    size_t offset = column_offset(column);
    if (offset < 0) {
        printf("Unknown column.\n");
        return -1;
    }
    // We have no max value yet, so the first is the maximum value
    int peak_idx = 0;
    // So start from the second
    int peak_diff = 0;
    char *prev = NULL;
    char *curr = (char*)&(records[0]);
    for (int i = 1; i < num_records; i++) {
        prev = curr;
        curr = (char*)&(records[i]);
        int diff = *((int *) (curr + offset)) - *((int *) (prev + offset));
        if ( peak_diff < diff) {
            peak_diff = diff;
            peak_idx = i;
        }
    }
    return peak_idx;
}

#endif


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
    covid_t *data = NULL;
    int num_records = parse_file(input, &data);
    //display(data, num_records);

    for (int i = 0; columns[i] != NULL; i++) {
        int peak_day_idx = peak_day(data, num_records, columns[i]);
        peak_day_results(data, peak_day_idx, columns[i]);
    }
    release_covid_data(&data);
    return 0;
}