#include "Player.hpp"

Player::Player()
{
    m_transform.position.x = 1024.0f / 2;
    m_transform.position.y = 768.0f / 2;
}

Player::~Player()
{}

void Player::Update()
{
    GameObject::Update();

    m_transform.rotation += 0.25;
}
