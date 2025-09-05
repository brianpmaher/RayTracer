#include "RayTracer/Math/Vector4.hpp"

#include <catch2/catch_test_macros.hpp>

namespace RayTracer::Math::Tests
{
    constexpr const char* Tags = "[Math][Vector4]";

    TEST_CASE("Vector4 can be created with default constructor", Tags)
    {
        Vector4 vector;

        REQUIRE(vector.x == 0.0f);
        REQUIRE(vector.y == 0.0f);
        REQUIRE(vector.z == 0.0f);
        REQUIRE(vector.w == 0.0f);
    }

    TEST_CASE("Vector4 can be created with parameterized constructor", Tags)
    {
        Vector4 vector{1.0f, -2.0f, 3.5f, 4.0f};

        REQUIRE(vector.x == 1.0f);
        REQUIRE(vector.y == -2.0f);
        REQUIRE(vector.z == 3.5f);
        REQUIRE(vector.w == 4.0f);
    }

    TEST_CASE("Vector4 can be created from Vector3 and w component", Tags)
    {
        Vector3 vec3{1.0f, -2.0f, 3.5f};
        float w = 4.0f;
        Vector4 vector{vec3, w};

        REQUIRE(vector.x == 1.0f);
        REQUIRE(vector.y == -2.0f);
        REQUIRE(vector.z == 3.5f);
        REQUIRE(vector.w == 4.0f);
    }

    TEST_CASE("Vector4 equality operator", Tags)
    {
        Vector4 a{1.0f, 2.0f, 3.0f, 4.0f};
        Vector4 b{1.0f, 2.0f, 3.0f, 4.0f};
        Vector4 c{1.0f, 2.1f, 3.0f, 4.0f};

        REQUIRE(a == b);
        REQUIRE_FALSE(a == c);
    }

    TEST_CASE("Vector4 inequality operator", Tags)
    {
        Vector4 a{1.0f, 2.0f, 3.0f, 4.0f};
        Vector4 b{1.0f, 2.0f, 3.0f, 4.0f};
        Vector4 c{1.0f, 2.1f, 3.0f, 4.0f};

        REQUIRE_FALSE(a != b);
        REQUIRE(a != c);
    }

    TEST_CASE("Vector4 addition operator", Tags)
    {
        Vector4 a{1.0f, 2.0f, 3.0f, 4.0f};
        Vector4 b{5.0f, 6.0f, 7.0f, 8.0f};
        Vector4 result = a + b;

        REQUIRE(result.x == 6.0f);
        REQUIRE(result.y == 8.0f);
        REQUIRE(result.z == 10.0f);
        REQUIRE(result.w == 12.0f);
    }

    TEST_CASE("Vector4 subtraction operator", Tags)
    {
        Vector4 a{6.0f, 8.0f, 10.0f, 12.0f};
        Vector4 b{5.0f, 6.0f, 7.0f, 8.0f};
        Vector4 result = a - b;

        REQUIRE(result.x == 1.0f);
        REQUIRE(result.y == 2.0f);
        REQUIRE(result.z == 3.0f);
        REQUIRE(result.w == 4.0f);
    }

    TEST_CASE("Vector4 negation operator", Tags)
    {
        Vector4 a{1.0f, -2.0f, 3.0f, -4.0f};
        Vector4 result = -a;

        REQUIRE(result.x == -1.0f);
        REQUIRE(result.y == 2.0f);
        REQUIRE(result.z == -3.0f);
        REQUIRE(result.w == 4.0f);
    }

    TEST_CASE("Vector4 scalar multiplication", Tags)
    {
        Vector4 a{1.0f, 2.0f, 3.0f, 4.0f};
        Vector4 result = a * 2.0f;

        REQUIRE(result.x == 2.0f);
        REQUIRE(result.y == 4.0f);
        REQUIRE(result.z == 6.0f);
        REQUIRE(result.w == 8.0f);

        Vector4 result2 = 2.0f * a;
        REQUIRE(result2 == result);
    }

    TEST_CASE("Vector4 scalar division", Tags)
    {
        Vector4 a{2.0f, 4.0f, 6.0f, 8.0f};
        Vector4 result = a / 2.0f;

        REQUIRE(result.x == 1.0f);
        REQUIRE(result.y == 2.0f);
        REQUIRE(result.z == 3.0f);
        REQUIRE(result.w == 4.0f);
    }

    TEST_CASE("Vector4 LengthSquared", Tags)
    {
        Vector4 a{3.0f, 4.0f, 0.0f, 0.0f};
        REQUIRE(a.LengthSquared() == 25.0f);
    }

    TEST_CASE("Vector4 Length", Tags)
    {
        Vector4 a{3.0f, 4.0f, 0.0f, 0.0f};
        REQUIRE(a.Length() == 5.0f);
    }

    TEST_CASE("Vector4 Normalize", Tags)
    {
        Vector4 a{3.0f, 4.0f, 0.0f, 0.0f};
        a.Normalize();
        REQUIRE(a.Length() == 1.0f);
        REQUIRE(a.x == 0.6f);
        REQUIRE(a.y == 0.8f);
        REQUIRE(a.z == 0.0f);
        REQUIRE(a.w == 0.0f);
    }

    TEST_CASE("Vector4 Normalized", Tags)
    {
        Vector4 a{3.0f, 4.0f, 0.0f, 0.0f};
        Vector4 b = a.Normalized();
        REQUIRE(b.Length() == 1.0f);
        REQUIRE(b.x == 0.6f);
        REQUIRE(b.y == 0.8f);
        REQUIRE(b.z == 0.0f);
        REQUIRE(b.w == 0.0f);
        REQUIRE(a.x == 3.0f); // original unchanged
        REQUIRE(a.y == 4.0f);
        REQUIRE(a.z == 0.0f);
        REQUIRE(a.w == 0.0f);
    }

    TEST_CASE("Vector4 Normalize zero vector", Tags)
    {
        Vector4 a{0.0f, 0.0f, 0.0f, 0.0f};
        a.Normalize();
        REQUIRE(a.x == 0.0f);
        REQUIRE(a.y == 0.0f);
        REQUIRE(a.z == 0.0f);
        REQUIRE(a.w == 0.0f);
    }

    TEST_CASE("Vector4 Normalized zero vector", Tags)
    {
        Vector4 a{0.0f, 0.0f, 0.0f, 0.0f};
        Vector4 b = a.Normalized();
        REQUIRE(b.x == 0.0f);
        REQUIRE(b.y == 0.0f);
        REQUIRE(b.z == 0.0f);
        REQUIRE(b.w == 0.0f);
    }

    TEST_CASE("Vector4 Dot product", Tags)
    {
        Vector4 a{1.0f, 2.0f, 3.0f, 4.0f};
        Vector4 b{5.0f, 6.0f, 7.0f, 8.0f};
        REQUIRE(a.Dot(b) == 70.0f);
    }
}
