#include <stdio.h>

#include "csv_parser.h"

int main() {
    char delimiter = '\n';
    Vector_csv vector_csv = vector_from_file(CSV_PATH, delimiter);

    print_vector(&vector_csv);

    return 0;
}
