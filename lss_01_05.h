#ifndef GAUSS_JORDAN_ELIMINATION_LSS_01_05_H
#define GAUSS_JORDAN_ELIMINATION_LSS_01_05_H

#include <stdio.h>
#include <stdlib.h>

#define get_a(A, n, tmp, i, j) A[(int) (tmp)[(i)] * (n) + (j)]
#define get_b(B, tmp, i) B[(int) (tmp)[(i)]]

size_t lss_memsize_01_05(int n);

void print_matrix(int n, double *A, double *B, const double *tmp);

int lss_01_05(int n, double *A, double *B, double *X, double *tmp);

#endif //GAUSS_JORDAN_ELIMINATION_LSS_01_05_H
