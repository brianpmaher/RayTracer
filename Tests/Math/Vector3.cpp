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
}
