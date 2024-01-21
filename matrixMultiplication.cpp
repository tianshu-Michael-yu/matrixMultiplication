#include <cstddef>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>

class Matrix{
    public:
        const size_t rows;
        const size_t cols;
        Matrix(size_t rows, size_t cols): rows(rows), cols(cols), data(new float[rows*cols]) {};
        Matrix(const Matrix &other): rows(other.rows), cols(other.cols), data(new float[rows*cols]) {
            for (size_t i = 0; i < rows*cols; i++){
                data[i] = other.data[i];
            }
            printf("copying\n");
        };
        
        Matrix& operator=(const Matrix &other) {
            if (this == &other) return *this;
            if (rows != other.rows || cols != other.cols) {
                throw std::runtime_error("Matrix dimensions must match");
            }
            printf("copying\n");
            for (size_t i = 0; i < rows*cols; i++){
                data[i] = other.data[i];
            }
            return *this;
        };
        Matrix operator*(const Matrix &other) {
            if (cols != other.rows) {
                throw std::runtime_error("Matrix dimensions must match");
            }
            Matrix result(rows, other.cols);
            for (size_t i=0; i<rows; ++i) {
                for (size_t j=0; j<other.cols; ++j) {
                    result.setElement(i, j, 0.0);
                }
            }
            for (size_t i = 0; i < rows; ++i){
                for (size_t k = 0; k < cols; ++k ) {
                    float this_i_k = this->getElement(i, k);
                    for (size_t j= 0; j < other.cols; ++j) {
                        float result_i_j = result.getElement(i, j);
                        result_i_j += this_i_k * other.getElement(k, j);
                        result.setElement(i, j, result_i_j);
                    }
                }
            }
            return result;
        };
        float getElement(const size_t row, const size_t col) const {
            return data[row*cols + col];
        };
        void setElement(const size_t row, const size_t col, float value) {
            data[row*cols + col] = value;
        };
        ~Matrix() {
            delete[] data;
        };
    private:
        float *data;
};

void initMatrix(Matrix &mat) {
    for (size_t i = 0; i < mat.rows; ++i) {
        for (size_t j = 0; j < mat.cols; ++j) {
            mat.setElement(i, j, 0.0F);
        }
    }
}

void printMatrix(const Matrix &mat) {
    for (size_t i = 0; i < mat.rows; ++i) {
        for (size_t j = 0; j < mat.cols; ++j) {
            printf("%f ", mat.getElement(i, j));
        }
        printf("\n");
    }
}

float a[1024][1024];
float b[1024][1024];
float c[1024][1024];

void initMatrix(float mat[1024][1024]) {
    for (size_t i = 0; i < 1024; ++i) {
        for (size_t j = 0; j < 1024; ++j) {
            mat[i][j] = 0.0F;
        }
    }
}

void multiply_ikj() {
    for (size_t i=0; i<1024; ++i) {
        for (size_t k=0; k<1024; ++k) {
            float a_i_k = a[i][k];
            for (size_t j=0; j<1024; ++j) {
                c[i][j] += a_i_k * b[k][j];
            }
        }
    }
}

int main(void) {
    Matrix A(1024, 1024);
    Matrix B(1024, 1024);
    initMatrix(A);
    initMatrix(B);

    auto start = std::chrono::high_resolution_clock::now();
    Matrix C = A * B;
    auto end = std::chrono::high_resolution_clock::now();

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