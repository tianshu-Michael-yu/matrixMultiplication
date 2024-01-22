#include <cstddef>
#include <stdexcept>
#include <stdio.h>
#include <array>

template <typename T, size_t rows, size_t cols>
class Matrix{
    public:
        Matrix(): data() {};
        template <size_t other_cols>
        Matrix<T, rows, other_cols> operator*(const Matrix<T, cols, other_cols> &other) {
            Matrix<T, rows, other_cols> result;
            for (size_t i=0; i<rows; ++i) {
                for (size_t j=0; j<other_cols; ++j) {
                    result.setElement(i, j, 0.0);
                }
            }
            for (size_t i = 0; i < rows; ++i){
                for (size_t k = 0; k < cols; ++k ) {
                    float this_i_k = this->getElement(i, k);
                    for (size_t j= 0; j < other_cols; ++j) {
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
    private:
        std::array<T, rows*cols> data;
};