#pragma once

#include "Vector3.hpp"

#include <cmath>
#include <limits>

namespace RayTracer
{
    struct Vector4
    {
        float x;
        float y;
        float z;
        float w;

        constexpr Vector4() noexcept
            : x{0}
            , y{0}
            , z{0}
            , w{0}
        {
        }

        constexpr Vector4(float x, float y, float z, float w) noexcept
            : x{x}
            , y{y}
            , z{z}
            , w{w}
        {
        }

        constexpr Vector4(const Vector3& vec3, float w) noexcept
            : x{vec3.x}
            , y{vec3.y}
            , z{vec3.z}
            , w{w}
        {
        }

        bool operator==(const Vector4& other) const
        {
            constexpr float Epsilon = std::numeric_limits<float>::epsilon();
            return std::fabsf(x - other.x) < Epsilon && std::fabsf(y - other.y) < Epsilon &&
                   std::fabsf(z - other.z) < Epsilon && std::fabsf(w - other.w) < Epsilon;
        }

        bool operator!=(const Vector4& other) const
        {
            return !(*this == other);
        }

        Vector4 operator+(const Vector4& other) const
        {
            return {x + other.x, y + other.y, z + other.z, w + other.w};
        }

        Vector4 operator-(const Vector4& other) const
        {
            return {x - other.x, y - other.y, z - other.z, w - other.w};
        }

        Vector4 operator-() const
        {
            return {-x, -y, -z, -w};
        }

        Vector4 operator*(float scalar) const
        {
            return {x * scalar, y * scalar, z * scalar, w * scalar};
        }

        Vector4 operator/(float scalar) const
        {
            return {x / scalar, y / scalar, z / scalar, w / scalar};
        }

        float LengthSquared() const
        {
            return x * x + y * y + z * z + w * w;
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
                w /= len;
            }
        }

        Vector4 Normalized() const
        {
            float len = Length();
            if (len > 0.0f)
            {
                return {x / len, y / len, z / len, w / len};
            }
            return *this;
        }

        float Dot(const Vector4& other) const
        {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }
    };

    inline Vector4 operator*(float scalar, const Vector4& vec)
    {
        return vec * scalar;
    }
}
