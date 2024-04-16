#include "Player.hpp"

// Move speed
#define PLAYER_SPEED 200.0f

// Look threshold
#define PLAYER_LOOK_THRESHOLD 0.25f

// Collider size
#define PLAYER_COLLIDER_WIDTH 96.0f
#define PLAYER_COLLIDER_HEIGHT 128.0f

// Collision pause time
#define PLAYER_COLLISION_TIME 1.0

// Action delays
#define PLAYER_FIRE_DELAY 0.5
#define PLAYER_SPECIAL_DELAY 10.0

// Action threshold
#define PLAYER_ACTION_THRESHOLD 0.5f

Player::Player():
moveLeft(false),
moveRight(false),
moveUp(false),
moveDown(false),
mFire(false),
mSpecial(false),
gFire(0.0f),
gSpecial(0.0f),
m_colliding(false),
m_pauseTimer(0.0)
{
    m_transform.position.x = 1024.0f / 2;
    m_transform.position.y = 768.0f / 2;

    Engine::inputHandler->RegisterValue(KEYBOARD, "A", &moveLeft);
    Engine::inputHandler->RegisterValue(KEYBOARD, "D", &moveRight);
    Engine::inputHandler->RegisterValue(KEYBOARD, "W", &moveUp);
    Engine::inputHandler->RegisterValue(KEYBOARD, "S", &moveDown);
    Engine::inputHandler->RegisterValue(MOUSE_POSITION, &mousePos);
    Engine::inputHandler->RegisterValue(MOUSE_POSITION, &mouseMotion);
    Engine::inputHandler->RegisterValue(MOUSE_BUTTON, "Left", &mFire);
    Engine::inputHandler->RegisterValue(MOUSE_BUTTON, "Right", &mSpecial);
    Engine::inputHandler->RegisterValue(GAMEPAD_LEFT_STICK, &moveAxis);
    Engine::inputHandler->RegisterValue(GAMEPAD_RIGHT_STICK, &lookAxis);
    Engine::inputHandler->RegisterValue(GAMEPAD_RIGHT_TRIGGER, &gFire);
    Engine::inputHandler->RegisterValue(GAMEPAD_LEFT_TRIGGER, &gSpecial);

    Engine::inputHandler->SetThreshold("RightX", PLAYER_LOOK_THRESHOLD);
    Engine::inputHandler->SetThreshold("RightY", PLAYER_LOOK_THRESHOLD);

    Vector2f colliderSize = { PLAYER_COLLIDER_WIDTH, PLAYER_COLLIDER_HEIGHT };
    m_collider = new BoxCollider(colliderSize, &m_transform);

    m_fireTimer = Timer(PLAYER_FIRE_DELAY);
    m_specialTimer = Timer(PLAYER_SPECIAL_DELAY);
}

Player::~Player()
{}

void Player::Update(double deltaTime)
{
    GameObject::Update(deltaTime);

    UpdatePauseTimer();
    UpdatePosition(deltaTime);
    UpdateRotation();
    UpdateFire(deltaTime);
    UpdateSpecial(deltaTime);
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

void Player::UpdatePauseTimer()
{
    if (Engine::timing->Paused())
        m_pauseTimer += Engine::timing->PausedTime();

    if (m_pauseTimer >= PLAYER_COLLISION_TIME)
    {
        Engine::timing->Unpause();
        m_pauseTimer = 0.0;
    }
}

void Player::UpdatePosition(double deltaTime)
{
    Vector2f velocity = moveAxis;
    if (moveLeft)
        velocity.x -= 1.0f;
    if (moveRight)
        velocity.x += 1.0f;
    if (moveUp)
        velocity.y -= 1.0f;
    if (moveDown)
        velocity.y += 1.0f;

    if (velocity.Magnitude() > 1.0f)
        velocity.Normalise();

    m_transform.position += velocity * deltaTime * PLAYER_SPEED;
}

void Player::UpdateRotation()
{
    if (Engine::timing->Paused())
        return;

    if (mouseMotion)
    {
        Vector2f lookDir = mousePos - m_transform.position;
        m_transform.rotation = lookDir.Angle();
    }
    else
    {
        m_transform.rotation = lookAxis.Angle();
    }    
}

void Player::UpdateFire(double deltaTime)
{
    m_fireTimer.Update(deltaTime);

    if (!m_fireTimer)
        return;

    if (mFire || gFire > PLAYER_ACTION_THRESHOLD)
    {
        cout << "Fire!" << endl;
        m_fireTimer.Reset();
    }
}

void Player::UpdateSpecial(double deltaTime)
{
    m_specialTimer.Update(deltaTime);

    if (!m_specialTimer)
        return;
        
    if (mSpecial || gSpecial > PLAYER_ACTION_THRESHOLD)
    {
        cout << "Special!" << endl;
        m_specialTimer.Reset();
    }
}
