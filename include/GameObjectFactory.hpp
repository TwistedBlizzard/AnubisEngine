#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <typeindex>
using std::type_index;

#include "Core.hpp"
#include "SpriteFactory.hpp"
#include "GameObject.hpp"

class GameObjectFactory
{
public:
    GameObjectFactory(SpriteFactory* spriteFactory);
    ~GameObjectFactory();

    template <class T, class... A>
    GameObject* Create(string spriteName, A... args) 
    {

        GameObject* go = new T(args...);
        Vector2f size {128.0f, 128.0f};

        Sprite* sprite = m_spriteFactory->Create(spriteName, size);

        go->SetSprite(sprite);
        m_gameObjects.push_back(go);
        return go;
    }

    void Update(double deltaTime);

    void Draw(SDL_Renderer* renderer);

private:
    SpriteFactory* m_spriteFactory;
    vector<GameObject*> m_gameObjects;
};


#endif // GAMEOBJECTFACTORY_H
