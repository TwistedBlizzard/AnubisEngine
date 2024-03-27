#include "GameObject.hpp"

GameObject::GameObject():
m_sprite(nullptr)
{}

GameObject::~GameObject()
{}

void GameObject::Update(double deltaTime)
{
    // Do nothing for now
}

Transform& GameObject::GetTransform()
{
    return m_transform;
}

Vector2f &GameObject::GetPosition()
{
    return m_transform.position;
}

double &GameObject::GetRotation()
{
    return m_transform.rotation;
}

Sprite *GameObject::GetSprite()
{
    return m_sprite;
}

void GameObject::SetSprite(Sprite *sprite)
{
    m_sprite = sprite;
}

void GameObject::Draw(SDL_Renderer *renderer)
{
    // Check if we have a sprite
    if(!m_sprite)
        return;

    m_sprite->Draw(renderer, m_transform.position, m_transform.rotation);
}

GameObject::operator Transform()
{
    return m_transform;
}

GameObject::operator Transform *()
{
    return &m_transform;
}
