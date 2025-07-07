#pragma once
#include <SDL3/SDL.h>
#include "Player.h"

class Game {
public:
    Game();
    ~Game();

    bool Init(const char* title, int width, int height);
    void Run();
    void Clean();

private:
    void HandleEvents();
    void Update();
    void Render();

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool isRunning = false;

    Uint64 lastTick = 0;
    double deltaTime = 0.0;

    Player* player = nullptr;
};