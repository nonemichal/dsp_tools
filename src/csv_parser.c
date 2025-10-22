#include "csv_parser.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* Create Vector_csv from csv file */
Vector_csv vector_from_file(const char *path, const char delimiter) {
    // open CSV file
    FILE *fptr;
    fptr = fopen(path, "r");

    // create an empty instance of Vector_csv
    Vector_csv vector_csv = {.val_buffer = NULL, .size = 0, .capacity = 0};

    // if file not found
    if (fptr == NULL) {
        printf("Not able to open the file.\nReturning an empty vector");
        return vector_csv;
    }

    // allocate float buffer
    float *val_buffer = malloc(VAL_BUFFER_SIZE * sizeof(float));
    size_t val_counter = 0;

    // read values from a csv file
    char chars_to_float[CHARS_TO_FLOAT_SIZE] = {0};
    char current_char = 0;
    size_t char_counter = 0;
    while ((current_char = (char)fgetc(fptr)) != EOF) {
        // check value counter
        if (val_counter >= VAL_BUFFER_SIZE) {
            printf("Size of value buffer cannot be geater than: "
                   "%zu.\nReturning an empty vector",
                   VAL_BUFFER_SIZE);
            fclose(fptr);
            free(val_buffer);
            return vector_csv;
        }

        // if value is not delimiter
        if (current_char != delimiter) {
            // write value to a buffer
            chars_to_float[char_counter] = current_char;

            // increment char counter
            char_counter++;

            // check char counter
            if (char_counter >= CHARS_TO_FLOAT_SIZE) {
                printf("Size of char buffer cannot be geater than: "
                       "%u.\nReturning an empty vector",
                       CHARS_TO_FLOAT_SIZE);
                fclose(fptr);
                free(val_buffer);
                return vector_csv;
            }

        } else {
            // convert chars to float and save
            val_buffer[val_counter] = strtof(chars_to_float, NULL);

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
    vector_csv.val_buffer = val_buffer;
    vector_csv.size = val_counter;
    vector_csv.capacity = VAL_BUFFER_SIZE;

    return vector_csv;
}

/* Print content of Vector_csv */
void print_vector(const Vector_csv *vector_csv) {
    size_t vector_size = vector_csv->size;
    size_t vector_capacity = vector_csv->capacity;

    printf("Vector size: %zu\nVector capacity: %zu\n\n", vector_size,
           vector_capacity);

    for (size_t i = 0; i < vector_size; i++) {
        float vector_value = vector_csv->val_buffer[i];
        printf("%zu: %f\n", i, vector_value);
    }
}
