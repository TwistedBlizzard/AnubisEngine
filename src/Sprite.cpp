#include "Sprite.hpp"

Sprite::Sprite()
{}

Sprite::~Sprite()
{}

void Sprite::SetTexture(SDL_Texture *texture)
{
    m_texture = texture;
}

void Sprite::SetSize(Vector2f size)
{
    m_size = size;
}

void Sprite::SetSource(SDL_FRect source)
{
    m_source = source;
}

void Sprite::Draw(SDL_Renderer *renderer, Vector2f position, double rotation)
{
    position -= m_size / 2.0f;

    SDL_FRect destination
    {
        position.x,
        position.y,
        m_size.x,
        m_size.y
    };

    SDL_RenderTextureRotated(renderer, m_texture, &m_source, &destination, rotation, NULL, SDL_FLIP_NONE);
}

Sprite::operator SDL_Texture *()
{
    return m_texture;
}
