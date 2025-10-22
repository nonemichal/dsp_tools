#ifndef CSV_PARSER_H_
#define CSV_PARSER_H_

#include <stddef.h>

#define VAL_BUFFER_SIZE 10000L  // max size of a value buffer
#define CHARS_TO_FLOAT_SIZE 32U // max size of chars to store one float
#define CSV_PATH_TEMPLATE                                                      \
    "../csv_files/signal.csv" // template path to the CSV file

/* struct to store numbers from a CSV file */
typedef struct {
    float *val_buffer; // pointer to array of floats
    size_t size;       // number of floats currently stored
    size_t capacity;   // total capacity of the val_buffer
} Vector_csv;

char *get_full_csv_path(void);
Vector_csv vector_from_file(const char *path, const char delimiter);
void print_vector(const Vector_csv *vector_csv);

#endif // CSV_PARSER_H_
