// 5. Gauss-Jordan Elimination with pivot selection by column

#include "lss_01_05.h"
#include <time.h>

#define DEFAULT_INPUT_FILENAME "lss_01_05_in.txt"
#define DEFAULT_OUTPUT_FILENAME "lss_01_05_out.txt"

int param_d = 0, // print debug messages
    param_e = 0, // print errors
    param_p = 0, // print matrix
    param_t = 0, // print execution time
    param_h = 0; // print help

void exception(int code, const char *message) {
    /*
     * 2 - Error: Wrong syntax of parameters. There is no such parameter
     * 3 - Error: Wrong syntax of parameters. Too much filenames
     * 4 - Error: Wrong order of parameters
     * 5 - Error: There is no such file
     * 6 - Error: File is empty
     * 7 - Error: n is not a positive integer
     * 8 - Error: Not enough elements in the matrix
     * 9 - Error: One of the elements of the matrix is not a number or n is not a positive integer
     */
    if (param_e) { printf("%s\n", message); }
    exit(code);
}

void print_help() {
    printf("Usage: lss [input_file_name] [output_file_name] [options]\n"
           "Where options include:\n"
           "   -d        print debug messages [default OFF]\n"
           "   -e        print errors [default OFF]\n"
           "   -p        print matrix [default OFF]\n"
           "   -t        print execution time [default OFF]\n"
           "   -h, -?    print this and exit\n"
           "Default input_file_name value is lss_01_05_in.txt, default output_file_name value is lss_01_05_out.txt\n");
}

void print_matrix(int n, double *A, double *B) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) { printf("%1.9lf\t", get(A, n, i, j)); }
        printf("\t\t%1.9lf\n", B[i]);
    }
    printf("\n");
}

void output(const char *output_filename, int result, int n, const double *X) {
    int i;
    FILE *output_file = fopen(output_filename, "w");
    if (result != 0) { fprintf(output_file, "%d\n", 0); } else {
        fprintf(output_file, "%d\n", n);
        for (i = 0; i < n; i++) { fprintf(output_file, "%1.9lf\n", X[i]); }
    }
}

int string_length(const char *string) {
    int length;
    for (length = 0; string[length] != '\0'; length++);
    return length;
}

int file_exists(const char *filename) { return fopen(filename, "r") != NULL; }

void validate_params(int argc, char *argv[], char **input_filename, char **output_filename) {
    int i, filenames_count = 0, input_filename_set = 0;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (string_length(argv[i]) == 2) {
                switch (argv[i][1]) {
                    case 'd': {
                        param_d = 1;
                        break;
                    }
                    case 'e': {
                        param_e = 1;
                        break;
                    }
                    case 'p': {
                        param_p = 1;
                        break;
                    }
                    case 't': {
                        param_t = 1;
                        break;
                    }
                    case 'h': case '?': {
                        param_h = 1;
                        break;
                    }
                    default: {
                        exception(2, "Error: Wrong syntax of parameters. There is no such parameter");
                    }
                }
            } else { exception(2, "Error: Wrong syntax of parameters. There is no such parameter"); }
        } else { filenames_count++; }
    }

    if (filenames_count > 2) { exception(3, "Error: Wrong syntax of parameters. Too much filenames"); }

    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            if (!input_filename_set) {
                if (i != 1) { exception(4, "Error: Wrong order of parameters"); }
                *input_filename = argv[i];
                if (!file_exists(*input_filename)) { exception(5, "Error: There is no such file"); }
                input_filename_set = 1;
            } else {
                if (i != 2) { exception(4, "Error: Wrong order of parameters");  }
                *output_filename = argv[i];
            }
        }
    }

    if (!input_filename_set) {
        if (!file_exists(*input_filename)) { exception(5, "Error: There is no such file"); }
    }
}

void input(const char *input_filename, double **A, double **B, int *n) {
    int i, check_input;
    FILE *input_file = fopen(input_filename, "r");

    check_input = fscanf(input_file, "%d", n);
    if (check_input == EOF) { exception(6, "Error: File is empty"); }

    if (check_input == 0 || *n <= 0) { exception(7, "Error: n is not a positive integer"); }

    *A = malloc((*n) * (*n) * sizeof(double));
    *B = malloc((*n) * sizeof(double));

    for (i = 0; i < (*n) * (*n); i++) {
        check_input = fscanf(input_file, "%lf", &(*A)[i]);
        if (check_input == EOF) { exception(8, "Error: Not enough elements in the matrix"); }
        if (check_input == 0) {
            exception(9,
                      "Error: One of the elements of the matrix is not a number or n is not a positive integer");
        }
    }

    for (i = 0; i < (*n); i++) {
        check_input = fscanf(input_file, "%lf", &(*B)[i]);
        if (check_input == EOF) { exception(8, "Error: Not enough elements in the matrix"); }
        if (check_input == 0) {
            exception(9,
                      "Error: One of the elements of the matrix is not a number or n is not a positive integer");
        }
    }
}

int main(int argc, char *argv[]) {
    int n = 0, result;
    double *A, *B, *X, *tmp;
    char *input_filename = DEFAULT_INPUT_FILENAME,
         *output_filename = DEFAULT_OUTPUT_FILENAME;

    validate_params(argc, argv, &input_filename, &output_filename);

    if (param_h) {
        print_help();
        return 0;
    }

    input(input_filename, &A, &B, &n);

    tmp = malloc(lss_memsize_01_05(n));
    X = malloc(n * sizeof(double));

    if (param_p) { print_matrix(n, A, B); }

    clock_t begin = clock();
    result = lss_01_05(n, A, B, X, tmp);
    clock_t end = clock();

    if (param_p) { print_matrix(n, A, B); }

    if (param_d) {
        switch (result) {
            case -1:
                printf("Success: The solution method is not applicable to this system\n"); //TODO Is it Success?
                break;
            case 0:
                printf("Success: Solution built\n");
                break;
            case 1:
                printf("Success: Solution for this system does not exist\n");
                break;
            default:
                break;
        }
    }

    double execution_time = (double) (end - begin) / CLOCKS_PER_SEC;

    if (param_t) { printf("Execution time: %1.9lf\n", execution_time); }

    output(output_filename, result, n, X);

    free(A);
    free(B);
    free(X);
    free(tmp);

    return result;
}
