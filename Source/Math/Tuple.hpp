#pragma once

#include <type_traits>

namespace RayTracer::Math
{
    template <typename T>
    struct Tuple
    {
        static_assert(std::is_floating_point_v<T>, "T must be a floating-point type (float or double)");

        constexpr T VectorW = 0;
        constexpr T PointW = 1;

        T x;
        T y;
        T z;
        const T w;

        constexpr Tuple(T x, T y, T z, T w) noexcept
            : x{x}
            , y{y}
            , z{z}
            , w{w}
        {
        }

        constexpr bool IsVector() const
        {
            return w == static_cast<T>(VectorW);
        }

        constexpr bool IsPoint() const
        {
            return w == static_cast<T>(PointW);
        }
    };
}
