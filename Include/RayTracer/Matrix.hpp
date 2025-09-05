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

        static constexpr Matrix Identity() noexcept
        {
            return Matrix(1.0f);
        }

        float& operator()(int row, int col)
        {
            return elements[row + col * Columns];
        }

        const float& operator()(int row, int col) const
        {
            return elements[row + col * Columns];
        }

        bool operator==(const Matrix& other) const
        {
            constexpr float Epsilon = std::numeric_limits<float>::epsilon();
            for (int i = 0; i < Columns * Rows; ++i)
            {
                if (std::fabsf(elements[i] - other.elements[i]) > Epsilon)
                {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const Matrix& other) const
        {
            return !(*this == other);
        }

        Matrix operator+(const Matrix& other) const
        {
            Matrix result;
            for (int i = 0; i < Columns * Rows; ++i)
            {
                result.elements[i] = elements[i] + other.elements[i];
            }
            return result;
        }

        Matrix operator-(const Matrix& other) const
        {
            Matrix result;
            for (int i = 0; i < Columns * Rows; ++i)
            {
                result.elements[i] = elements[i] - other.elements[i];
            }
            return result;
        }

        Matrix operator*(float scalar) const
        {
            Matrix result;
            for (int i = 0; i < Columns * Rows; ++i)
            {
                result.elements[i] = elements[i] * scalar;
            }
            return result;
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

        void TransposeInPlace()
        {
            for (int c = 0; c < Columns; ++c)
            {
                for (int r = c + 1; r < Rows; ++r)
                {
                    std::swap(elements[r + c * Columns], elements[c + r * Columns]);
                }
            }
        }

        float Trace() const
        {
            return elements[0] + elements[5] + elements[10] + elements[15];
        }

        float FrobeniusNorm() const
        {
            float sum = 0.0f;
            for (int i = 0; i < Columns * Rows; ++i)
            {
                sum += elements[i] * elements[i];
            }
            return std::sqrtf(sum);
        }

        float Determinant() const
        {
            // Using the formula for 4x4 determinant
            float m[16];
            for (int i = 0; i < 16; ++i)
                m[i] = elements[i];

            float det = m[0] * (m[5] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[9] * m[15] - m[11] * m[13]) +
                                m[7] * (m[9] * m[14] - m[10] * m[13])) -
                        m[1] * (m[4] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[8] * m[15] - m[11] * m[12]) +
                                m[7] * (m[8] * m[14] - m[10] * m[12])) +
                        m[2] * (m[4] * (m[9] * m[15] - m[11] * m[13]) - m[5] * (m[8] * m[15] - m[11] * m[12]) +
                                m[7] * (m[8] * m[13] - m[9] * m[12])) -
                        m[3] * (m[4] * (m[9] * m[14] - m[10] * m[13]) - m[5] * (m[8] * m[14] - m[10] * m[12]) +
                                m[6] * (m[8] * m[13] - m[9] * m[12]));
            return det;
        }

        Matrix Inverse() const
        {
            float det = Determinant();
            if (std::fabsf(det) < std::numeric_limits<float>::epsilon())
            {
                // Singular matrix, return identity or handle error
                return Identity();
            }

            Matrix inv;
            float m[16];
            for (int i = 0; i < 16; ++i)
                m[i] = elements[i];

            // Adjugate method
            inv.elements[0] = m[5] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[9] * m[15] - m[11] * m[13]) +
                              m[7] * (m[9] * m[14] - m[10] * m[13]);
            inv.elements[1] = -(m[1] * (m[10] * m[15] - m[11] * m[14]) - m[2] * (m[9] * m[15] - m[11] * m[13]) +
                                m[3] * (m[9] * m[14] - m[10] * m[13]));
            inv.elements[2] = m[1] * (m[6] * m[15] - m[7] * m[14]) - m[2] * (m[5] * m[15] - m[7] * m[13]) +
                              m[3] * (m[5] * m[14] - m[6] * m[13]);
            inv.elements[3] = -(m[1] * (m[6] * m[11] - m[7] * m[10]) - m[2] * (m[5] * m[11] - m[7] * m[9]) +
                                m[3] * (m[5] * m[10] - m[6] * m[9]));

            inv.elements[4] = -(m[4] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[8] * m[15] - m[11] * m[12]) +
                                m[7] * (m[8] * m[14] - m[10] * m[12]));
            inv.elements[5] = m[0] * (m[10] * m[15] - m[11] * m[14]) - m[2] * (m[8] * m[15] - m[11] * m[12]) +
                              m[3] * (m[8] * m[14] - m[10] * m[12]);
            inv.elements[6] = -(m[0] * (m[6] * m[15] - m[7] * m[14]) - m[2] * (m[4] * m[15] - m[7] * m[12]) +
                                m[3] * (m[4] * m[14] - m[6] * m[12]));
            inv.elements[7] = m[0] * (m[6] * m[11] - m[7] * m[10]) - m[2] * (m[4] * m[11] - m[7] * m[8]) +
                              m[3] * (m[4] * m[10] - m[6] * m[8]);

            inv.elements[8] = m[4] * (m[9] * m[15] - m[11] * m[13]) - m[5] * (m[8] * m[15] - m[11] * m[12]) +
                              m[7] * (m[8] * m[13] - m[9] * m[12]);
            inv.elements[9] = -(m[0] * (m[9] * m[15] - m[11] * m[13]) - m[1] * (m[8] * m[15] - m[11] * m[12]) +
                                m[3] * (m[8] * m[13] - m[9] * m[12]));
            inv.elements[10] = m[0] * (m[5] * m[15] - m[7] * m[13]) - m[1] * (m[4] * m[15] - m[7] * m[12]) +
                               m[3] * (m[4] * m[13] - m[5] * m[12]);
            inv.elements[11] = -(m[0] * (m[5] * m[11] - m[7] * m[9]) - m[1] * (m[4] * m[11] - m[7] * m[8]) +
                                 m[3] * (m[4] * m[9] - m[5] * m[8]));

            inv.elements[12] = -(m[4] * (m[9] * m[14] - m[10] * m[13]) - m[5] * (m[8] * m[14] - m[10] * m[12]) +
                                 m[6] * (m[8] * m[13] - m[9] * m[12]));
            inv.elements[13] = m[0] * (m[9] * m[14] - m[10] * m[13]) - m[1] * (m[8] * m[14] - m[10] * m[12]) +
                               m[2] * (m[8] * m[13] - m[9] * m[12]);
            inv.elements[14] = -(m[0] * (m[5] * m[14] - m[6] * m[13]) - m[1] * (m[4] * m[14] - m[6] * m[12]) +
                                 m[2] * (m[4] * m[13] - m[5] * m[12]));
            inv.elements[15] = m[0] * (m[5] * m[10] - m[6] * m[9]) - m[1] * (m[4] * m[10] - m[6] * m[8]) +
                               m[2] * (m[4] * m[9] - m[5] * m[8]);

            for (int i = 0; i < 16; ++i)
            {
                inv.elements[i] /= det;
            }
            return inv;
        }

        static Matrix Translation(const Vector3& translation)
        {
            Matrix result = Identity();
            result.elements[12] = translation.x;
            result.elements[13] = translation.y;
            result.elements[14] = translation.z;
            return result;
        }

        static Matrix Scaling(const Vector3& scale)
        {
            Matrix result;
            result.elements[0] = scale.x;
            result.elements[5] = scale.y;
            result.elements[10] = scale.z;
            result.elements[15] = 1.0f;
            return result;
        }

        static Matrix RotationX(float angle)
        {
            Matrix result = Identity();
            float c = std::cosf(angle);
            float s = std::sinf(angle);
            result.elements[5] = c;
            result.elements[6] = -s;
            result.elements[9] = s;
            result.elements[10] = c;
            return result;
        }

        static Matrix RotationY(float angle)
        {
            Matrix result = Identity();
            float c = std::cosf(angle);
            float s = std::sinf(angle);
            result.elements[0] = c;
            result.elements[2] = s;
            result.elements[8] = -s;
            result.elements[10] = c;
            return result;
        }

        static Matrix RotationZ(float angle)
        {
            Matrix result = Identity();
            float c = std::cosf(angle);
            float s = std::sinf(angle);
            result.elements[0] = c;
            result.elements[1] = -s;
            result.elements[4] = s;
            result.elements[5] = c;
            return result;
        }

        static Matrix Perspective(float fov, float aspect, float near, float far)
        {
            Matrix result;
            float tanHalfFov = std::tanf(fov / 2.0f);
            result.elements[0] = 1.0f / (aspect * tanHalfFov);
            result.elements[5] = 1.0f / tanHalfFov;
            result.elements[10] = -(far + near) / (far - near);
            result.elements[11] = -1.0f;
            result.elements[14] = -(2.0f * far * near) / (far - near);
            return result;
        }

        static Matrix Orthographic(float left, float right, float bottom, float top, float near, float far)
        {
            Matrix result = Identity();
            result.elements[0] = 2.0f / (right - left);
            result.elements[5] = 2.0f / (top - bottom);
            result.elements[10] = -2.0f / (far - near);
            result.elements[12] = -(right + left) / (right - left);
            result.elements[13] = -(top + bottom) / (top - bottom);
            result.elements[14] = -(far + near) / (far - near);
            return result;
        }

        static Matrix LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
        {
            Vector3 z = (eye - target).Normalized();
            Vector3 x = up.Cross(z).Normalized();
            Vector3 y = z.Cross(x);

            Matrix result = Identity();
            result.elements[0] = x.x;
            result.elements[1] = y.x;
            result.elements[2] = z.x;
            result.elements[4] = x.y;
            result.elements[5] = y.y;
            result.elements[6] = z.y;
            result.elements[8] = x.z;
            result.elements[9] = y.z;
            result.elements[10] = z.z;
            result.elements[12] = -x.Dot(eye);
            result.elements[13] = -y.Dot(eye);
            result.elements[14] = -z.Dot(eye);
            return result;
        }

        static Matrix Shear(float xy, float xz, float yx, float yz, float zx, float zy)
        {
            Matrix result = Identity();
            result.elements[4] = xy; // Shear x by y
            result.elements[8] = xz; // Shear x by z
            result.elements[1] = yx; // Shear y by x
            result.elements[9] = yz; // Shear y by z
            result.elements[2] = zx; // Shear z by x
            result.elements[6] = zy; // Shear z by y
            return result;
        }
    };

    inline Matrix operator*(float scalar, const Matrix& mat)
    {
        return mat * scalar;
    }

    inline Vector4 operator*(const Vector4& vec, const Matrix& mat)
    {
        return mat * vec;
    }
}
