#include "lss_01_05.h"
#include <math.h>

#define EPS 1e-20
#define not_zero(number) fabs(number) > EPS

extern int param_d, param_e;

size_t lss_memsize_01_05(int n) { return n * sizeof(double); }

int row_index_of_column_max_element(int n, double *A, int k) {
    int i, row_index = -1;
    double max = 0;

    for (i = k; i < n; i++) {
        if (not_zero(fabs(get(A, n, i, k)) - fabs(max))) {
            max = fabs(get(A, n, i, k));
            row_index = i;
        }
    }

    return row_index;
}

int zero_coefficients_row(int n, double *A, int k) {
    int j, zero_coefficients_row = 1;

    for (j = 0; j < n; j++) {
        if (not_zero(get(A, n, k, j))) {
            zero_coefficients_row = 0;
            break;
        }
    }

    return zero_coefficients_row;
}

void rows_swap(int n, double *A, double *B, int k, int row_index) {
    int j;
    double tmp;

    for (j = 0; j < n; j++) {
        tmp = get(A, n, k, j);
        get(A, n, k, j) = get(A, n, row_index, j);
        get(A, n, row_index, j) = tmp;
    }

    tmp = B[k];
    B[k] = B[row_index];
    B[row_index] = tmp;
}

int lss_01_05(int n, double *A, double *B, double *X, double *tmp) {
    int i, j, k, row_index;

    for (k = 0; k < n; k++) {
        row_index = row_index_of_column_max_element(n, A, k);

        if (zero_coefficients_row(n, A, k) && not_zero(B[k])) { return 1; }

        if (row_index == -1) {
            X[k] = 0;
            continue;
        }

        if (k != row_index) {
            rows_swap(n, A, B, k, row_index);

            if (param_d) {
                printf("Row %d is swapped with row %d\n\n", k, row_index);
                print_matrix(n, A, B);
            }
        }

        B[k] = B[k] / get(A, n, k, k);
        for (j = n - 1; j >= k; j--) { get(A, n, k, j) = get(A, n, k, j) / get(A, n, k, k); }
        for (i = 0; i < n; i++) {
            if (i == k) { continue; }
            B[i] = B[i] - get(A, n, i, k) * B[k];
        }
        for (j = n - 1; j >= k; j--) {
            for (i = 0; i < n; i++) {
                if (i == k) { continue; }
                get(A, n, i, j) = get(A, n, i, j) - get(A, n, i, k) * get(A, n, k, j);
            }
        }

        if (param_d) { print_matrix(n, A, B); }
    }

    for (i = 0; i < n; i++) { X[i] = B[i]; }

    return 0;
}
