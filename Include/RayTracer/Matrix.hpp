#pragma once

#include <cmath>
#include <limits>

#include "Vector4.hpp"

namespace RayTracer
{
    /**
     * A 4x4 matrix, stored in column-major order.
     */
    struct Matrix
    {
        static constexpr int Columns = 4;
        static constexpr int Rows = 4;

        float elements[Columns * Rows];

        constexpr Matrix() noexcept
            : elements{}
        {
            for (int i = 0; i < Columns * Rows; ++i)
            {
                elements[i] = 0.0f;
            }
        }

        constexpr Matrix(const float diagonal) noexcept
            : elements{}
        {
            for (int i = 0; i < Columns * Rows; ++i)
            {
                if (i % (Columns + 1) == 0)
                {
                    elements[i] = diagonal;
                }
                else
                {
                    elements[i] = 0.0f;
                }
            }
        }

        Matrix operator*(const Matrix& other) const
        {
            Matrix result;
            for (int c = 0; c < Columns; ++c)
            {
                for (int r = 0; r < Rows; ++r)
                {
                    float sum = 0.0f;
                    for (int k = 0; k < Columns; ++k)
                    {
                        sum += elements[k + c * Columns] * other.elements[r + k * Columns];
                    }
                    result.elements[r + c * Columns] = sum;
                }
            }
            return result;
        }

        Vector4 operator*(const Vector4& vec) const
        {
            Vector4 result;
            result.x = elements[0] * vec.x + elements[4] * vec.y + elements[8] * vec.z + elements[12] * vec.w;
            result.y = elements[1] * vec.x + elements[5] * vec.y + elements[9] * vec.z + elements[13] * vec.w;
            result.z = elements[2] * vec.x + elements[6] * vec.y + elements[10] * vec.z + elements[14] * vec.w;
            result.w = elements[3] * vec.x + elements[7] * vec.y + elements[11] * vec.z + elements[15] * vec.w;
            return result;
        }

        Matrix Transpose() const
        {
            Matrix result;
            for (int c = 0; c < Columns; ++c)
            {
                for (int r = 0; r < Rows; ++r)
                {
                    result.elements[c + r * Columns] = elements[r + c * Columns];
                }
            }
            return result;
        }
    };
}
