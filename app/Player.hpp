#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"

class Player : public GameObject
{
public:
    Player();
    ~Player();

    void Update(double deltaTime) override;

private:
};

#endif // PLAYER_H