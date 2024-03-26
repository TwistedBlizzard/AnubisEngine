#ifndef GAME_H
#define GAME_H

#include "Core.hpp"
#include "SpriteFactory.hpp"
#include "GameObjectFactory.hpp"
#include "InputMapParser.hpp"

class Game
{
public:
    Game();
    ~Game();

    void Setup(SDL_Renderer* renderer);

    void Update();
    void Draw();

private:
    SDL_Renderer* m_renderer;
    SpriteFactory* m_spriteFactory;
    GameObjectFactory* m_gameObjectFactory;
};

#endif // GAME_H