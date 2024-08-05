#pragma once
#include <cmath>
#include <algorithm>
#include "vector_math.h"

template<typename... Args>
Matrix translation(Args... args)
{
    const arr<flt> coordinates{cast<flt>(args)...};
    const int coordinate_count = coordinates.size();

    Matrix matrix{identity_matrix(coordinate_count + 1)};

    for (int row{0}; row < coordinate_count; ++row)
    {
        matrix(row, coordinate_count) = coordinates[row];
    }

    return matrix;
}

template<typename... Args>
Matrix scaling(Args... args)
{
    const arr<flt> coordinates{cast<flt>(args)...};
    const int coordinate_count = coordinates.size();
    Matrix matrix{identity_matrix(coordinate_count + 1)};

    for (int row{0}; row < coordinate_count; ++row)
    {
        matrix(row, row) = coordinates[row];
    }

    return matrix;
}

Matrix rotation(const char& rotation_axis, const flt& rotation_in_degrees, const int& matrix_size)
{
    const flt rotation_in_radians{rotation_in_degrees * std::numbers::pi / 180};
    Matrix matrix{identity_matrix(matrix_size)};
    arr<int> index{};
    if (rotation_axis == 'x')
    {
        matrix(1, 1) = std::cos(rotation_in_radians);
        matrix(1, 2) = -std::sin(rotation_in_radians);
        matrix(2, 1) = std::sin(rotation_in_radians);
        matrix(2, 2) = std::cos(rotation_in_radians);
    }
    else if (rotation_axis == 'y')
    {
        matrix(0, 0) = std::cos(rotation_in_radians);
        matrix(0, 2) = std::sin(rotation_in_radians);
        matrix(2, 0) = -std::sin(rotation_in_radians);
        matrix(2, 2) = std::cos(rotation_in_radians);
    }
    else if (rotation_axis == 'z')
    {
        matrix(0, 0) = std::cos(rotation_in_radians);
        matrix(0, 1) = -std::sin(rotation_in_radians);
        matrix(1, 0) = std::sin(rotation_in_radians);
        matrix(1, 1) = std::cos(rotation_in_radians);
    }
    return matrix;
}

Matrix four_by_four_shear(flt xy, flt xz, flt yx, flt yz, flt zx, flt zy)
{
    return Matrix {{1,yx,zx,0},{xy,1,zy,0},{xz,yz,1,0},{0,0,0,1}};
}
