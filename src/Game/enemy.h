#pragma once
#include "../Map/path.h"
#include <SDL3/SDL.h>

class Enemy {
public:
    float x, y, speed; // Vị trí của kẻ địch
    int currentWaypoint; // Chỉ số waypoint hiện tại
    Path* path; // Đường đi của kẻ địch

    Enemy(Path* p, float startX, float startY, float spd);
    void update(float deltaTime);
    void render(SDL_Renderer* renderer);
};