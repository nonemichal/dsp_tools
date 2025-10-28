#include "vector_csv.h"

#include <libgen.h>
#include <limits.h>
#include <linux/limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *get_parent_path(const char *file_path);
static char *get_csv_path(CsvMode csv_mode);
static Data_and_size get_data_from_file(FILE *fptr, char delimiter);

/* Return the absolute path to the CSV file */
char *get_full_csv_path(CsvMode csv_mode) {
    static const char *file_path = __FILE__;
    const char *parent_path = get_parent_path(file_path);
    const char *csv_path = get_csv_path(csv_mode);

    // calculate required buffer size
    // src_dir '/' + csv_path + '\0'
    size_t len =
        strnlen(parent_path, PATH_MAX) + 1 + strnlen(csv_path, PATH_MAX) + 1;
    if (len > PATH_MAX) {
        printf("Full path would exceed PATH_MAX: %d.\nReturning nullptr\n\n",
               PATH_MAX);
        return nullptr;
    }

    // allocate path buffer
    char *full_path = (char *)malloc(sizeof(char) * len);
    if (full_path == nullptr) {
        printf("Path buffer allocation failed.\nReturning nullptr\n\n");
        return nullptr;
    }

    // build full path
    snprintf(full_path, len, "%s/%s", parent_path, csv_path);
    full_path[PATH_MAX - 1] = '\0';

    printf("Full path built successfully: %s\n\n", full_path);

    return full_path;
}

/* Get a parent path based on the file path */
static char *get_parent_path(const char *file_path) {
    // make a copy of file path
    char file_copy[PATH_MAX] = {0};
    strncpy(file_copy, file_path, PATH_MAX - 1);
    file_copy[PATH_MAX - 1] = '\0';

    // get the directory of the source file
    const char *parent_string = dirname(file_copy);

    // copy parent path to a static buffer
    static char parent_path[PATH_MAX] = {0};
    strncpy(parent_path, parent_string, PATH_MAX - 1);
    parent_path[PATH_MAX - 1] = '\0';

    return parent_path;
}

/* Get a CSV file name based on the csv_mode */
static char *get_csv_path(CsvMode csv_mode) {
    const char *csv_string;
    switch (csv_mode) {
    case CSV_MODE_READ:
        csv_string = CSV_PATH_READ;
        break;
    case CSV_MODE_WRITE:
        csv_string = CSV_PATH_WRITE;
        break;
    default:
        printf("Wrong CSV mode\nReturning nullptr\n\n");
        return nullptr;
    }

    // copy csv path to a static buffer
    static char csv_path[PATH_MAX] = {0};
    strncpy(csv_path, csv_string, PATH_MAX - 1);
    csv_path[PATH_MAX - 1] = '\0';

    return csv_path;
}

/* Create a Vector_csv from the CSV file */
Vector_csv vector_csv_from_file(const char *path, char delimiter) {
    // open the CSV file in reading mode
    FILE *fptr = fopen(path, "r");

    // create an empty instance of Vector_csv
    Vector_csv vector_csv = {.data_and_size = {.data = nullptr, .size = 0},
                             .capacity = 0};

    // if file could not be opened
    if (fptr == nullptr) {
        printf("Not able to open the file: %s.\nReturning an empty vector\n\n",
               path);
        return vector_csv;
    }

    // Get data and size of it
    Data_and_size data_and_size = get_data_from_file(fptr, delimiter);

    // close file
    fclose(fptr);

    if (data_and_size.size == 0) {
        printf("Size of data is equal 0.\nReturning an empty vector\n\n");
    }

    // update an instance of Vector_csv and return it
    vector_csv.data_and_size = data_and_size;
    vector_csv.capacity = DATA_BUFFER_SIZE;

    printf("Vector created successfully\n\n");

    return vector_csv;
}

