#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <Core.hpp>

using std::ostream;

struct Vector2f
{
    float x = 0.0f;
    float y = 0.0f;

    Vector2f()
    {
        x = 0.0f;
        y = 0.0f;
    }

    Vector2f(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    static Vector2f FromAngle(const float& angle, const float& magnitude)
    {
        const float radians = Radians(angle);

        Vector2f vector
        {
            cosf(radians) * magnitude,
            sinf(radians) * magnitude
        };

        return vector;
    }

    Vector2f operator+(const Vector2f& rhs)
    {
        return Vector2f
        {
            x + rhs.x,
            y + rhs.y
        };
    }

    Vector2f operator-(const Vector2f& rhs)
    {
        return Vector2f
        {
            x - rhs.x,
            y - rhs.y
        };
    }

    Vector2f operator*(const float& rhs)
    {
        return Vector2f
        {
            x * rhs,
            y * rhs
        };
    }

    Vector2f operator/(const float& rhs)
    {
        return Vector2f
        {
            x / rhs,
            y / rhs
        };
    }

    Vector2f operator+=(const Vector2f& rhs)
    {
        return Vector2f
        {
            x += rhs.x,
            y += rhs.y
        };
    }

    Vector2f operator-=(const Vector2f& rhs)
    {
        return Vector2f
        {
            x -= rhs.x,
            y -= rhs.y
        };
    }

    Vector2f operator*=(const float& rhs)
    {
        return Vector2f
        {
            x *= rhs,
            y *= rhs
        };
    }

    Vector2f operator/=(const float& rhs)
    {
        return Vector2f
        {
            x /= rhs,
            y /= rhs
        };
    }

    float SqMagnitude()
    {
        return (x * x) + (y * y);
    }

    float Magnitude()
    {
        return sqrtf(SqMagnitude());
    }

    Vector2f Normalised()
    {
        float magnitude = Magnitude();
        
        if (magnitude > 0.0f)
            return *this / magnitude;

        return Vector2f(0.0f, 0.0f);
    }

    void Normalise()
    {
        Vector2f vector = Normalised();

        x = vector.x;
        y = vector.y;
    }

    float Distance(const Vector2f& other)
    {
        Vector2f offset
        {
            x - other.x,
            y - other.y
        };

        return offset.Magnitude();
    }

    float Angle()
    {
        float angle = atan2f(y, x);

        return Degrees(angle) + 90.0f;
    }

    void SetRotation(const float& degrees)
    {
        float angle = Radians(90.0f - degrees);
        __SetRotation(angle);
    }

    void Rotate(const float& degrees)
    {
        float angle = Radians(degrees) + atan2f(y, x);
        __SetRotation(angle);
    }

    void RotateAround(const float& degrees, const Vector2f& point)
    {
        Vector2f vector
        {
            x - point.x,
            y - point.y
        };

        vector.Rotate(degrees);

        x = vector.x + point.x;
        y = vector.y + point.y;
    }

    Vector2f Abs()
    {
        return Vector2f
        {
            fabsf(x),
            fabsf(y)
        };
    }

    void __SetRotation(float angle)
    {
        float magnitude = Magnitude();

        x = magnitude * cosf(angle);
        y = magnitude * sinf(angle);
    }

    operator SDL_FPoint()
    {
        return SDL_FPoint
        {
            x,
            y
        };
    }
};


// Adapted from https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes
// and https://stackoverflow.com/questions/12802536/c-multiple-definitions-of-operator
inline ostream& operator<<(ostream& os, const Vector2f& vector)
{
    os << vector.x << ", " << vector.y;
    return os;
}

#endif // VECTOR2F_H