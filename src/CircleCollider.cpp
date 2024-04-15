#include "CircleCollider.hpp"

CircleCollider::CircleCollider(float radius, Transform* transform):
Collider(COLLIDER_CIRCLE, transform),
m_radius(radius)
{}

CircleCollider::~CircleCollider()
{}

bool CircleCollider::IsColliding(Collider *other)
{
    if (!CheckAABB(other))
        return false;

    switch (other->GetType())
    case COLLIDER_CIRCLE:
    case COLLIDER_BOX:
    default:
        break;
    
    return true;
}

void CircleCollider::SetRadius(float radius)
{
    m_radius = radius;
}

void CircleCollider::DrawCollider(SDL_Renderer *renderer)
{
    Transform transform = *m_transform + m_offset;

    SDL_FPoint points[37];

    for (int i = 0; i < 36; i++)
    {
        float angle = Radians(i * 10);
        float x = cosf(angle) * m_radius;
        float y = sinf(angle) * m_radius;

        points[i] = transform.position + Vector2f(x, y);
    }

    points[36] = points[0];

    SDL_Color old;
    GetRenderDrawColor(renderer, old);
    SetRenderDrawColor(renderer, m_ColliderColor);
    SDL_RenderLines(renderer, points, 37);
    SetRenderDrawColor(renderer, old);
}

SDL_FRect CircleCollider::GetAABB()
{
    Transform transform = *m_transform + m_offset;

    SDL_FRect boundingBox
    {
        transform.position.x - m_radius,
        transform.position.y - m_radius,
        m_radius * 2,
        m_radius * 2
    };

    return boundingBox;
}
