#include "Collider.hpp"

Collider::Collider(ColliderType type, Transform* transform):
m_type(type),
m_transform(transform)
{}

Collider::~Collider()
{}

void Collider::DrawAABB(SDL_Renderer *renderer)
{
    SDL_FRect rect = GetAABB();

    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
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