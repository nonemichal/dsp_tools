#include "csv_parser.h"

int main(void) {
    // variables to load a CSV file
    const char *csv_path = get_full_csv_path();
    static const char delimiter = '\n';

    // load a CSV file as vector
    Vector_csv vector_csv = vector_from_file(csv_path, delimiter);

    print_vector(&vector_csv);

    return 0;
}
