#pragma once
#include <SDL3/SDL.h>


class Player {
public:
    Player(float x, float y, float w, float h, float speed);

    void HandleInput(const Uint8* keystate);
    void Update(double deltaTime, int screenW, int screenH);
    void Render(SDL_Renderer* renderer);

private:
    SDL_FRect rect;
    float speed;
};