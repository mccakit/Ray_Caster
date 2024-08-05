#pragma once

#include "c_with_classes.h"

struct Vector
{
    arr<flt> elements{};

    Vector(const arr<flt>& data):
        elements{data}
    {
    }
    Vector(const init_list<flt>& data):
    elements{data}
    {
    }
    double& operator ()(const int& index)
    {
        return elements[index];
    }

    double operator ()(const int& index) const
    {
        return elements[index];
    }

    int size() const
    {
        return elements.size();
    }
};

out& operator <<(out& out, const Vector& vec)
{
    for (int index{0}; index < vec.size(); ++index)
    {
        out << vec(index) << "\n";
    }
    return out;
}

Vector operator *(const Vector& ls_vector, const double& rs_factor)
{
    Vector result{ls_vector};
    for (int index{0}; index < ls_vector.size(); ++index)
    {
        result(index) *= rs_factor;
    }
    return result;
}

Vector operator *(const flt& ls_factor, const Vector& rs_vector)
{
    Vector result{rs_vector};
    for (int index{0}; index < rs_vector.size(); ++index)
    {
        result(index) *= ls_factor;
    }
    return result;
}

void operator *=(Vector& ls_vector, const flt& rs_factor)
{
    for (int index{0}; index < ls_vector.size(); ++index)
    {
        ls_vector(index) *= rs_factor;
    }
}

Vector operator +(const Vector& ls_vector, const Vector& rs_vector)
{
    Vector result = ls_vector;
    for (int index{0}; index < ls_vector.size(); ++index)
    {
        result(index) += rs_vector(index);
    }
    return result;
}

void operator +=(Vector& ls_vector, const Vector& rs_vector)
{
    for (int index{0}; index < ls_vector.size(); ++index)
    {
        ls_vector(index) += rs_vector(index);
    }
}

Vector operator -(const Vector& ls_vector, const Vector& rs_vector)
{
    Vector result{ls_vector};
    for (int index{0}; index < ls_vector.size(); ++index)
    {
        result(index) -= rs_vector(index);
    }
    return result;
}

void operator -=(Vector& ls_vector, const Vector& rs_vector)
{
    for (int index{0}; index < ls_vector.size(); ++index)
    {
        ls_vector(index) -= rs_vector(index);
    }
}

flt dotproduct(const Vector& vec1, const Vector& vec2)
{
    flt sum{};
    for (int i {0}; i < vec1.size(); ++i)
    {
        sum+= vec1(i) * vec2(i);
    }
    return sum;
}

template<typename... Args>
Vector point(Args... args)
{
    arr<flt> arr{cast<flt>(args)...};
    arr.append(1);
    return arr;
}
struct Matrix
{
    arr<Vector> vectors{};

    Matrix(const arr<Vector>& data):
        vectors{data}
    {
    }
    Matrix(const init_list<Vector>& data):
    vectors{data}
    {
    }
    Matrix(const int size):
        vectors{arr<Vector>(size, arr<double>(size))}
    {
    }

    flt& operator ()(const int row, const int col)
    {
        return vectors[col](row);
    }

    flt operator ()(const int row, const int col) const
    {
        return vectors[col](row);
    }

    Vector& operator ()(const int col)
    {
        return vectors[col];
    }

    Vector operator ()(const int col) const
    {
        return vectors[col];
    }

    int size() const
    {
        return vectors.size();
    }
};

out& operator <<(out& out, const Matrix& matrix)
{
    const int matrix_size{matrix.size()};
    for (int row{0}; row < matrix_size; ++row)
    {
        for (int col{0}; col < matrix_size; ++col)
        {
            out << matrix(row, col) << " ";
        }
        out << "\n";
    }
    return out;
}

Matrix operator *(Matrix ls_matrix, const flt& rs_factor)
{
    for (int i{0}; i < ls_matrix.size(); ++i)
    {
        ls_matrix(i) *= rs_factor;
    }
    return ls_matrix;
}

Matrix operator *(const flt& ls_factor, Matrix rs_matrix)
{
    for (int i{0}; i < rs_matrix.size(); ++i)
    {
        rs_matrix(i) *= ls_factor;
    }
    return rs_matrix;
}

void operator *=(Matrix& ls_matrix, const double& rs_factor)
{
    for (int i{0}; i < ls_matrix.size(); ++i)
    {
        ls_matrix(i) *= rs_factor;
    }
}

Matrix operator +(Matrix ls_matrix, const Matrix& rs_matrix)
{
    const int matrix_size{ls_matrix.size()};
    for (int row{0}; row < matrix_size; ++row)
    {
        for (int col{0}; col < matrix_size; ++col)
        {
            ls_matrix(row, col) += rs_matrix(row, col);
        }
    }
    return ls_matrix;
}

