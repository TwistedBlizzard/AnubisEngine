#ifndef SPRITE_H
#define SPRITE_H

#include "Core.hpp"

#include "Vector2f.hpp"

class Sprite
{
public:
    Sprite();
    ~Sprite();

    void SetTexture(SDL_Texture* texture);
    void SetSize(Vector2f size);
    void SetSource(SDL_FRect source);

    void Draw(SDL_Renderer* renderer, Vector2f position, double rotation = 0.0);

    // Allows us to cast to SDL_Texture
    operator SDL_Texture*();

protected:
    SDL_Texture* m_texture;
    Vector2f m_size;
    SDL_FRect m_source;
};

#endif // SPRITE_H