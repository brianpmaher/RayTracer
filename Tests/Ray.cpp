#include "RayTracer/Ray.hpp"

#include <catch2/catch_test_macros.hpp>

namespace RayTracer::Tests
{
    constexpr const char* Tags = "[Ray]";

    TEST_CASE("Ray can be created with default constructor", Tags)
    {
        Ray ray;

        REQUIRE(ray.origin == Vector3{0.0f, 0.0f, 0.0f});
        REQUIRE(ray.direction == Vector3{0.0f, 0.0f, 1.0f});
    }

    TEST_CASE("Ray can be created with parameterized constructor", Tags)
    {
        Vector3 origin{1.0f, 2.0f, 3.0f};
        Vector3 direction{0.0f, 1.0f, 0.0f};
        Ray ray{origin, direction};

        REQUIRE(ray.origin == origin);
        REQUIRE(ray.direction == direction.Normalized());
    }

    TEST_CASE("Ray At method", Tags)
    {
        Vector3 origin{0.0f, 0.0f, 0.0f};
        Vector3 direction{1.0f, 0.0f, 0.0f};
        Ray ray{origin, direction};

        Vector3 point = ray.At(2.0f);
        REQUIRE(point == Vector3{2.0f, 0.0f, 0.0f});
    }
}
