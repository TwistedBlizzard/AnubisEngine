#include "Player.hpp"

Player::Player():
moveLeft(false),
moveRight(false),
moveUp(false),
moveDown(false),
fire(false),
special(false),
m_colliding(false),
m_pauseTimer(0.0)
{
    m_transform.position.x = 1024.0f / 2;
    m_transform.position.y = 768.0f / 2;

    Engine::inputHandler->RegisterValue(KEYBOARD, "A", &moveLeft);
    Engine::inputHandler->RegisterValue(KEYBOARD, "D", &moveRight);
    Engine::inputHandler->RegisterValue(KEYBOARD, "W", &moveUp);
    Engine::inputHandler->RegisterValue(KEYBOARD, "S", &moveDown);
    Engine::inputHandler->RegisterValue(MOUSE_BUTTON, "Left", &fire);
    Engine::inputHandler->RegisterValue(MOUSE_BUTTON, "Right", &special);
    Engine::inputHandler->RegisterValue(MOUSE_POSITION, &mousePos);

    m_collider = new BoxCollider({96.0f, 128.0f}, &m_transform);
}

Player::~Player()
{}

void Player::Update(double deltaTime)
{
    if (Engine::timing->Paused())
        m_pauseTimer += Engine::timing->PausedTime();

    if (m_pauseTimer >= 1.0)
    {
        Engine::timing->Unpause();
        m_pauseTimer = 0.0;
    }

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

void Player::CheckCollision(Collider *collider)
{
    if (Engine::timing->Paused())
        return;

    bool colliding = m_collider->IsColliding(collider);

    if (colliding && !m_colliding)
    {
        // We just started colliding
        Engine::timing->Pause();
        m_colliding = true;
        m_collider->SetAABBColor(COLOR_RED);
    }
    else if(!colliding && m_colliding)
    {
        // We just stopped colliding
        m_colliding = false;
        m_collider->SetAABBColor(COLOR_GREEN);
    }
}
