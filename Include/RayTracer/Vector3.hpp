#pragma once

#include <cmath>
#include <limits>

namespace RayTracer
{
    struct Vector3
    {
        float x;
        float y;
        float z;

        constexpr Vector3() noexcept
            : x{0}
            , y{0}
            , z{0}
        {
        }

        constexpr Vector3(float x, float y, float z) noexcept
            : x{x}
            , y{y}
            , z{z}
        {
        }

        bool operator==(const Vector3& other) const
        {
            constexpr float Epsilon = std::numeric_limits<float>::epsilon();
            return std::fabsf(x - other.x) < Epsilon && std::fabsf(y - other.y) < Epsilon &&
                   std::fabsf(z - other.z) < Epsilon;
        }

        bool operator!=(const Vector3& other) const
        {
            return !(*this == other);
        }

        Vector3 operator+(const Vector3& other) const
        {
            return {x + other.x, y + other.y, z + other.z};
        }

        Vector3 operator-(const Vector3& other) const
        {
            return {x - other.x, y - other.y, z - other.z};
        }

        Vector3 operator-() const
        {
            return {-x, -y, -z};
        }

        Vector3 operator*(float scalar) const
        {
            return {x * scalar, y * scalar, z * scalar};
        }

        Vector3 operator/(float scalar) const
        {
            return {x / scalar, y / scalar, z / scalar};
        }

        float LengthSquared() const
        {
            return x * x + y * y + z * z;
        }

        float Length() const
        {
            return std::sqrtf(LengthSquared());
        }

        void Normalize()
        {
            float len = Length();
            if (len > 0.0f)
            {
                x /= len;
                y /= len;
                z /= len;
            }
        }

        Vector3 Normalized() const
        {
            float len = Length();
            if (len > 0.0f)
            {
                return {x / len, y / len, z / len};
            }
            return *this;
        }

        float Dot(const Vector3& other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }

        Vector3 Cross(const Vector3& other) const
        {
            return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
        }
    };

    inline Vector3 operator*(float scalar, const Vector3& vec)
    {
        return vec * scalar;
    }
}
