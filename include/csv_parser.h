#ifndef CSV_PARSER_H_
#define CSV_PARSER_H_

#include <stddef.h>

#define VAL_BUFFER_SIZE 10000L  // max size of value buffer
#define CHARS_TO_FLOAT_SIZE 32U // max size of chars to store one float
#define DEFAULT_CSV_PATH "../csv_files/signal.csv" // default path of csv file

/* struct to store numbers from csv file */
typedef struct {
    float *val_buffer; // pointer to array of floats
    size_t size;       // number of floats currently stored
    size_t capacity;   // total capacity of val_buffer
} Vector_csv;

Vector_csv vector_from_file(const char *path, const char delimiter);
void print_vector(const Vector_csv *vector_csv);

#endif // CSV_PARSER_H_
