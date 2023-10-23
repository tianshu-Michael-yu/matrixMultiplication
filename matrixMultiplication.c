#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

#define N 1024
const int BLOCK_SIZE = 256;
double A[N][N], B[N][N], C[N][N];


double calc_time(struct timespec start, struct timespec end) {
  double start_sec = (double)start.tv_sec*1000000000.0 + (double)start.tv_nsec;
  double end_sec = (double)end.tv_sec*1000000000.0 + (double)end.tv_nsec;

  if (end_sec < start_sec) {
    return 0;
  } else {
    return end_sec - start_sec;
  }
}

void init_array() {
    int i, j;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            A[i][j] = i+j;
            B[i][j] = i+j;
            C[i][j] = 0.0;
        }
    }
}

void multiply_ijk() {
    int i, j, k;
    double sum;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            sum = 0.0;
            for (k=0; k<N; k++) {
                sum += A[i][k]*B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

void matrix_multiply() {
    for (int i = 0; i < N; i += BLOCK_SIZE) {
        for (int j = 0; j < N; j += BLOCK_SIZE) {
            for (int k = 0; k < N; k += BLOCK_SIZE) {
                // Perform matrix multiplication for the current block
                for (int i1 = i; i1 < i + BLOCK_SIZE && i1<N; i1++) {
                    for (int j1 = j; j1 < j + BLOCK_SIZE && j1<N; j1++) {
                        for (int k1 = k; k1 < k + BLOCK_SIZE && k1<N; k1++) {
                            C[i1][j1] += A[i1][k1] * B[k1][j1];
                        }
                    }
                }
            }
        }
    }
}

void multiply_jki() {
    int i, j, k;
    double tmp;
    for (j=0; j<N; j++) {
        for (k=0; k<N; k++) {
            tmp = B[k][j];
            for (i=0; i<N; i++) {
                C[i][j] += A[i][k]*tmp;
            }
        }
    }
}

void multiply_ikj() {
    int i, j, k;
    double tmp;
    for (i=0; i<N; i++) {
        for (k=0; k<N; k++) {
            tmp = A[i][k];
            for (j=0; j<N; j++) {
                C[i][j] += tmp*B[k][j];
            }
        }
    }
}

void sum() {
    int i, j;
    double sum = 0.0;
    for (i=0; i<N; i++) {
        for (j=0; j<N; j++) {
            sum += C[i][j];
        }
    }
    printf("Sum=%f\n", sum);
}

int main(int argc, char *argv[]) {
    struct timespec start_time, end_time;
    int mod_of_multiplication = atoi(argv[1]);
    init_array();
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    if (mod_of_multiplication == 0) {
        multiply_ijk();
    } else if (mod_of_multiplication == 1) {
        multiply_jki();
    } else if (mod_of_multiplication == 2) {
        multiply_ikj();
    } else if (mod_of_multiplication == 3) {
        matrix_multiply();
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elaspe_s = calc_time(start_time, end_time)/1000000000.0;
    printf("Time=%f\n", elaspe_s);
    sum();
    return EXIT_SUCCESS;
}