#include "csv_parser.h"

#include <libgen.h>
#include <limits.h>
#include <linux/limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Return the absolute path to signal.csv */
char *get_full_csv_path(CsvMode csv_mode) {
    // make a copy of __FILE__
    char file_path[PATH_MAX] = {0};
    strncpy(file_path, __FILE__, PATH_MAX - 1);
    file_path[PATH_MAX - 1] = '\0';

    // get the directory of the source file
    const char *src_dir = dirname(file_path);

    // get a csv_path based on the csv_mode
    static const char *csv_path;
    switch (csv_mode) {
    case CSV_MODE_READ:
        csv_path = CSV_PATH_READ;
        break;
    case CSV_MODE_WRITE:
        csv_path = CSV_PATH_WRITE;
        break;
    default:
        printf("Wrong CSV mode\nReturning NULL\n\n");
        return NULL;
    }

    // calculate required buffer size
    // src_dir '/' + csv_path + '\0'
    size_t len = strlen(src_dir) + 1 + strlen(csv_path) + 1;
    if (len > PATH_MAX) {
        printf("Full path would exceed PATH_MAX: %d.\nReturning NULL\n\n",
               PATH_MAX);
        return NULL;
    }

    // allocate path buffer
    char *full_path = malloc(len);
    if (full_path == NULL) {
        printf("Path buffer allocation failed.\nReturning NULL\n\n");
        return NULL;
    }

    // build full path
    snprintf(full_path, len, "%s/%s", src_dir, csv_path);

    printf("Full path built successfully: %s\n\n", full_path);

    return full_path;
}

/* Create a Vector_csv from a CSV file */
Vector_csv vector_from_file(const char *path, char delimiter) {
    // open a CSV file in reading mode
    FILE *fptr;
    fptr = fopen(path, "r");

    // create an empty instance of Vector_csv
    Vector_csv vector_csv = {.data_buffer = NULL, .size = 0, .capacity = 0};

    // if file could not be opened
    if (fptr == NULL) {
        printf("Not able to open the file: %s.\nReturning an empty vector\n\n",
               path);
        return vector_csv;
    }

    // allocate float buffer
    float *data_buffer = malloc(DATA_BUFFER_SIZE * sizeof(float));
    size_t val_counter = 0;

    // if allocation failed
    if (data_buffer == NULL) {
        printf(
            "Value buffer allocation failed.\nReturning an empty vector\n\n");
        fclose(fptr);
        return vector_csv;
    }

    // read values from a CSV file
    char chars_to_float[CHARS_TO_FLOAT_SIZE] = {0};
    char current_char = 0;
    size_t char_counter = 0;
    while ((current_char = (char)fgetc(fptr)) != EOF) {
        // check value counter
        if (val_counter >= DATA_BUFFER_SIZE) {
            printf("Size of value buffer cannot be geater than: "
                   "%zu.\nReturning an empty vector\n\n",
                   DATA_BUFFER_SIZE);
            fclose(fptr);
            free(data_buffer);
            return vector_csv;
        }

        // if value is not a delimiter
        if (current_char != delimiter) {
            // write value to a buffer
            chars_to_float[char_counter] = current_char;

            // increment char counter
            char_counter++;

            // check char counter
            if (char_counter >= CHARS_TO_FLOAT_SIZE) {
                printf("Size of char buffer cannot be geater than: "
                       "%u.\nReturning an empty vector\n\n",
                       CHARS_TO_FLOAT_SIZE);
                fclose(fptr);
                free(data_buffer);
                return vector_csv;
            }

        } else {
            // convert chars to a float and save
            data_buffer[val_counter] = strtof(chars_to_float, NULL);

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

    // close file
    fclose(fptr);

    // update an instance of Vector_csv and return it
    vector_csv.data_buffer = data_buffer;
    vector_csv.size = val_counter;
    vector_csv.capacity = DATA_BUFFER_SIZE;

    printf("Vector created successfully\n\n");

    return vector_csv;
}

/* Create a CSV file from a Vector_csv */
void vector_to_file(const Vector_csv *vector_csv, const char *path,
                    char delimiter) {
    // Open a CSV file in writing mode
    FILE *fptr;
    fptr = fopen(path, "w");

    // if file could not be opened
    if (fptr == NULL) {
        printf("Not able to open the file: %s.\n\n", path);
        return;
    }

    // create a buffer for string batcher
    char batch[BATCH_SIZE] = {0};
    size_t batch_len = 0;

    // read data from a Vector_csv
    size_t vector_size = vector_csv->size;
    for (size_t i = 0; i < vector_size; i++) {
        // calculate current batch position and length left
        char *batch_pos = batch + batch_len;
        size_t len_left = BATCH_SIZE - batch_len;

        // get data from a Vector_csv and append batch buffer
        float data = vector_csv->data_buffer[i];
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
void print_vector(const Vector_csv *vector_csv) {
    size_t vector_size = vector_csv->size;
    size_t vector_capacity = vector_csv->capacity;

    printf("Vector size: %zu\nVector capacity: %zu\n\n", vector_size,
           vector_capacity);

    for (size_t i = 0; i < vector_size; i++) {
        float vector_value = vector_csv->data_buffer[i];
        printf("%zu: %f\n", i, vector_value);
    }

    printf("\n");
}
