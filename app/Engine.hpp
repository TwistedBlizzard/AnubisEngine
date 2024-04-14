#ifndef ENGINE_H
#define ENGINE_H

#include "Core.hpp"

#include "Timing.hpp"
#include "GameObjectFactory.hpp"
#include "InputHandler.hpp"
#include "SpriteFactory.hpp"

class Engine
{
public:
    static SDL_Renderer* renderer;
    static Timing* timing;
    static SpriteFactory* spriteFactory;
    static GameObjectFactory* gameObjectFactory;
    static InputHandler* inputHandler;

    static void AutoInit(SDL_Window* window);

private:
    static bool s_initialised;
};

#endif // ENGINE_H