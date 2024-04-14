#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Core.hpp"

#include "Transform.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"

class GameObject
{
public:
    GameObject();
    ~GameObject();

    virtual void Update(double deltaTime);

    Transform& GetTransform();
    Vector2f& GetPosition();
    double& GetRotation();

    Sprite* GetSprite();
    void SetSprite(Sprite* sprite);

    Collider* GetCollider();

    virtual void Draw(SDL_Renderer* renderer);

    // Operators for casts, etc.
    operator Transform();
    operator Transform*();

protected:
    Transform m_transform;
    Sprite* m_sprite;
    Collider* m_collider;
};

#endif // GAMEOBJECT_H