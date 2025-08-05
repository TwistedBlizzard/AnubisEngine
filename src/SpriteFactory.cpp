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
        cout << "Error: A texture already exists with name: " << name << endl;
        return;
    }

    SDL_Surface* surface = IMG_Load(filename.c_str());

    if (surface)
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        m_textures[name] = texture;
    }
    else
    {
        cout << "Error: Failed to load texture: " << filename << endl;
        return;
    }

    SDL_DestroySurface(surface);
}

Sprite *SpriteFactory::Create(string name, Vector2f size)
{
    if (!m_textures.contains(name))
    {
        cout << "Error: Texture does not exist: " << name << endl;
        return nullptr;
    }

    SDL_Texture* texture = m_textures[name];
    const auto w = static_cast<float>(texture->w);
    const auto h = static_cast<float>(texture->h);
    SDL_FRect source
    {
        0.0f,
        0.0f,
        w,
        h
    };

    Sprite* sprite = new Sprite();
    sprite->SetTexture(texture);
    sprite->SetSize(size);
    sprite->SetSource(source);

    return sprite;
}
