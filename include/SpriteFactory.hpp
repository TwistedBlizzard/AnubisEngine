#ifndef SPRITEFACTORY_H
#define SPRITEFACTORY_H

#include "Core.hpp"

#include "Sprite.hpp"

class SpriteFactory
{
public:
    SpriteFactory(SDL_Renderer* renderer);
    ~SpriteFactory();

    void LoadTexture(string name, string filename);

    Sprite* Create(string name, Vector2f size);

private:
    SDL_Renderer* m_renderer;
    map<string, SDL_Texture*> m_textures;
};

#endif // SPRITEFACTORY_H