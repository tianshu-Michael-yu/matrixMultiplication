#include <cstddef>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
    Matrix A(2, 3);
    Matrix B(3, 2);
    A.setElement(0, 0, 1.0);
    A.setElement(0, 1, 2.0);
    A.setElement(0, 2, 3.0);
    A.setElement(1, 0, 4.0);
    A.setElement(1, 1, 5.0);
    A.setElement(1, 2, 6.0);

    B.setElement(0, 0, 7.0);
    B.setElement(0, 1, 8.0);
    B.setElement(1, 0, 9.0);
    B.setElement(1, 1, 10.0);
    B.setElement(2, 0, 11.0);
    B.setElement(2, 1, 12.0);
    Matrix C = A * B;
    for (size_t i = 0; i < C.rows; ++i) {
        for (size_t j = 0; j < C.cols; ++j) {
            printf("%f ", C.getElement(i, j));
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}