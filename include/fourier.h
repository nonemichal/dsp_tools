#ifndef FOURIER_H_
#define FOURIER_H_

#include <complex.h>

#include "vector_complex.h"
#include "vector_csv.h"

Vector_complex dft_from_vector(const Vector_csv *vector_csv);

#endif // FOURIER_H_
