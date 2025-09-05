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
}
