#ifndef VECTOR2F_H
#define VECTOR2F_H

struct Vector2f
{
    float x = 0.0f;
    float y = 0.0f;

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
};

#endif // VECTOR2F_H