#include "Player.hpp"

Player::Player(InputHandler* inputHandler):
moveLeft(false),
moveRight(false),
moveUp(false),
moveDown(false),
fire(false),
special(false)
{
    m_transform.position.x = 1024.0f / 2;
    m_transform.position.y = 768.0f / 2;

    inputHandler->RegisterValue(KEYBOARD, "A", &moveLeft);
    inputHandler->RegisterValue(KEYBOARD, "D", &moveRight);
    inputHandler->RegisterValue(KEYBOARD, "W", &moveUp);
    inputHandler->RegisterValue(KEYBOARD, "S", &moveDown);
    inputHandler->RegisterValue(MOUSE_BUTTON, "Left", &fire);
    inputHandler->RegisterValue(MOUSE_BUTTON, "Right", &special);
    inputHandler->RegisterValue(MOUSE_POSITION, &mousePos);

    m_collider = new CircleCollider(64.0f, &m_transform);
}

Player::~Player()
{}

void Player::Update(double deltaTime)
{
    GameObject::Update(deltaTime);

    m_transform.rotation += deltaTime * 25.0;

    Vector2f velocity;
    if (moveLeft)
        velocity.x -= 1.0f;
    if (moveRight)
        velocity.x += 1.0f;
    if (moveUp)
        velocity.y -= 1.0f;
    if (moveDown)
        velocity.y += 1.0f;

    velocity.Normalise();

    float speed = 100.0f;

    m_transform.position += velocity * deltaTime * speed;
}

void Player::Draw(SDL_Renderer *renderer)
{
    GameObject::Draw(renderer);

    m_collider->DrawCollider(renderer);
    m_collider->DrawAABB(renderer);
}
