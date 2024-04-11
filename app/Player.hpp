#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"
#include "InputHandler.hpp"

class Player : public GameObject
{
public:
    Player(InputHandler* InputHandler);
    ~Player();

    void Update(double deltaTime) override;

private:
    bool moveLeft;
    bool moveRight;
    bool moveUp;
    bool moveDown;
    bool fire;
    bool special;
    Vector2f mousePos;
};

#endif // PLAYER_H