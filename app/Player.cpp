#include "Player.hpp"

Player::Player()
{
    m_transform.position.x = 1024.0f / 2;
    m_transform.position.y = 768.0f / 2;
}

Player::~Player()
{}

void Player::Update(double deltaTime)
{
    GameObject::Update(deltaTime);

    m_transform.rotation += deltaTime * 25.0;
}
