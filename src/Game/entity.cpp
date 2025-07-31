#include "entity.h"
#include <iostream>

Entity::Entity(SDL_Renderer* renderer, const std::string& texturePath, float x, float y, float w, float h)
    : m_renderer(renderer) {
    m_rect = {x, y, w, h};
    m_texture = AssetManager::getInstance(renderer).getTexture(texturePath);
    if (m_texture == nullptr) {
        std::cerr << "Failed to create Entity: texture is null for path: " << texturePath << std::endl;
    }
}

Entity::~Entity() {

}

void Entity::update(double deltaTime) {
    
}

void Entity::render() {
    if (m_texture) {
        SDL_RenderTexture(m_renderer, m_texture, NULL, &m_rect);
    }
}