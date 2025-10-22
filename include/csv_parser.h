#ifndef CSV_PARSER_H_
#define CSV_PARSER_H_

#include <stddef.h>

#define DATA_BUFFER_SIZE 10000L // max size of a value buffer
#define CHARS_TO_FLOAT_SIZE 64U // max size of chars to store one float
#define CSV_PATH_READ                                                          \
    "../csv_files/signal.csv" // path to the CSV file that will be read
#define CSV_PATH_WRITE                                                         \
    "../csv_files/out.csv" // path to the CSV file that will be written
#define BATCH_SIZE 1024    // batch size to store string and write it to a file

/* enum defining whether the CSV file should be read or written */
typedef enum { CSV_MODE_READ, CSV_MODE_WRITE } CsvMode;

/* struct to store numbers from a CSV file */
typedef struct {
    float *data_buffer; // pointer to array of floats
    size_t size;        // number of floats currently stored
    size_t capacity;    // total capacity of the data_buffer
} Vector_csv;

char *get_full_csv_path(CsvMode csv_mode);
Vector_csv vector_from_file(const char *path, char delimiter);
void vector_to_file(const Vector_csv *vector_csv, const char *path,
                    char delimiter);
void print_vector(const Vector_csv *vector_csv);

#endif // CSV_PARSER_H_
