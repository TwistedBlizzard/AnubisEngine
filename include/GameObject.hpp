#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Core.hpp"

#include "Transform.hpp"
#include "Sprite.hpp"

class GameObject
{
public:
    GameObject();
    ~GameObject();

    virtual void Update();

    Transform& GetTransform();
    Vector2f& GetPosition();
    double& GetRotation();

    Sprite* GetSprite();
    void SetSprite(Sprite* sprite);

    virtual void Draw(SDL_Renderer* renderer);

    // Operators for casts, etc.
    operator Transform();
    operator Transform*();

protected:
    Transform m_transform;
    Sprite* m_sprite;
};

#endif // GAMEOBJECT_H