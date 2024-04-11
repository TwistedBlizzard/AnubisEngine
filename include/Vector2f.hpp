#ifndef VECTOR2F_H
#define VECTOR2F_H

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
};

#endif // VECTOR2F_H