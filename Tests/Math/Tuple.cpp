#include "Math/Tuple.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Tuple can be created with parameterized constructor", "[Tuple]")
{
    constexpr RayTracer::Math::Tuple<double> tuple{1.0, -2.0, 3.5, 1.0};

    STATIC_REQUIRE(tuple.x == 1.0);
    STATIC_REQUIRE(tuple.y == -2.0);
    STATIC_REQUIRE(tuple.z == 3.5);
    STATIC_REQUIRE(tuple.w == 1.0);
}

TEST_CASE("Tuple with w=0 is a vector", "[Tuple]")
{
    constexpr RayTracer::Math::Tuple<double> vector{4.3, -4.2, 3.1, 0.0};

    STATIC_REQUIRE(vector.IsVector());
    STATIC_REQUIRE_FALSE(vector.IsPoint());
}

TEST_CASE("Tuple with w=1 is a point", "[Tuple]")
{
    constexpr RayTracer::Math::Tuple<float> point{4.3f, -4.2f, 3.1f, 1.0f};

    STATIC_REQUIRE(point.IsPoint());
    STATIC_REQUIRE_FALSE(point.IsVector());
}
