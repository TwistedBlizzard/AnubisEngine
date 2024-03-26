#include "GameObjectFactory.hpp"

GameObjectFactory::GameObjectFactory(SpriteFactory* spriteFactory):
m_spriteFactory(spriteFactory)
{}

GameObjectFactory::~GameObjectFactory()
{}

void GameObjectFactory::Update()
{
    for (GameObject* go : m_gameObjects)
        go->Update();
}

void GameObjectFactory::Draw(SDL_Renderer *renderer)
{
    for (GameObject* go : m_gameObjects)
        go->Draw(renderer);
}
