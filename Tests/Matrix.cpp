#include "RayTracer/Matrix.hpp"
#include "RayTracer/Vector4.hpp"

#include <catch2/catch_test_macros.hpp>

namespace RayTracer::Tests
{
    constexpr const char* Tags = "[Matrix]";

    TEST_CASE("Matrix can be created with default constructor", Tags)
    {
        Matrix matrix;

        for (int i = 0; i < 16; ++i)
        {
            REQUIRE(matrix.elements[i] == 0.0f);
        }
    }

    TEST_CASE("Matrix can be created with diagonal constructor", Tags)
    {
        Matrix matrix{2.0f};

        REQUIRE(matrix.elements[0] == 2.0f);
        REQUIRE(matrix.elements[5] == 2.0f);
        REQUIRE(matrix.elements[10] == 2.0f);
        REQUIRE(matrix.elements[15] == 2.0f);

        for (int i = 0; i < 16; ++i)
        {
            if (i % 5 == 0)
            {
                REQUIRE(matrix.elements[i] == 2.0f);
            }
            else
            {
                REQUIRE(matrix.elements[i] == 0.0f);
            }
        }
    }

    TEST_CASE("Matrix identity", Tags)
    {
        Matrix identity = Matrix::Identity();

        REQUIRE(identity.elements[0] == 1.0f);
        REQUIRE(identity.elements[5] == 1.0f);
        REQUIRE(identity.elements[10] == 1.0f);
        REQUIRE(identity.elements[15] == 1.0f);
    }

    TEST_CASE("Matrix element access", Tags)
    {
        Matrix matrix;
        matrix(0, 1) = 5.0f;

        REQUIRE(matrix(0, 1) == 5.0f);
        REQUIRE(matrix.elements[4] == 5.0f);
    }

    TEST_CASE("Matrix equality", Tags)
    {
        Matrix a = Matrix::Identity();
        Matrix b = Matrix::Identity();
        Matrix c;

        REQUIRE(a == b);
        REQUIRE_FALSE(a == c);
    }

    TEST_CASE("Matrix addition", Tags)
    {
        Matrix a{1.0f};
        Matrix b{2.0f};
        Matrix result = a + b;

        REQUIRE(result.elements[0] == 3.0f);
        REQUIRE(result.elements[5] == 3.0f);
    }

    TEST_CASE("Matrix subtraction", Tags)
    {
        Matrix a{3.0f};
        Matrix b{1.0f};
        Matrix result = a - b;

        REQUIRE(result.elements[0] == 2.0f);
        REQUIRE(result.elements[5] == 2.0f);
    }

    TEST_CASE("Matrix scalar multiplication", Tags)
    {
        Matrix a{2.0f};
        Matrix result = a * 3.0f;

        REQUIRE(result.elements[0] == 6.0f);
        REQUIRE(result.elements[5] == 6.0f);
    }

    TEST_CASE("Matrix multiplication", Tags)
    {
        Matrix a{1.0f};
        Matrix b{2.0f};
        Matrix result = a * b;

        REQUIRE(result.elements[0] == 2.0f);
        REQUIRE(result.elements[5] == 2.0f);
        REQUIRE(result.elements[10] == 2.0f);
        REQUIRE(result.elements[15] == 2.0f);
    }

    TEST_CASE("Matrix vector multiplication", Tags)
    {
        Matrix matrix{1.0f};
        Vector4 vec{1.0f, 2.0f, 3.0f, 4.0f};
        Vector4 result = matrix * vec;

        REQUIRE(result.x == 1.0f);
        REQUIRE(result.y == 2.0f);
        REQUIRE(result.z == 3.0f);
        REQUIRE(result.w == 4.0f);
    }

    TEST_CASE("Matrix transpose", Tags)
    {
        Matrix matrix;
        matrix.elements[1] = 1.0f;
        matrix.elements[4] = 2.0f;

        Matrix transposed = matrix.Transpose();

        REQUIRE(transposed.elements[0] == 0.0f);
        REQUIRE(transposed.elements[1] == 2.0f);
        REQUIRE(transposed.elements[4] == 1.0f);
    }

