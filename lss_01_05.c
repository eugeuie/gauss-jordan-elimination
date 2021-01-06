#include "lss_01_05.h"
#include <math.h>

#define EPS 1e-20
#define not_zero(number) fabs(number) > EPS

extern int param_d, param_e;

size_t lss_memsize_01_05(int n) { return n * sizeof(double); }

int row_index_of_column_max_element(int n, double *A, const double *tmp, int k) {
    int i, row_index = -1;
    double max = 0;

    for (i = k; i < n; i++) {
        if (not_zero(fabs(get_a(A, n, tmp, i, k)) - fabs(max))) {
            max = fabs(get_a(A, n, tmp, i, k));
            row_index = i;
        }
    }

    return row_index;
}

int zero_coefficients_row(int n, double *A, const double *tmp, int k) {
    int j, zero_coefficients_row = 1;

    for (j = 0; j < n; j++) {
        if (not_zero(get_a(A, n, tmp, k, j))) {
            zero_coefficients_row = 0;
            break;
        }
    }

    return zero_coefficients_row;
}

void rows_indices_swap(double *row_indices, int first_row_index, int second_row_index) {
    double tmp = row_indices[first_row_index];
    row_indices[first_row_index] = row_indices[second_row_index];
    row_indices[second_row_index] = tmp;
}

int lss_01_05(int n, double *A, double *B, double *X, double *tmp) {
    int i, j, k, row_index;

    for (k = 0; k < n; k++) {
        row_index = row_index_of_column_max_element(n, A, tmp, k);

        if (zero_coefficients_row(n, A, tmp, k) && not_zero(get_b(B, tmp, k))) { return 1; }

        if (row_index == -1) {
            X[k] = 0;
            continue;
        }

        if (k != row_index) {
            rows_indices_swap(tmp, k, row_index);

            if (param_d) {
                printf("Row %d is swapped with row %d\n\n", k, row_index);
                print_matrix(n, A, B, tmp);
            }
        }

        get_a(B, 1, tmp, k, 0) = get_b(B, tmp, k) / get_a(A, n, tmp, k, k);
        for (j = n - 1; j >= k; j--) { get_a(A, n, tmp, k, j) = get_a(A, n, tmp, k, j) / get_a(A, n, tmp, k, k); }
        for (i = 0; i < n; i++) {
            if (i == k) { continue; }
            get_a(B, 1, tmp, i, 0) = get_b(B, tmp, i) - get_a(A, n, tmp, i, k) * get_b(B, tmp, k);
        }
        for (j = n - 1; j >= k; j--) {
            for (i = 0; i < n; i++) {
                if (i == k) { continue; }
                get_a(A, n, tmp, i, j) = get_a(A, n, tmp, i, j) - get_a(A, n, tmp, i, k) * get_a(A, n, tmp, k, j);
            }
        }

        if (param_d) { print_matrix(n, A, B, tmp); }
    }

    for (i = 0; i < n; i++) { X[i] = get_b(B, tmp, i); }

    return 0;
}
