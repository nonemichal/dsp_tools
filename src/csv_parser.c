#include "csv_parser.h"
#include <stddef.h>
#include <stdio.h>

int *load_csv(const char *path, const char d) {
    // read file
    FILE *fptr;
    fptr = fopen(path, "r");

    // if file not found
    if (fptr == NULL) {
        printf("Not able to open the file.");
    }

    // seek to the end of the file
    fseek(fptr, 0L, SEEK_END);
    size_t file_size = (size_t)ftell(fptr);

    // seek back
    fseek(fptr, 0L, SEEK_SET);



    // close the file
    fclose(fptr);
}
