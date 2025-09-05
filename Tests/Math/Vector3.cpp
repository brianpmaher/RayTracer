#include "RayTracer/Math/Vector3.hpp"

#include <catch2/catch_test_macros.hpp>

namespace RayTracer::Math::Tests
{
    constexpr const char* Tags = "[Math][Vector3]";

    TEST_CASE("Vector3 can be created with default constructor", Tags)
    {
        Vector3 vector;

        REQUIRE(vector.x == 0.0);
        REQUIRE(vector.y == 0.0);
        REQUIRE(vector.z == 0.0);
    }

    TEST_CASE("Vector3 can be created with parameterized constructor", Tags)
    {
        Vector3 vector{1.0, -2.0, 3.5};

        REQUIRE(vector.x == 1.0);
        REQUIRE(vector.y == -2.0);
        REQUIRE(vector.z == 3.5);
    }

    TEST_CASE("Vector3 equality operator", Tags)
    {
        Vector3 a{1.0f, 2.0f, 3.0f};
        Vector3 b{1.0f, 2.0f, 3.0f};
        Vector3 c{1.0f, 2.1f, 3.0f};

        REQUIRE(a == b);
        REQUIRE_FALSE(a == c);
    }

    TEST_CASE("Vector3 inequality operator", Tags)
    {
        Vector3 a{1.0f, 2.0f, 3.0f};
        Vector3 b{1.0f, 2.0f, 3.0f};
        Vector3 c{1.0f, 2.1f, 3.0f};

        REQUIRE_FALSE(a != b);
        REQUIRE(a != c);
    }

    TEST_CASE("Vector3 addition operator", Tags)
    {
        Vector3 a{1.0f, 2.0f, 3.0f};
        Vector3 b{4.0f, 5.0f, 6.0f};
        Vector3 result = a + b;

        REQUIRE(result.x == 5.0f);
        REQUIRE(result.y == 7.0f);
        REQUIRE(result.z == 9.0f);
    }

    TEST_CASE("Vector3 subtraction operator", Tags)
    {
        Vector3 a{5.0f, 7.0f, 9.0f};
        Vector3 b{4.0f, 5.0f, 6.0f};
        Vector3 result = a - b;

        REQUIRE(result.x == 1.0f);
        REQUIRE(result.y == 2.0f);
        REQUIRE(result.z == 3.0f);
    }

    TEST_CASE("Vector3 negation operator", Tags)
    {
        Vector3 a{1.0f, -2.0f, 3.0f};
        Vector3 result = -a;

        REQUIRE(result.x == -1.0f);
        REQUIRE(result.y == 2.0f);
        REQUIRE(result.z == -3.0f);
    }

    TEST_CASE("Vector3 scalar multiplication", Tags)
    {
        Vector3 a{1.0f, 2.0f, 3.0f};
        Vector3 result = a * 2.0f;

        REQUIRE(result.x == 2.0f);
        REQUIRE(result.y == 4.0f);
        REQUIRE(result.z == 6.0f);

        Vector3 result2 = 2.0f * a;
        REQUIRE(result2 == result);
    }

    TEST_CASE("Vector3 scalar division", Tags)
    {
        Vector3 a{2.0f, 4.0f, 6.0f};
        Vector3 result = a / 2.0f;

        REQUIRE(result.x == 1.0f);
        REQUIRE(result.y == 2.0f);
        REQUIRE(result.z == 3.0f);
    }

    TEST_CASE("Vector3 LengthSquared", Tags)
    {
        Vector3 a{3.0f, 4.0f, 0.0f};
        REQUIRE(a.LengthSquared() == 25.0f);
    }

    TEST_CASE("Vector3 Length", Tags)
    {
        Vector3 a{3.0f, 4.0f, 0.0f};
        REQUIRE(a.Length() == 5.0f);
    }

    TEST_CASE("Vector3 Normalize", Tags)
    {
        Vector3 a{3.0f, 4.0f, 0.0f};
        a.Normalize();
        REQUIRE(a.Length() == 1.0f);
        REQUIRE(a.x == 0.6f);
        REQUIRE(a.y == 0.8f);
        REQUIRE(a.z == 0.0f);
    }

    TEST_CASE("Vector3 Normalized", Tags)
    {
        Vector3 a{3.0f, 4.0f, 0.0f};
        Vector3 b = a.Normalized();
        REQUIRE(b.Length() == 1.0f);
        REQUIRE(b.x == 0.6f);
        REQUIRE(b.y == 0.8f);
        REQUIRE(b.z == 0.0f);
        REQUIRE(a.x == 3.0f); // original unchanged
        REQUIRE(a.y == 4.0f);
        REQUIRE(a.z == 0.0f);
    }

    TEST_CASE("Vector3 Normalize zero vector", Tags)
    {
        Vector3 a{0.0f, 0.0f, 0.0f};
        a.Normalize();
        REQUIRE(a.x == 0.0f);
        REQUIRE(a.y == 0.0f);
        REQUIRE(a.z == 0.0f);
    }

    TEST_CASE("Vector3 Normalized zero vector", Tags)
    {
        Vector3 a{0.0f, 0.0f, 0.0f};
        Vector3 b = a.Normalized();
        REQUIRE(b.x == 0.0f);
        REQUIRE(b.y == 0.0f);
        REQUIRE(b.z == 0.0f);
    }

    TEST_CASE("Vector3 Dot product", Tags)
    {
        Vector3 a{1.0f, 2.0f, 3.0f};
        Vector3 b{4.0f, 5.0f, 6.0f};
        REQUIRE(a.Dot(b) == 32.0f);
    }

    TEST_CASE("Vector3 Cross product", Tags)
    {
        Vector3 a{1.0f, 2.0f, 3.0f};
        Vector3 b{4.0f, 5.0f, 6.0f};
        Vector3 result = a.Cross(b);
        REQUIRE(result.x == -3.0f);
        REQUIRE(result.y == 6.0f);
        REQUIRE(result.z == -3.0f);
    }
}
