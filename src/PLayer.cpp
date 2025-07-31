#include "Player.h"

Player::Player(float x, float y, float w, float h, float speed) : speed(speed){
    rect = { x, y, w, h };
}

void Player::HandleInput(const Uint8* keystate) {

}

void Player::Update(double deltaTime, int screenW, int screenH) {
    int numKeys;
    const bool* state = SDL_GetKeyboardState(&numKeys);

    if (state[SDL_SCANCODE_W]) rect.y -= speed * deltaTime;
    if (state[SDL_SCANCODE_S]) rect.y += speed * deltaTime;
    if (state[SDL_SCANCODE_A]) rect.x -= speed * deltaTime;
    if (state[SDL_SCANCODE_D]) rect.x += speed * deltaTime;

    if (rect.x < 0) rect.x = 0;
    if (rect.y < 0) rect.y = 0;
    if (rect.x + rect.w > screenW) rect.x = screenW - rect.w;
    if (rect.y + rect.h > screenH) rect.y = screenH - rect.h;
}

void Player::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}