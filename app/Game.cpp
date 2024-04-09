#include "Game.hpp"

#include "Player.hpp"

Game::Game():
m_renderer(nullptr),
m_spriteFactory(nullptr),
m_gameObjectFactory(nullptr),
m_quit(false)
{}

Game::~Game()
{}

void Game::Setup(SDL_Renderer* renderer)
{
    m_renderer = renderer;

    m_timing = new Timing();
    m_timing->Init();

    m_spriteFactory = new SpriteFactory(renderer);
    m_gameObjectFactory = new GameObjectFactory(m_spriteFactory);

    m_spriteFactory->LoadTexture("Ship 1", "img/Ship1.png");
    m_spriteFactory->LoadTexture("Ship 2", "img/Ship2.png");

    GameObject* player1 = m_gameObjectFactory->Create<Player>("Ship 1");
}

void Game::Update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            m_quit = true;
            continue;
        }
    }

    m_timing->Update();

    double deltaTime = m_timing->DeltaTime();

    m_gameObjectFactory->Update(deltaTime);
}

void Game::Draw()
{
    m_gameObjectFactory->Draw(m_renderer);
}

bool Game::ShouldQuit()
{
    return m_quit;
}
