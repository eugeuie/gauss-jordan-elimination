#ifndef GAUSS_JORDAN_ELIMINATION_LSS_01_05_H
#define GAUSS_JORDAN_ELIMINATION_LSS_01_05_H

#include <stdio.h>
#include <stdlib.h>

size_t lss_memsize_01_05(int n);

void print_matrix(int n, double *A, double *B);

int lss_01_05(int n, double *A, double *B, double *X, double *tmp);

#endif //GAUSS_JORDAN_ELIMINATION_LSS_01_05_H
