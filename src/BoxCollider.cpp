#include "BoxCollider.hpp"

BoxCollider::BoxCollider(Vector2f size, Transform* transform):
Collider(COLLIDER_BOX, transform),
m_size(size)
{}

BoxCollider::~BoxCollider()
{}

bool BoxCollider::IsColliding(Collider *other)
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

void BoxCollider::SetSize(Vector2f size)
{
    m_size = size;
}

void BoxCollider::DrawCollider(SDL_Renderer *renderer)
{
    Vector2f bottomRight = m_size / 2;

    Vector2f topLeft
    {
        -bottomRight.x,
        -bottomRight.y
    };

    Vector2f topRight
    {
        bottomRight.x,
        topLeft.y
    };

    Vector2f bottomLeft
    {
        topLeft.x,
        bottomRight.y
    };

    topLeft.Rotate(m_transform->rotation);
    topRight.Rotate(m_transform->rotation);
    bottomRight.Rotate(m_transform->rotation);
    bottomLeft.Rotate(m_transform->rotation);

    Vector2f position = m_transform->position;

    SDL_FPoint points[]
    {
        position + topLeft,
        position + topRight,
        position + bottomRight,
        position + bottomLeft,
        position + topLeft
    };

    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderLines(renderer, points, 5);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

SDL_FRect BoxCollider::GetAABB()
{
    Vector2f bottomRight = m_size / 2;
    Vector2f bottomLeft
    {
        -bottomRight.x,
        bottomRight.y
    };

    bottomRight.Rotate(m_transform->rotation);
    bottomLeft.Rotate(m_transform->rotation);

    bottomRight = bottomRight.Abs();
    bottomLeft = bottomLeft.Abs();

    float w = (bottomRight.x > bottomLeft.x) ? bottomRight.x : bottomLeft.x;
    float h = (bottomRight.y > bottomLeft.y) ? bottomRight.y : bottomLeft.y;

    return SDL_FRect
    {
        m_transform->position.x - w,
        m_transform->position.y - h,
        w * 2,
        h * 2
    };
}
