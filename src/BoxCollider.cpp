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

    Transform transform = *m_transform + m_offset;


    topLeft.Rotate(transform.rotation);
    topRight.Rotate(transform.rotation);
    bottomRight.Rotate(transform.rotation);
    bottomLeft.Rotate(transform.rotation);

    Vector2f position = transform.position;

    SDL_FPoint points[]
    {
        position + topLeft,
        position + topRight,
        position + bottomRight,
        position + bottomLeft,
        position + topLeft
    };

    SDL_Color old;
    GetRenderDrawColor(renderer, old);
    SetRenderDrawColor(renderer, m_ColliderColor);
    SDL_RenderLines(renderer, points, 5);
    SetRenderDrawColor(renderer, old);
}

SDL_FRect BoxCollider::GetAABB()
{
    Vector2f bottomRight = m_size / 2;
    Vector2f bottomLeft
    {
        -bottomRight.x,
        bottomRight.y
    };

    Transform transform = *m_transform + m_offset;

    bottomRight.Rotate(transform.rotation);
    bottomLeft.Rotate(transform.rotation);

    bottomRight = bottomRight.Abs();
    bottomLeft = bottomLeft.Abs();

    float w = (bottomRight.x > bottomLeft.x) ? bottomRight.x : bottomLeft.x;
    float h = (bottomRight.y > bottomLeft.y) ? bottomRight.y : bottomLeft.y;

    return SDL_FRect
    {
        transform.position.x - w,
        transform.position.y - h,
        w * 2,
        h * 2
    };
}