/* Get data (and size of it) from csv file */
static Data_and_size get_data_from_file(FILE *fptr, char delimiter) {
    // create an empty instance of Data_and_size
    Data_and_size data_and_size = {.data = nullptr, .size = 0};

    // allocate float buffer
    float *data = malloc(sizeof(float) * DATA_BUFFER_SIZE);
    size_t val_counter = 0;

    // if allocation failed
    if (data == nullptr) {
        printf(
            "Data buffer allocation failed.\nReturning an empty structure\n\n");
        return data_and_size;
    }

    // read values from the CSV file
    char chars_to_float[CHARS_TO_FLOAT_SIZE] = {0};
    char current_char = 0;
    size_t char_counter = 0;
    while ((current_char = (char)fgetc(fptr)) != EOF) {
        // check value counter
        if (val_counter >= DATA_BUFFER_SIZE) {
            printf("Size of value buffer cannot be geater than: "
                   "%zu.\nReturning an empty structure\n\n",
                   DATA_BUFFER_SIZE);
            free(data);
            return data_and_size;
        }

        // if value is not a delimiter
        if (current_char != delimiter) {
            // write value to a buffer
            chars_to_float[char_counter] = current_char;

            // increment char counter
            char_counter++;

            // check char counter
            if (char_counter >= CHARS_TO_FLOAT_SIZE) {
                printf("Size of char buffer cannot be greater than: "
                       "%u.\nReturning an empty structure\n\n",
                       CHARS_TO_FLOAT_SIZE);
                free(data);
                return data_and_size;
            }

        } else {
            // convert chars to a float and save
            data[val_counter] = strtof(chars_to_float, nullptr);

            // clean buffer
            for (size_t i = 0; i < char_counter; i++) {
                chars_to_float[i] = 0;
            }

            // reset char counter
            char_counter = 0;

            // increment value counter
            val_counter++;
        }
    }

    // update an instance of Data_and_size and return it
    data_and_size.data = data;
    data_and_size.size = val_counter;

    return data_and_size;
}

/* Create a CSV file from a Vector_csv */
void vector_csv_to_file(const Vector_csv *vector_csv, const char *path,
                        char delimiter) {
    // Open a CSV file in writing mode
    FILE *fptr;
    fptr = fopen(path, "w");

    // if file could not be opened
    if (fptr == nullptr) {
        printf("Not able to open the file: %s.\n\n", path);
        return;
    }

    // create a buffer for string batcher
    char batch[BATCH_SIZE] = {0};
    size_t batch_len = 0;

    // get data and size
    Data_and_size data_and_size = vector_csv->data_and_size;

    // read data from a Vector_csv
    size_t vector_size = data_and_size.size;
    for (size_t i = 0; i < vector_size; i++) {
        // calculate current batch position and length left
        char *batch_pos = batch + batch_len;
        size_t len_left = BATCH_SIZE - batch_len;

        // get data from a Vector_csv and append batch buffer
        float data = data_and_size.data[i];
        size_t bytes_written =
            (size_t)snprintf(batch_pos, len_left, "%f%c", data, delimiter);
        batch_len += bytes_written;

        //  write to a file if batch is almost empty or last iteration
        if (len_left < CHARS_TO_FLOAT_SIZE || i == (vector_size - 1)) {
            fwrite(batch, 1, batch_len, fptr);
            batch_len = 0;
        }
    }

    // Close the file
    fclose(fptr);

    printf("File written successfully\n\n");
}

/* Print content of Vector_csv */
void print_vector_csv(const Vector_csv *vector_csv) {
    // get data, size and capacity
    Data_and_size data_and_size = vector_csv->data_and_size;
    const float *data = data_and_size.data;
    size_t vector_size = data_and_size.size;
    size_t vector_capacity = vector_csv->capacity;

    printf("Vector size: %zu\nVector capacity: %zu\n\n", vector_size,
           vector_capacity);

    for (size_t i = 0; i < vector_size; i++) {
        float vector_value = data[i];
        printf("%zu: %f\n", i, vector_value);
    }

    printf("\n");
}
