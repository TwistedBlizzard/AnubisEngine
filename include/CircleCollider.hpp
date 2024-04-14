#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "Collider.hpp"

class CircleCollider : public Collider
{
public:
    CircleCollider(float radius, Transform* transform);
    ~CircleCollider();

    bool IsColliding(Collider* other) override;

    void SetRadius(float radius);

    void DrawCollider(SDL_Renderer* renderer) override;

protected:
    float m_radius;

    SDL_FRect GetAABB() override;
};

#endif // CIRCLECOLLIDER_H