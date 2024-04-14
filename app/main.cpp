#include <iostream>
using std::cout;
using std::endl;

#include "Core.hpp"
#include "Engine.hpp"
#include "Game.hpp"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);

    SDL_Window* window = SDL_CreateWindow("AnubisEngine Demo", 1024, 768, SDL_WINDOW_RESIZABLE);
    Engine::AutoInit(window);

    Game* game = new Game();
    game->Setup();

    bool should_quit = false;

    while (!game->ShouldQuit())
    {
        SetRenderDrawColor(Engine::renderer, COLOR_BLACK);
        SDL_RenderClear(Engine::renderer);

        game->Update();
        game->Draw();

        SDL_RenderPresent(Engine::renderer);
    }
    
    SDL_Quit();
}