#ifndef ENTITY_H
#define ENTITY_H

#include <SDL3/SDL.h>
#include <string>
#include "../Graphics/AssetManager.h"

class Entity {
public:
    Entity(SDL_Renderer* renderer, const std::string& texturePath, float x, float y, float w, float h);
    virtual ~Entity();

    virtual void update(double deltaTime);
    virtual void render();

    SDL_FRect getRect() const { return m_rect; }
    void setPosition(float x, float y) { m_rect.x = x; m_rect.y = y; }

protected:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    SDL_FRect m_rect;
};

#endif