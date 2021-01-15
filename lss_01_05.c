#include "lss_01_05.h"
#include <math.h>

#define EPS 1e-12

extern int param_d, param_e;

size_t lss_memsize_01_05(int n) {
    return n * sizeof(double);
}

int lss_01_05(int n, double *A, double *B, double *X, double *tmp) {
    int row, col, pivot, i, j;
    double t, *where = tmp;

    for (col = 0; col < n; ++col) {
        where[col] = -1;
    }

    for (row = 0, col = 0; row < n && col < n; ++col) {
        // Поиск главного элемента по столбцу
        pivot = row;
        for (i = row; i < n; ++i) {
            if (fabs(A[n * i + col]) > fabs(A[n * pivot + col])) {
                pivot = i;
            }
        }
        if (fabs(A[n * pivot + col]) < EPS) {
            continue;
        }

        // Перестановка строки, содержащей главный элемент по столбцу на место текущей строки
        if (pivot != row) {
            for (j = 0; j < n; ++j) {
                t = A[n * pivot + j];
                A[n * pivot + j] = A[n * row + j];
                A[n * row + j] = t;
            }
            t = B[pivot];
            B[pivot] = B[row];
            B[row] = t;

            if (param_d) {
                printf("Row %d is swapped with row %d:\n\n", row, pivot);
                print_matrix(n, A, B);
            }
        }

        // Записываем, в какой строке должна получиться переменная текущего столбца
        where[col] = row;

        // Делим строку на главный элемент
        t = A[n * row + col];
        for (j = col; j < n; ++j) {
            A[n * row + j] = A[n * row + j] / t;
        }
        B[row] = B[row] / t;

        // Прибавляем текущую строку к остальным строкам с таким коэффициентом, чтобы их коэффициенты в текущем столбце обращались в нули
        for (i = 0; i < n; ++i) {
            if (i != row) {
                t = A[n * i + col];
                for (j = col; j < n; ++j) {
                    A[n * i + j] = A[n * i + j] - t * A[n * row + j];
                }
                B[i] = B[i] - t * B[row];
            }
        }

        ++row;

        if (param_d) {
            printf("Column %d is nullified:\n\n", col);
            print_matrix(n, A, B);
        }
    }

    // Присваиваем столбец B столбцу X
    for (col = 0; col < n; ++col) {
        if (fabs(where[col] - (-1)) > EPS) {
            X[col] = B[(int) where[col]];
        } else {
            X[col] = 0;
        }
    }

    // Подстановка полученного решения в систему
    for (row = 0; row < n; ++row) {
        t = 0;
        for (col = 0; col < n; ++col) {
            t = t + X[col] * A[n * row + col];
        }
        if (fabs(t - B[row]) > EPS) {
            return 1;
        }
    }

    return 0;
}
