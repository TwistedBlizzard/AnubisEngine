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
    SDL_FPoint points[37];

    for (int i = 0; i < 36; i++)
    {
        float angle = Radians(i * 10);
        float x = cosf(angle) * m_radius;
        float y = sinf(angle) * m_radius;

        points[i] = m_transform->position + Vector2f(x, y);
    }

    points[36] = points[0];

    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderLines(renderer, points, 37);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

SDL_FRect CircleCollider::GetAABB()
{
    SDL_FRect boundingBox
    {
        m_transform->position.x - m_radius,
        m_transform->position.y - m_radius,
        m_radius * 2,
        m_radius * 2
    };

    return boundingBox;
}
