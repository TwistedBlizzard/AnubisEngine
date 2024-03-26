#include "SpriteFactory.hpp"

SpriteFactory::SpriteFactory(SDL_Renderer* renderer):
m_renderer(renderer)
{}

SpriteFactory::~SpriteFactory()
{}

void SpriteFactory::LoadTexture(string name, string filename)
{
    if (m_textures.contains(name))
    {
        cout << name << " is already a texture" << endl;
    }

    SDL_Surface* surface = IMG_Load(filename.c_str());

    if (surface)
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        m_textures[name] = texture;
    }
    else
    {
        cout << "Failed to load texture: " << filename << endl;
    }

    SDL_DestroySurface(surface);
}

Sprite *SpriteFactory::Create(string name, Vector2f size)
{
    if (!m_textures.contains(name))
    {
        cout << "Texture \"" << name << "\" does not exist" << endl;
    }

    SDL_Texture* texture = m_textures[name];
    int x, y;
    SDL_QueryTexture(texture, NULL, NULL, &x, &y);
    SDL_FRect source
    {
        0.0f,
        0.0f,
        (float)x,
        (float)y
    };

    Sprite* sprite = new Sprite();
    sprite->SetTexture(texture);
    sprite->SetSize(size);
    sprite->SetSource(source);

    return sprite;
}
