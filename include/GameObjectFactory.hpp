#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <typeindex>
using std::type_index;

#include "Core.hpp"
#include "SpriteFactory.hpp"
#include "GameObject.hpp"

class IFactory
{
public:
    IFactory() {}
    ~IFactory() {}

    virtual GameObject* Create() = 0;
};

template <class T>
class Factory : public IFactory
{
public:
    GameObject* Create() override {return new T();}
};

class GameObjectFactory
{
public:
    GameObjectFactory(SpriteFactory* spriteFactory);
    ~GameObjectFactory();

    template <class T>
    GameObject* Create(string spriteName) 
    {
        type_index id = typeid(T);

        if(!m_factories.contains(id))
        {
            m_factories[id] = new Factory<T>();
        }

        GameObject* go =  m_factories[id]->Create();

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
    map<type_index, IFactory*> m_factories;
    vector<GameObject*> m_gameObjects;
};


#endif // GAMEOBJECTFACTORY_H
