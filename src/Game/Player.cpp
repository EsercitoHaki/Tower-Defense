#include "Player.h"
#include <SDL3/SDL.h>

Player::Player(SDL_Renderer* renderer, const std::string& texturePath, float x, float y, float w, float h, float speed)
    : Entity(renderer, texturePath, x, y, w, h), m_speed(speed), m_inputHandler(nullptr) {

}

Player::~Player() {

}

void Player::update(double deltaTime) {
    if (m_inputHandler == nullptr) {

        return;
    }

    if (m_inputHandler->isKeyDown(SDLK_UP) || m_inputHandler->isKeyDown(SDLK_W)) {
        m_rect.y -= m_speed * deltaTime;
    }
    if (m_inputHandler->isKeyDown(SDLK_DOWN) || m_inputHandler->isKeyDown(SDLK_S)) {
        m_rect.y += m_speed * deltaTime;
    }
    if (m_inputHandler->isKeyDown(SDLK_LEFT) || m_inputHandler->isKeyDown(SDLK_A)) {
        m_rect.x -= m_speed * deltaTime;
    }
    if (m_inputHandler->isKeyDown(SDLK_RIGHT) || m_inputHandler->isKeyDown(SDLK_D)) {
        m_rect.x += m_speed * deltaTime;
    }

    int window_w, window_h;
    SDL_GetWindowSize(SDL_GetRenderWindow(m_renderer), &window_w, &window_h);

    if (m_rect.x < 0) m_rect.x = 0;
    if (m_rect.y < 0) m_rect.y = 0;
    if (m_rect.x + m_rect.w > window_w) m_rect.x = (float)window_w - m_rect.w;
    if (m_rect.y + m_rect.h > window_h) m_rect.y = (float)window_h - m_rect.h;
}

void Player::render() {
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(m_renderer, &m_rect);
}