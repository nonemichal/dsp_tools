#include "csv_parser.h"

int main(void) {
    // load a CSV file
    CsvMode csv_mode = CSV_MODE_READ;
    char *csv_path = get_full_csv_path(csv_mode);
    char delimiter = '\n';
    Vector_csv vector_csv = vector_from_file(csv_path, delimiter);

    // print content of vector
    print_vector(&vector_csv);

    // save a CSV file
    csv_mode = CSV_MODE_WRITE;
    csv_path = get_full_csv_path(csv_mode);
    vector_to_file(&vector_csv, csv_path, delimiter);

    return 0;
}
