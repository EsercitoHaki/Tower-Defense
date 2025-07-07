#include "TextureManager.h"
#include <iostream>

SDL_Texture* TextureManager::LoadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    if (!tempSurface) {
        std::cerr << "Failed to load image: " << path << SDL_GetError() << std::endl;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_DestroySurface(tempSurface);

    if (!texture) {
        std::cerr << "Failed to create texture: " << path << SDL_GetError() << std::endl;
    }

    return texture;
}