    TEST_CASE("Matrix transpose in place", Tags)
    {
        Matrix matrix;
        matrix.elements[1] = 1.0f;
        matrix.elements[4] = 2.0f;

        matrix.TransposeInPlace();

        REQUIRE(matrix.elements[0] == 0.0f);
        REQUIRE(matrix.elements[1] == 2.0f);
        REQUIRE(matrix.elements[4] == 1.0f);
    }

    TEST_CASE("Matrix trace", Tags)
    {
        Matrix matrix{2.0f};
        REQUIRE(matrix.Trace() == 8.0f);
    }

    TEST_CASE("Matrix Frobenius norm", Tags)
    {
        Matrix matrix{1.0f};
        REQUIRE(matrix.FrobeniusNorm() == 2.0f);
    }

    TEST_CASE("Matrix determinant", Tags)
    {
        Matrix matrix{1.0f};
        REQUIRE(matrix.Determinant() == 1.0f);
    }

    TEST_CASE("Matrix inverse", Tags)
    {
        Matrix matrix{2.0f};
        Matrix inv = matrix.Inverse();
        Matrix product = matrix * inv;

        REQUIRE(product == Matrix::Identity());
    }

    TEST_CASE("Matrix translation", Tags)
    {
        Vector3 trans{1.0f, 2.0f, 3.0f};
        Matrix transMat = Matrix::Translation(trans);

        REQUIRE(transMat.elements[12] == 1.0f);
        REQUIRE(transMat.elements[13] == 2.0f);
        REQUIRE(transMat.elements[14] == 3.0f);
    }

    TEST_CASE("Matrix scaling", Tags)
    {
        Vector3 scale{2.0f, 3.0f, 4.0f};
        Matrix scaleMat = Matrix::Scaling(scale);

        REQUIRE(scaleMat.elements[0] == 2.0f);
        REQUIRE(scaleMat.elements[5] == 3.0f);
        REQUIRE(scaleMat.elements[10] == 4.0f);
    }

    TEST_CASE("Matrix rotation X", Tags)
    {
        Matrix rot = Matrix::RotationX(0.0f);
        REQUIRE(rot == Matrix::Identity());
    }

    TEST_CASE("Matrix rotation Y", Tags)
    {
        Matrix rot = Matrix::RotationY(0.0f);
        REQUIRE(rot == Matrix::Identity());
    }

    TEST_CASE("Matrix rotation Z", Tags)
    {
        Matrix rot = Matrix::RotationZ(0.0f);
        REQUIRE(rot == Matrix::Identity());
    }

    TEST_CASE("Matrix perspective", Tags)
    {
        Matrix persp = Matrix::Perspective(1.0f, 1.0f, 0.1f, 100.0f);
        REQUIRE(persp.elements[11] == -1.0f);
    }

    TEST_CASE("Matrix orthographic", Tags)
    {
        Matrix ortho = Matrix::Orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
        REQUIRE(ortho.elements[0] == 1.0f);
    }

    TEST_CASE("Matrix look at", Tags)
    {
        Vector3 eye{0.0f, 0.0f, 5.0f};
        Vector3 target{0.0f, 0.0f, 0.0f};
        Vector3 up{0.0f, 1.0f, 0.0f};
        Matrix look = Matrix::LookAt(eye, target, up);
        REQUIRE(look.elements[10] == 1.0f);
    }

    TEST_CASE("Matrix shear", Tags)
    {
        Matrix shear = Matrix::Shear(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
        REQUIRE(shear.elements[4] == 1.0f);
        REQUIRE(shear.elements[8] == 2.0f);
        REQUIRE(shear.elements[1] == 3.0f);
        REQUIRE(shear.elements[9] == 4.0f);
        REQUIRE(shear.elements[2] == 5.0f);
        REQUIRE(shear.elements[6] == 6.0f);
    }
}
