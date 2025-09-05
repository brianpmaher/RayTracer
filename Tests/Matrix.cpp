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
}
