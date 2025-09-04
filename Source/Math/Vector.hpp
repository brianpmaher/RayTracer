#pragma once

#include "Tuple.hpp"

namespace RayTracer::Math
{
    template <typename T>
    struct Vector : public Tuple<T>
    {
        static_assert(std::is_floating_point_v<T>, "T must be a floating-point type (float or double)");

        constexpr Vector() noexcept
            : Tuple<T>{static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(VectorW)}
        {
        }

        constexpr Vector(T x, T y, T z) noexcept
            : Tuple<T>{x, y, z, static_cast<T>(VectorW)}
        {
        }
    };
}
