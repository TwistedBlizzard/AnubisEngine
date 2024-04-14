#include "Collider.hpp"

Collider::Collider(ColliderType type, Transform* transform):
m_type(type),
m_transform(transform),
m_AABBColor(COLOR_GREEN),
m_ColliderColor(COLOR_YELLOW)
{}

Collider::~Collider()
{}

void Collider::DrawAABB(SDL_Renderer *renderer)
{
    SDL_FRect rect = GetAABB();

    SDL_Color old;
    GetRenderDrawColor(renderer, old);
    SetRenderDrawColor(renderer, m_AABBColor);
    SDL_RenderRect(renderer, &rect);
    SetRenderDrawColor(renderer, old);
}

void Collider::SetAABBColor(SDL_Color color)
{
    m_AABBColor = color;
}

void Collider::SetColliderColor(SDL_Color color)
{
    m_ColliderColor = color;
}

bool Collider::CheckAABB(Collider *other)
{
    SDL_FRect thisAABB = GetAABB();
    SDL_FRect otherAABB = other->GetAABB();

    // Adapted for SDL from https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection

    // collision x-axis?
    bool collisionX = thisAABB.x + thisAABB.w >= otherAABB.x &&
        otherAABB.x + otherAABB.w >= thisAABB.x;
    // collision y-axis?
    bool collisionY = thisAABB.y + thisAABB.h >= otherAABB.y &&
        otherAABB.y + otherAABB.h >= thisAABB.y;
    // collision only if on both axes
    return collisionX && collisionY;
}