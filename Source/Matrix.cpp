#include "RayTracer/Matrix.hpp"

#include <cmath>

namespace RayTracer
{
    float Matrix::Determinant() const
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

    Matrix Matrix::Inverse() const
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
}
