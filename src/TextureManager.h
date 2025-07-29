#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <map>

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const std::string& path, SDL_Renderer* renderer);
};