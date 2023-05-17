#include <iostream>
#include <vector>
#include <memory>

template <typename T>
class Matrix
{
private:
    size_t m_rows;
    size_t m_cols;
    std::unique_ptr<std::vector<T>> m_data;
public:
    Matrix() : m_rows(0), m_cols(0) {}
    Matrix(size_t rows, size_t cols) : m_rows(rows), m_cols(cols), m_data(std::make_unique<std::vector<T>>(rows * cols)) {}
    Matrix(const Matrix& other) : m_rows(other.m_rows), m_cols(other.m_cols), m_data(std::make_unique<std::vector<T>>(*other.m_data)) {}
    Matrix(Matrix&& other) : m_rows(other.m_rows), m_cols(other.m_cols), m_data(std::move(other.m_data)) {}

    Matrix& operator=(const Matrix& other)
    {
        if (&other == this) return *this;
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = std::make_unique<std::vector<T>>(*other.m_data);
        return *this;
    }

    Matrix& operator=(Matrix&& other)
    {
        if (&other == this) return *this;
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = std::move(other.m_data);
        return *this;
    }

    Matrix operator+(const Matrix& other) const
    {
        if (m_rows != other.m_rows || m_cols != other.m_cols)
            throw std::runtime_error("Matrix dimensions do not match");
        Matrix result(m_rows, m_cols);
        for (size_t i = 0; i < m_rows; ++i)
            for (size_t j = 0; j < m_cols; ++j)
                result(i, j) = (*this)(i, j) + other(i, j);
        return result;
    }

    Matrix operator-(const Matrix& other) const
    {
        if (m_rows != other.m_rows || m_cols != other.m_cols)
            throw std::runtime_error("Matrix dimensions do not match");
        Matrix result(m_rows, m_cols);
        for (size_t i = 0; i < m_rows; ++i)
            for (size_t j = 0; j < m_cols; ++j)
                result(i, j) = (*this)(i, j) - other(i, j);
        return result;
    }

    Matrix operator*(const Matrix& other) const
    {
        if (m_cols != other.m_rows)
            throw std::runtime_error("Matrix dimensions do not match");
        Matrix result(m_rows, other.m_cols);
        for (size_t i = 0; i < m_rows; ++i)
            for (size_t j = 0; j < other.m_cols; ++j)
                for (size_t k = 0; k < m_cols; ++k)
                    result(i, j) += (*this)(i, k) * other(k, j);
        return result;
    }

    T& operator()(size_t i, size_t j)
    {
        return (*m_data)[i * m_cols + j];
    }

    const T& operator()(size_t i, size_t j) const
    {
        return (*m_data)[i * m_cols + j];
    }

    size_t rows() const
    {
        return m_rows;
    }

    size_t cols() const
    {
        return m_cols;
    }
};

template <typename T>
Matrix<T> transpose(Matrix<T>&& matrix)
{
    Matrix<T> result(matrix.cols(), matrix.rows());
    for (size_t i = 0; i < matrix.rows(); ++i)
        for (size_t j = 0; j < matrix.cols(); ++j)
            result(j, i) = matrix(i, j);
    return result;
}

int main()
{
    Matrix<int> A(2, 3);
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    Matrix<int> B(3, 2);
    B(0, 0) = 7; B(0, 1) = 8;
    B(1, 0) = 9; B(1, 1) = 10;
    B(2, 0) = 11; B(2, 1) = 12;

    Matrix<int> C = A * B;
    Matrix<int> D = transpose(std::move(A)); // используем move-семантику для передачи матрицы по универсальной ссылке

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
