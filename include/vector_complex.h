#ifndef VECTOR_COMPLEX_H_
#define VECTOR_COMPLEX_H_

#include <complex.h>
#include <stddef.h>

#include "vector_csv.h"

/* struct to store complex data */
typedef struct {
    float complex *complex_data; // pointer to complex data
    size_t size;                 // size of data
} Vector_complex;

Vector_csv get_magnitude(const Vector_complex *vector_complex);
void print_complex_vector(const Vector_complex *vector_complex);

#endif // VECTOR_COMPLEX_H_
