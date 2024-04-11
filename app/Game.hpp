#ifndef GAME_H
#define GAME_H

#include "Core.hpp"
#include "SpriteFactory.hpp"
#include "GameObjectFactory.hpp"
#include "Timing.hpp"
#include "InputHandler.hpp"

class Game
{
public:
    Game();
    ~Game();

    void Setup(SDL_Renderer* renderer);

    void Update();
    void Draw();

    bool ShouldQuit();

private:
    SDL_Renderer* m_renderer;
    Timing* m_timing;
    SpriteFactory* m_spriteFactory;
    GameObjectFactory* m_gameObjectFactory;
    InputHandler* m_inputHandler;
    bool m_quit;
};

#endif // GAME_H