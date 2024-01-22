#include "matrixMultiplication.h"
#include <stdlib.h>
#include <chrono>
#include <iostream>

template <typename T, size_t rows, size_t cols>
void initMatrix(Matrix<T, rows, cols> &mat) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            mat.setElement(i, j, 0.0F);
        }
    }
}

template <typename T, size_t rows, size_t cols>
void printMatrix(const Matrix<T, rows, cols> &mat) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            printf("%f ", mat.getElement(i, j));
        }
        printf("\n");
    }
}

constexpr size_t N = 512;
float a[N][N];
float b[N][N];
float c[N][N];

void initMatrix(float mat[N][N]) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            mat[i][j] = 0.0F;
        }
    }
}

void multiply_ikj() {
    for (size_t i=0; i<N; ++i) {
        for (size_t k=0; k<N; ++k) {
            float a_i_k = a[i][k];
            for (size_t j=0; j<N; ++j) {
                c[i][j] += a_i_k * b[k][j];
            }
        }
    }
}


int main(void) {
    Matrix<float, N, N> A;
    Matrix<float, N, N> B;
    initMatrix(A);
    initMatrix(B);

    auto start = std::chrono::high_resolution_clock::now();
    Matrix C = A * B;
    auto end = std::chrono::high_resolution_clock::now();
    //printMatrix(C);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j){
            if (C.getElement(i, j) != 0.0F) {
                printf("Error at (%ld, %ld): %f != %f\n", i, j, C.getElement(i, j), 0.0F);
                return EXIT_FAILURE;
            }
        }
    }

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    initMatrix(a);
    initMatrix(b);
    initMatrix(c);
    auto start2 = std::chrono::high_resolution_clock::now();
    multiply_ikj();
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;
    std::cout << "Elapsed time: " << elapsed2.count() << " s\n";

    return EXIT_SUCCESS;

}