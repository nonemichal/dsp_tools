#include "csv_parser.h"

int main(void) {
    // variables to load a csv file
    static const char *csv_path = DEFAULT_CSV_PATH;
    static const char delimiter = '\n';

    Vector_csv vector_csv = vector_from_file(csv_path, delimiter);

    print_vector(&vector_csv);

    return 0;
}
