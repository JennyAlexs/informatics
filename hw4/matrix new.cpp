#include <iostream>
#include <vector>
#include <memory>

template <typename T, size_t Rows, size_t Cols>
class Matrix {
private:
    std::vector<T> m_data;

public:
    Matrix() : m_data(Rows * Cols) {}
 Matrix(const std::initializer_list<std::initializer_list<T>>& values) : Matrix() {
        size_t i = 0;
        for (auto& row : values) {
            size_t j = 0;
            for (auto& value : row) {
                (*this)(i, j) = value;
                ++j;
            }
            ++i;
        }
    }

    Matrix(const Matrix& other) : m_data(other.m_data) {}

    Matrix(Matrix&& other) : m_data(std::move(other.m_data)) {}

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            m_data = other.m_data;
        }
        return *this;
    }

    Matrix& operator=(Matrix&& other) {
        if (this != &other) {
            m_data = std::move(other.m_data);
        }
        return *this;
    }

    Matrix operator+(const Matrix& other) const
    {
        if (Rows != other.Rows || Cols != other.Cols)
            throw std::runtime_error("Matrix dimensions do not match");
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i)
            for (size_t j = 0; j < Cols; ++j)
                result(i, j) = (*this)(i, j) + other(i, j);
        return result;
    }

    Matrix operator-(const Matrix& other) const
    {
        if (Rows != other.Rows || Cols != other.Cols)
            throw std::runtime_error("Matrix dimensions do not match");
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i)
            for (size_t j = 0; j < Cols; ++j)
                result(i, j) = (*this)(i, j) - other(i, j);
        return result;
    }
    template <size_t otherCols>
    Matrix<T, Rows, otherCols> operator*(const Matrix<T, Cols, otherCols>& other) const
    {
        Matrix<T, Rows, otherCols> result;
        for (size_t i = 0; i < Rows; ++i)
            for (size_t j = 0; j < otherCols; ++j)
                for (size_t k = 0; k < Cols; ++k)
                    result(i, j) += (*this)(i, k) * other(k, j);
        return result;
    }

    T& operator()(size_t i, size_t j)
    {
        return m_data[i * Cols + j];
    }

    const T& operator()(size_t i, size_t j) const
    {
        return m_data[i * Cols + j];
    }

    size_t rows() const
    {
        return Rows;
    }

    size_t cols() const
    {
        return Cols;
    }
};

template <typename T, size_t Rows, size_t Cols>
Matrix<T, Cols, Rows> transpose(Matrix<T, Rows, Cols>&& matrix)
{
    Matrix<T, Cols, Rows> result;
    for (size_t i = 0; i < Rows; ++i)
        for (size_t j = 0; j < Cols; ++j)
            result(j, i) = matrix(i, j);
    return result;
}

int main()
{
    Matrix<int, 2, 3> A{ {1, 2, 3}, {4, 5, 6} };
    Matrix<int, 3, 2> B{ {7, 8}, {9, 10}, {11, 12} };

    Matrix<int, 2, 2> C = A * B;
    Matrix<int, 3, 2> D = transpose(std::move(A));

    std::cout << "Matrix A:\n";
    for (size_t i = 0; i < A.rows(); ++i)
    {
        for (size_t j = 0; j < A.cols(); ++j)
            std::cout << A(i, j) << " ";
        std::cout << "\n";
    }

    std::cout << "Matrix B:\n";
    for (size_t i = 0; i < B.rows(); ++i)
    {
        for (size_t j = 0; j < B.cols(); ++j)
            std::cout << B(i, j) << " ";
        std::cout << "\n";
    }
    
        std::cout << "Matrix C = A * B:\n";
    for (size_t i = 0; i < C.rows(); ++i)
    {
        for (size_t j = 0; j < C.cols(); ++j)
            std::cout << C(i, j) << " ";
        std::cout << "\n";
        
    }
        std::cout << "Matrix D = transpose(A):\n";
        for (size_t i = 0; i < D.rows(); ++i)
        {
            for (size_t j = 0; j < D.cols(); ++j)
                std::cout << D(i, j) << " ";
            std::cout << "\n";
        }
    return 0;
    
}
