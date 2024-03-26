#include "Game.hpp"

#include "Player.hpp"

Game::Game():
m_renderer(nullptr),
m_spriteFactory(nullptr),
m_gameObjectFactory(nullptr)
{}

Game::~Game()
{}

void Game::Setup(SDL_Renderer* renderer)
{
    InputMapParser::Parse("InputMap.conf");

    m_renderer = renderer;
    
    m_spriteFactory = new SpriteFactory(renderer);
    m_gameObjectFactory = new GameObjectFactory(m_spriteFactory);

    m_spriteFactory->LoadTexture("Ship 1", "img/Ship1.png");
    m_spriteFactory->LoadTexture("Ship 2", "img/Ship2.png");

    GameObject* player1 = m_gameObjectFactory->Create<Player>("Ship 1");
}

void Game::Update()
{
    m_gameObjectFactory->Update();
}

void Game::Draw()
{
    m_gameObjectFactory->Draw(m_renderer);
}
