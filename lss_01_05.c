#include "lss_01_05.h"
#include <math.h>

extern int param_d, param_e;
const double EPS = 1e-25;

size_t lss_memsize_01_05(int n) { return n * sizeof(double); }

int row_index_of_column_max_element(int n, double *A, int k) {
    int i = 0, row_index = -1;
    double max = 0;

    for (i = k; i < n; i++) {
        if (fabs(A[i * n + k]) - fabs(max) > EPS) {
            max = fabs(A[i * n + k]);
            row_index = i;
        }
    }

    return row_index;
}

void rows_swap(int n, double *A, double *B, int k, int row_index) {
    int j = 0;
    double tmp;

    for (j = 0; j < n; j++) {
        tmp = A[k * n + j];
        A[k * n + j] = A[row_index * n + j];
        A[row_index * n + j] = tmp;
    }

    tmp = B[k];
    B[k] = B[row_index];
    B[row_index] = tmp;
}

int lss_01_05(int n, double *A, double *B, double *X, double *tmp) {
    int i, j, k, row_index;

    for (k = 0; k < n; k++) {
        row_index = row_index_of_column_max_element(n, A, k);

        if (row_index == -1) {
            if (fabs(B[k]) > EPS) {
                if (param_d) {
                    printf("System has no solution\n");
                }
                return 1;
            }
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

        B[k] = B[k] / A[k * n + k];
        for (j = n - 1; j >= k; j--) {
            A[k * n + j] = A[k * n + j] / A[k * n + k];
        }
        for (i = 0; i < n; i++) {
            if (i == k) { continue; }
            B[i] = B[i] - A[i * n + k] * B[k];
        }
        for (j = n - 1; j >= k; j--) {
            for (i = 0; i < n; i++) {
                if (i == k) { continue; }
                A[i * n + j] = A[i * n + j] - A[i * n + k] * A[k * n + j];
            }
        }

        if (param_d) {
            print_matrix(n, A, B);
        }
    }

    for (i = 0; i < n; i++) {
        X[i] = B[i];
    }

    return 0;
}
