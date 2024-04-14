#ifndef PLAYER_H
#define PLAYER_H

#include "Engine.hpp"
#include "GameObject.hpp"
#include "BoxCollider.hpp"

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
    bool fire;
    bool special;
    Vector2f mousePos;

    bool m_colliding;
    double m_pauseTimer;
};

#endif // PLAYER_H