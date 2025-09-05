#pragma once

#include "Ray.hpp"
#include "Vector3.hpp"

#include <cmath>

namespace RayTracer
{
    struct Sphere
    {
        struct RayIntersection
        {
            bool hit = false;
            float t1 = 0.0f;
            float t2 = 0.0f;
        };

        Vector3 center;
        float radius;

        constexpr Sphere() noexcept
            : center{0.0f, 0.0f, 0.0f}
            , radius{1.0f}
        {
        }

        constexpr Sphere(const Vector3& center, float radius) noexcept
            : center{center}
            , radius{radius}
        {
        }

        RayIntersection Intersect(const Ray& ray) const;

        Vector3 NormalAt(const Vector3& point) const
        {
            return (point - center).Normalized();
        }
    };
}
