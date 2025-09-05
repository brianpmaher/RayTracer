#pragma once

#include <cmath>
#include <limits>

namespace RayTracer
{
    struct Color
    {
        float r;
        float g;
        float b;

        constexpr Color() noexcept
            : r{0}
            , g{0}
            , b{0}
        {
        }

        constexpr Color(float r, float g, float b) noexcept
            : r{r}
            , g{g}
            , b{b}
        {
        }

        bool operator==(const Color& other) const
        {
            constexpr float Epsilon = std::numeric_limits<float>::epsilon();
            return std::fabsf(r - other.r) < Epsilon && std::fabsf(g - other.g) < Epsilon &&
                   std::fabsf(b - other.b) < Epsilon;
        }

        bool operator!=(const Color& other) const
        {
            return !(*this == other);
        }

        Color operator+(const Color& other) const
        {
            return {r + other.r, g + other.g, b + other.b};
        }

        Color operator-(const Color& other) const
        {
            return {r - other.r, g - other.g, b - other.b};
        }

        Color operator-() const
        {
            return {-r, -g, -b};
        }

        Color operator*(float scalar) const
        {
            return {r * scalar, g * scalar, b * scalar};
        }

        Color operator/(float scalar) const
        {
            return {r / scalar, g / scalar, b / scalar};
        }

        Color operator*(const Color& other) const
        {
            return {r * other.r, g * other.g, b * other.b};
        }
    };

    inline Color operator*(float scalar, const Color& col)
    {
        return col * scalar;
    }
}
