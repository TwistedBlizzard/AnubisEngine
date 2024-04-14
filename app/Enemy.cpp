#include "Enemy.hpp"

#include "BoxCollider.hpp"

Enemy::Enemy():
GameObject()
{
    m_transform.position.x = 1024.0f / 3;
    m_transform.position.y = 768.0f / 2;

    m_collider = new BoxCollider({128.0f, 128.0f}, &m_transform);
}

Enemy::~Enemy()
{}

void Enemy::Draw(SDL_Renderer *renderer)
{
    GameObject::Draw(renderer);

    m_collider->DrawAABB(renderer);
}
