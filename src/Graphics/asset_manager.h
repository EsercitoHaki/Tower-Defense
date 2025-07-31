#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <map>
#include <string>
#include <iostream>

class AssetManager {
public:
    static AssetManager& getInstance(SDL_Renderer* renderer = nullptr);
    ~AssetManager();

    SDL_Texture* getTexture(const std::string& path);
    void clean();

private:
    AssetManager();
    AssetManager(SDL_Renderer* renderer);
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    SDL_Renderer* m_renderer;
    std::map<std::string, SDL_Texture*> m_textures;
};

#endif