#include <iostream>
#include <vector>
#include <memory>

template<typename T, unsigned m_rows, unsigned m_cols>
class Matrix {
private:
    std::unique_ptr<std::vector<T>> m_data;

public:

    Matrix(){
        m_data = std::unique_ptr<std::vector<T>>(new std::vector<T>(m_rows * m_cols));
    }

    Matrix(const Matrix& other){
        m_data = std::unique_ptr<std::vector<T>>(new std::vector<T>(*other.m_data));
    }

    Matrix(Matrix&& other){
        m_data = std::move(other.m_data);
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            m_data = std::unique_ptr<std::vector<T>>(new std::vector<T>(*other.m_data));
        }
        return *this;
    }

    Matrix& operator=(Matrix&& other) {
        if (this != &other) {
            m_data = std::move(other.m_data);
        }
        return *this;
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

template<typename T, unsigned m_rows, unsigned m_cols>
Matrix<T, m_rows, m_cols> operator+(const Matrix<T, m_rows, m_cols> self, const Matrix<T, m_rows, m_cols>& other)
{
    Matrix<T, m_rows, m_cols> result;
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            result(i, j) = self(i, j) + other(i, j);
    return result;
}

template<typename T, unsigned m_rows, unsigned m_cols>
Matrix<T, m_rows, m_cols> operator-(const Matrix<T, m_rows, m_cols> self, const Matrix<T, m_rows, m_cols>& other)
{
    Matrix<T, m_rows, m_cols> result;
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            result(i, j) = self(i, j) - other(i, j);
    return result;
}


template<typename T, unsigned L, unsigned M, unsigned R>
Matrix<T, L, R> operator*(const Matrix<T, L, M> self, const Matrix<T, M, R>& other)
{
    Matrix<T, L, R> result;
    for (size_t i = 0; i < L; ++i)
        for (size_t j = 0; j < R; ++j)
            for (size_t k = 0; k < M; ++k)
                result(i, j) += self(i, k) * other(k, j);
    return result;
}

    


template<typename T, unsigned m_rows, unsigned m_cols>
Matrix<T, m_cols, m_rows> transpose(Matrix<T, m_rows, m_cols>&& matrix)
{
    Matrix<T, m_cols, m_rows> result;
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            result(j, i) = matrix(i, j);
    return result;
}

int main()
{
    Matrix<int, 2, 3> A;
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    Matrix<int, 3, 2> B;
    B(0, 0) = 7; B(0, 1) = 8;
    B(1, 0) = 9; B(1, 1) = 10;
    B(2, 0) = 11; B(2, 1) = 12;

    Matrix<int, 2, 2> C = A * B;
    Matrix<int, 3, 2> D = transpose(std::move(A)); // используем move-семантику для передачи матрицы по универсальной ссылке

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
