#include "Game.hpp"

#include "Player.hpp"

Game::Game():
m_renderer(nullptr),
m_timing(nullptr),
m_spriteFactory(nullptr),
m_gameObjectFactory(nullptr),
m_inputHandler(nullptr),
m_quit(false),
m_paused(false),
m_pauseKey(false),
m_lastPauseKey(false),
m_pauseCounter(0.0)
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

    m_inputHandler = new InputHandler();
    
    GameObject* go = m_gameObjectFactory->Create<Player>("Ship 1", m_inputHandler);

    m_inputHandler->RegisterValue(KEYBOARD, "Delete", &m_pauseKey);
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

        m_inputHandler->HandleEvent(event);
    }

    m_timing->Update();

    bool unpaused = false;

    // Check if the pause key was just pressed
    if (m_pauseKey && !m_lastPauseKey)
    {
        m_paused = !m_paused;
        m_lastPauseKey = true;

        if (m_paused)
        {
            m_timing->Pause();
        }
        else
        {
            m_timing->Unpause();
            unpaused = true;
        }
    }
    else if (m_lastPauseKey && !m_pauseKey)
    {
        // Pause key was released
        m_lastPauseKey = false;
    }

    m_pauseCounter += m_timing->PausedTime();

    double deltaTime = m_timing->DeltaTime();

    if (unpaused)
    {
        cout << "Paused for " << m_pauseCounter << " seconds" << endl;
        m_pauseCounter = 0.0;
    }

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
