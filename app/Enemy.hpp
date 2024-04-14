#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.hpp"

class Enemy : public GameObject
{
public:
    Enemy();
    ~Enemy();

    void Draw(SDL_Renderer* renderer) override;
};

#endif // ENEMY_H