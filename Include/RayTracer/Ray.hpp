#pragma once

#include "Vector3.hpp"

namespace RayTracer
{
    struct Ray
    {
        Vector3 origin;
        Vector3 direction;

        constexpr Ray() noexcept
            : origin{0.0f, 0.0f, 0.0f}
            , direction{0.0f, 0.0f, 1.0f}
        {
        }

        Ray(const Vector3& origin, const Vector3& direction) noexcept
            : origin{origin}
            , direction{direction.Normalized()}
        {
        }

        Vector3 At(float t) const
        {
            return origin + t * direction;
        }
    };
}
