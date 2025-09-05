#include "RayTracer/Sphere.hpp"

#include <cmath>
#include <utility>

namespace RayTracer
{
    Sphere::RayIntersection Sphere::Intersect(const Ray& ray) const
    {
        Vector3 oc = ray.origin - center;
        float a = ray.direction.Dot(ray.direction);
        float b = 2.0f * oc.Dot(ray.direction);
        float c = oc.Dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
        {
            return {};
        }
        float sqrtD = std::sqrtf(discriminant);
        float t1 = (-b - sqrtD) / (2 * a);
        float t2 = (-b + sqrtD) / (2 * a);
        if (t1 > t2)
            std::swap(t1, t2); // Ensure t1 <= t2
        if (t2 < 0)
        {
            return {};
        }
        Sphere::RayIntersection inter;
        inter.hit = true;
        if (t1 >= 0)
        {
            inter.t1 = t1;
            inter.t2 = t2;
        }
        else
        {
            inter.t1 = t2;
            inter.t2 = t2; // Only one positive
        }
        return inter;
    }
}
