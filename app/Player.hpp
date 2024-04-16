#ifndef PLAYER_H
#define PLAYER_H

#include "Engine.hpp"
#include "GameObject.hpp"
#include "BoxCollider.hpp"
#include "Timer.hpp"

class Player : public GameObject
{
public:
    Player();
    ~Player();

    void Update(double deltaTime) override;

    void Draw(SDL_Renderer* renderer) override;

    void CheckCollision(Collider* collider);

private:
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;
    Vector2f mousePos;
    bool mouseMotion;
    bool mFire;
    bool mSpecial;
    Vector2f moveAxis;
    Vector2f lookAxis;
    float gFire;
    float gSpecial;

    bool m_colliding;
    double m_pauseTimer;

    Timer m_fireTimer;
    Timer m_specialTimer;

    void UpdatePauseTimer();
    void UpdatePosition(double deltaTime);
    void UpdateRotation();
    void UpdateFire(double deltaTime);
    void UpdateSpecial(double deltaTime);
};

#endif // PLAYER_H