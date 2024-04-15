#ifndef COLLIDER_H
#define COLLIDER_H

#include "Core.hpp"
#include "Transform.hpp"

enum ColliderType
{
    COLLIDER_CIRCLE,
    COLLIDER_BOX
};

class Collider
{
public:
    Collider(ColliderType type, Transform* transform);
    virtual ~Collider();

    virtual bool IsColliding(Collider* other) = 0;

    ColliderType GetType() { return m_type; }

    void SetOffset(const Transform& offset);
    void SetPositionOffset(const Vector2f& offset);
    void SetRotationOffset(const float& offset);

    void DrawAABB(SDL_Renderer* renderer);
    virtual void DrawCollider(SDL_Renderer* renderer) {}

    void SetAABBColor(SDL_Color color);
    void SetColliderColor(SDL_Color color);

protected:
    ColliderType m_type;

    Transform* m_transform;
    Transform m_offset;

    virtual SDL_FRect GetAABB() = 0;
    bool CheckAABB(Collider* other);

    SDL_Color m_AABBColor;
    SDL_Color m_ColliderColor;
};

#endif // COLLIDER_H