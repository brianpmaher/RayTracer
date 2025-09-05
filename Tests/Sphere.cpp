#include "RayTracer/Sphere.hpp"

#include <catch2/catch_test_macros.hpp>

namespace RayTracer::Tests
{
    constexpr const char* Tags = "[Sphere]";

    TEST_CASE("Sphere can be created with default constructor", Tags)
    {
        Sphere sphere;

        REQUIRE(sphere.center == Vector3{0.0f, 0.0f, 0.0f});
        REQUIRE(sphere.radius == 1.0f);
    }

    TEST_CASE("Sphere can be created with parameterized constructor", Tags)
    {
        Vector3 center{1.0f, 2.0f, 3.0f};
        float radius = 2.5f;
        Sphere sphere{center, radius};

        REQUIRE(sphere.center == center);
        REQUIRE(sphere.radius == radius);
    }

    TEST_CASE("Sphere intersection hit", Tags)
    {
        Sphere sphere{{0.0f, 0.0f, 0.0f}, 1.0f};
        Ray ray{{0.0f, 0.0f, -5.0f}, {0.0f, 0.0f, 1.0f}};
        Sphere::RayIntersection inter = sphere.Intersect(ray);

        REQUIRE(inter.hit);
        REQUIRE(inter.t1 == 4.0f);
        REQUIRE(inter.t2 == 6.0f);
    }

    TEST_CASE("Sphere intersection miss", Tags)
    {
        Sphere sphere{{0.0f, 0.0f, 0.0f}, 1.0f};
        Ray ray{{0.0f, 2.0f, -5.0f}, {0.0f, 0.0f, 1.0f}};
        Sphere::RayIntersection inter = sphere.Intersect(ray);

        REQUIRE_FALSE(inter.hit);
    }

    TEST_CASE("Sphere normal at point", Tags)
    {
        Sphere sphere{{0.0f, 0.0f, 0.0f}, 1.0f};
        Vector3 point{1.0f, 0.0f, 0.0f};
        Vector3 normal = sphere.NormalAt(point);

        REQUIRE(normal == Vector3{1.0f, 0.0f, 0.0f});
    }
}
