#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Collider.hpp"

class BoxCollider : public Collider
{
public:
    BoxCollider(Vector2f size, Transform* transform);
    ~BoxCollider();

    bool IsColliding(Collider* other) override;

    void SetSize(Vector2f size);

    void DrawCollider(SDL_Renderer* renderer) override;

protected:
    Vector2f m_size;

    SDL_FRect GetAABB() override;
};

#endif // BOXCOLLIDER_H