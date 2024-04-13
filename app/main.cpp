#include <iostream>
using std::cout;
using std::endl;

#include "Core.hpp"
#include "Game.hpp"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);

    SDL_Window* window = SDL_CreateWindow("AnubisEngine Demo", 1024, 768, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, 0);

    Game* game = new Game();
    game->Setup(renderer);

    bool should_quit = false;

    while (!game->ShouldQuit())
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        game->Update();
        game->Draw();

        SDL_RenderPresent(renderer);
    }
    
    SDL_Quit();
}