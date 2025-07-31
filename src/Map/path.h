#pragma once
#include <vector>
#include <SDL3/SDL.h>

class Path {
public:
    std::vector<SDL_Point> waypoints;
    Path(const std::vector<SDL_Point>& points) : waypoints(points) {}
};