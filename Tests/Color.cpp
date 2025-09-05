#include "RayTracer/Color.hpp"

#include <catch2/catch_test_macros.hpp>

namespace RayTracer::Tests
{
    constexpr const char* Tags = "[Color]";

    TEST_CASE("Color can be created with default constructor", Tags)
    {
        Color color;

        REQUIRE(color == Color{0.0f, 0.0f, 0.0f});
    }

    TEST_CASE("Color can be created with parameterized constructor", Tags)
    {
        Color color{1.0f, 0.5f, 0.2f};

        REQUIRE(color == Color{1.0f, 0.5f, 0.2f});
    }

    TEST_CASE("Color equality operator", Tags)
    {
        Color a{1.0f, 0.5f, 0.2f};
        Color b{1.0f, 0.5f, 0.2f};
        Color c{1.0f, 0.6f, 0.2f};

        REQUIRE(a == b);
        REQUIRE_FALSE(a == c);
    }

    TEST_CASE("Color inequality operator", Tags)
    {
        Color a{1.0f, 0.5f, 0.2f};
        Color b{1.0f, 0.5f, 0.2f};
        Color c{1.0f, 0.6f, 0.2f};

        REQUIRE_FALSE(a != b);
        REQUIRE(a != c);
    }

    TEST_CASE("Color addition operator", Tags)
    {
        Color a{0.1f, 0.2f, 0.3f};
        Color b{0.4f, 0.5f, 0.6f};
        Color result = a + b;

        REQUIRE(result == Color{0.5f, 0.7f, 0.9f});
    }

    TEST_CASE("Color subtraction operator", Tags)
    {
        Color a{0.5f, 0.7f, 0.9f};
        Color b{0.4f, 0.5f, 0.6f};
        Color result = a - b;

        REQUIRE(result == Color{0.1f, 0.2f, 0.3f});
    }

    TEST_CASE("Color negation operator", Tags)
    {
        Color a{0.1f, -0.2f, 0.3f};
        Color result = -a;

        REQUIRE(result == Color{-0.1f, 0.2f, -0.3f});
    }

    TEST_CASE("Color scalar multiplication", Tags)
    {
        Color a{0.1f, 0.2f, 0.3f};
        Color result = a * 2.0f;

        REQUIRE(result == Color{0.2f, 0.4f, 0.6f});

        Color result2 = 2.0f * a;
        REQUIRE(result2 == result);
    }

    TEST_CASE("Color scalar division", Tags)
    {
        Color a{0.2f, 0.4f, 0.6f};
        Color result = a / 2.0f;

        REQUIRE(result == Color{0.1f, 0.2f, 0.3f});
    }

    TEST_CASE("Color Hadamard product", Tags)
    {
        Color a{0.1f, 0.2f, 0.3f};
        Color b{2.0f, 3.0f, 4.0f};
        Color result = a * b;

        REQUIRE(result == Color{0.2f, 0.6f, 1.2f});
    }
}
