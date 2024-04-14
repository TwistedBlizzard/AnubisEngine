#include "Game.hpp"

Game::Game():
m_quit(false),
m_paused(false),
m_pauseKey(false),
m_lastPauseKey(false),
m_pauseCounter(0.0),
m_player(nullptr),
m_enemy(nullptr)
{}

Game::~Game()
{}

void Game::Setup()
{
    Engine::spriteFactory->LoadTexture("Ship 1", "img/Ship1.png");
    Engine::spriteFactory->LoadTexture("Ship 2", "img/Ship2.png");

    m_player = Engine::gameObjectFactory->Create<Player>("Ship 1");
    m_enemy = Engine::gameObjectFactory->Create<Enemy>("Ship 2");

    Engine::inputHandler->RegisterValue(KEYBOARD, "Delete", &m_pauseKey);

    Engine::timing->Init();
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

        Engine::inputHandler->HandleEvent(event);
    }

    Engine::timing->Update();

    bool unpaused = false;

    // Check if the pause key was just pressed
    if (m_pauseKey && !m_lastPauseKey)
    {
        m_paused = !m_paused;
        m_lastPauseKey = true;

        if (m_paused)
        {
            Engine::timing->Pause();
        }
        else
        {
            Engine::timing->Unpause();
            unpaused = true;
        }
    }
    else if (m_lastPauseKey && !m_pauseKey)
    {
        // Pause key was released
        m_lastPauseKey = false;
    }

    m_pauseCounter += Engine::timing->PausedTime();

    double deltaTime = Engine::timing->DeltaTime();

    if (unpaused)
    {
        cout << "Paused for " << m_pauseCounter << " seconds" << endl;
        m_pauseCounter = 0.0;
    }

    Engine::gameObjectFactory->Update(deltaTime);

    m_player->CheckCollision(m_enemy->GetCollider());
}

void Game::Draw()
{
    Engine::gameObjectFactory->Draw(Engine::renderer);
}

bool Game::ShouldQuit()
{
    return m_quit;
}
