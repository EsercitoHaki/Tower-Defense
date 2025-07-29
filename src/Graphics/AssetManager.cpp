#include "AssetManager.h"

static AssetManager* s_instance = nullptr;

AssetManager& AssetManager::getInstance(SDL_Renderer* renderer) {
    if (s_instance == nullptr) {
        if (renderer == nullptr) {
            std::cerr << "Error: AssetManager needs a renderer for initial setup!" << std::endl;
            return *s_instance;
        }
        s_instance = new AssetManager(renderer);
    }
    return *s_instance;
}

AssetManager::AssetManager() : m_renderer(nullptr) {

}

AssetManager::AssetManager(SDL_Renderer* renderer) : m_renderer(renderer) {

}

AssetManager::~AssetManager() {
    clean();
    s_instance = nullptr;
}

SDL_Texture* AssetManager::getTexture(const std::string& path) {
    if (m_textures.count(path)) {
        return m_textures[path];
    }

    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! IMG_Error: " << SDL_GetError() << std::endl;
        std::cerr << "Current working directory: " << SDL_GetBasePath() << std::endl;
    } else {
        std::cout << "Successfully loaded image: " << path << std::endl;  // Debug info
        newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cerr << "Unable to create texture from " << path << "! SDL_ERROR: " << SDL_GetError() << std::endl;
        } else {
            std::cout << "Successfully created texture from: " << path << std::endl;  // Debug info
        }
        SDL_DestroySurface(loadedSurface);
    }

    m_textures[path] = newTexture;
    return newTexture;
}

void AssetManager::clean() {
    for (auto const& [path, texture] : m_textures) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    m_textures.clear();
}