#include "vector_complex.h"

#include <complex.h>
#include <stdlib.h>

#include "vector_csv.h"

Vector_csv get_magnitude(const Vector_complex *vector_complex) {
    const float complex *complex_data = vector_complex->complex_data;
    const size_t size = vector_complex->size;

    float *data = (float *)malloc(sizeof(float) * size);
    if (data == nullptr) {
        printf("Data buffer allocation failed\n");
    }

    for (size_t i = 0; i < size; i++) {
        data[i] = cabsf(complex_data[i]);
    }

    Data_and_size data_and_size = {.data = data, .size = size};
    Vector_csv vector_csv = {.data_and_size = data_and_size, .capacity = size};

    return vector_csv;
}
void print_complex_vector(const Vector_complex *vector_complex) {}
