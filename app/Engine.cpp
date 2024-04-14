#include "Engine.hpp"

SDL_Renderer* Engine::renderer = nullptr;
Timing* Engine::timing = nullptr;
SpriteFactory* Engine::spriteFactory = nullptr;
GameObjectFactory* Engine::gameObjectFactory = nullptr;
InputHandler* Engine::inputHandler = nullptr;

bool Engine::s_initialised = false;

void Engine::AutoInit(SDL_Window *window)
{
    if (s_initialised)
        return;

    renderer = SDL_CreateRenderer(window, NULL, 0);
    timing = new Timing();
    spriteFactory = new SpriteFactory(renderer);
    gameObjectFactory = new GameObjectFactory(spriteFactory);
    inputHandler = new InputHandler();

    s_initialised = true;
}