void operator +=(Matrix& ls_matrix, const Matrix& rs_matrix)
{
    const int matrix_size{ls_matrix.size()};
    for (int row{0}; row < matrix_size; ++row)
    {
        for (int col{0}; col < matrix_size; ++col)
        {
            ls_matrix(row, col) += rs_matrix(row, col);
        }
    }
}

Matrix operator -(Matrix ls_matrix, const Matrix& rs_matrix)
{
    const int matrix_size{ls_matrix.size()};
    for (int row{0}; row < matrix_size; ++row)
    {
        for (int col{0}; col < matrix_size; ++col)
        {
            ls_matrix(row, col) -= rs_matrix(row, col);
        }
    }
    return ls_matrix;
}

void operator -=(Matrix& ls_matrix, const Matrix& rs_matrix)
{
    const int matrix_size{ls_matrix.size()};
    for (int row{0}; row < matrix_size; ++row)
    {
        for (int col{0}; col < matrix_size; ++col)
        {
            ls_matrix(row, col) -= rs_matrix(row, col);
        }
    }
}

Vector operator *(const Matrix& ls_matrix, const Vector& rs_vector)
{
    const int vector_size{rs_vector.size()};
    Vector transformed_vector{arr<flt>(vector_size)};
    for (int row{0}; row < vector_size; ++row)
    {
        transformed_vector += rs_vector(row) * ls_matrix(row);
    }
    return transformed_vector;
}

Matrix operator *(const Matrix& ls_matrix, Matrix rs_matrix)
{
    for (int col{0}; col < rs_matrix.size(); ++col)
    {
        rs_matrix(col) = ls_matrix * rs_matrix(col);
    }
    return rs_matrix;
}

Matrix identity_matrix(const int size)
{
    Matrix identity_matrix{size};
    for (int index{0}; index < size; ++index)
    {
        identity_matrix(index, index) = 1;
    }
    return identity_matrix;
}

Matrix transpose(const Matrix& matrix)
{
    const int matrix_size{matrix.size()};
    Matrix result{matrix_size};
    for (int row{0}; row < matrix_size; ++row)
    {
        for (int col{0}; col < matrix_size; ++col)
        {
            result(col, row) = matrix(row, col);
        }
    }

    return result;
}

Matrix submatrix(const Matrix& matrix, const int& ignored_row_index, const int& ignored_col_index)
{
    const int matrix_size{matrix.size()};
    Matrix result{matrix_size - 1};
    for (int col{0}; col < matrix_size; ++col)
    {
        for (int row{0}; row < matrix_size; ++row)
        {
            if (row > ignored_row_index and col > ignored_col_index)
            {
                result(row - 1, col - 1) = matrix(row, col);
            }
            else if (row > ignored_row_index and col < ignored_col_index)
            {
                result(row - 1, col) = matrix(row, col);
            }
            else if (row < ignored_row_index and col > ignored_col_index)
            {
                result(row, col - 1) = matrix(row, col);
            }
            else if (row < ignored_row_index and col < ignored_col_index)
            {
                result(row, col) = matrix(row, col);
            }
        }
    }
    return result;
}

flt determinant(const Matrix& matrix);

flt minor(const Matrix& matrix, const int& ignored_row_index, const int& ignored_col_index)
{
    return determinant(submatrix(matrix, ignored_row_index, ignored_col_index));
}

flt cofactor(const Matrix& matrix, const int& ignored_row_index, const int& ignored_col_index)
{
    if ((ignored_row_index + ignored_col_index) % 2 != 0)
    {
        return minor(matrix, ignored_row_index, ignored_col_index) * -1;
    }
    else
    {
        return minor(matrix, ignored_row_index, ignored_col_index);
    }
}

flt determinant(const Matrix& matrix)
{
    const int matrix_size{matrix.size()};
    if (matrix_size == 2)
    {
        return matrix(0, 0) * matrix(1, 1) - matrix(0, 1) * matrix(1, 0);
    }
    else
    {
        flt result{0};
        for (int row{0}; row < matrix_size; ++row)
        {
            result += cofactor(matrix, row, 0) * matrix(row, 0);
        }
        return result;
    }
}

Matrix inverse(const Matrix& matrix)
{
    const int matrix_size{matrix.size()};
    Matrix result = matrix;
    for (int col{}; col < matrix_size; ++col)
    {
        for (int row{}; row < matrix_size; ++row)
        {
            result(row, col) = cofactor(matrix, row, col);
        }
    }
    result = transpose(result);
    result *= 1 / determinant(matrix);
    return result;
}
