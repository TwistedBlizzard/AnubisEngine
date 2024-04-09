#include <iostream>
using std::cout;
using std::endl;

#include "Core.hpp"
#include "Game.hpp"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_CreateWindowAndRenderer(1024, 768, SDL_WINDOW_RESIZABLE, &window, &renderer);

    Game* game = new Game();
    game->Setup(renderer);

    bool should_quit = false;

    while (!game->ShouldQuit())
    {
        SDL_RenderClear(renderer);

        game->Update();
        game->Draw();

        SDL_RenderPresent(renderer);
    }
    
    SDL_Quit();
}