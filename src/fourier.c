#include "fourier.h"

#include <complex.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include "vector_complex.h"
#include "vector_csv.h"

/* Calculate Discrete Fourier Transform based on Vector_csv */
Vector_complex dft_from_vector(const Vector_csv *vector_csv) {
    // get data and size from Vector_csv
    const Data_and_size data_and_size = vector_csv->data_and_size;
    const float *data = data_and_size.data;
    const size_t size = data_and_size.size;

    // create an empty instance of Vector_complex
    Vector_complex vector_complex = {.complex_data = nullptr, .size = 0};

    // check passed Vector_csv
    if (data == nullptr) {
        printf("Vector data must not point to null\nReturning an empty complex "
               "vector\n\n");
        return vector_complex;
    }
    if (size == 0) {
        printf(
            "Vector must not be empty\nReturning an empty complex vector\n\n");
        return vector_complex;
    }

    // allocate memory for complex data buffer
    float complex *complex_data =
        (float complex *)malloc(sizeof(float complex) * size);
    if (complex_data == nullptr) {
        printf("Complex data allocation failed\nReturning an empty complex "
               "vector\n\n");
        return vector_complex;
    }

    // constant value in every iteration
    const float size_float = (float)size;
    const float complex const_value =
        (float complex)(-1 * I * 2 * M_PI / size_float);

    // calculate Discrete Fourier Transform
    for (size_t i = 0; i < size; i++) {
        complex_data[i] = 0;

        for (size_t j = 0; j < size; j++) {
            const float i_float = (float)i;
            const float j_float = (float)j;
            complex_data[i] += data[j] * cexpf(const_value * i_float * j_float);
        }
    }

    // update Vector_complex
    vector_complex.complex_data = complex_data;
    vector_complex.size = size;

    return vector_complex;
}
