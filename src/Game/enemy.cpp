#include "enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(Path* p, float startX, float startY, float spd)
    : path(p), x(startX), y(startY), speed(spd), currentWaypoint(0) {
    std::cout << "Enemy created at (" << x << ", " << y << ") with speed " << speed << std::endl;
    if (path) {
        std::cout << "Path has " << path->waypoints.size() << " waypoints" << std::endl;
        for (size_t i = 0; i < path->waypoints.size(); i++) {
            std::cout << "  Waypoint " << i << ": (" << path->waypoints[i].x << ", " << path->waypoints[i].y << ")" << std::endl;
        }
        
        if (path->waypoints.size() > 0) {
            SDL_Point firstWaypoint = path->waypoints[0];
            float dx = firstWaypoint.x - x;
            float dy = firstWaypoint.y - y;
            float distanceToFirst = std::sqrt(dx * dx + dy * dy);
            
            if (distanceToFirst < 10.0f) {
                std::cout << "Enemy is close to first waypoint, skipping to next" << std::endl;
                currentWaypoint = 1;
            }
        }
    }
}

void Enemy::update(float deltaTime) {
    if (!path) {
        std::cout << "No path!" << std::endl;
        return;
    }
    
    if (currentWaypoint >= path->waypoints.size()) {
        return;
    }
    
    SDL_Point target = path->waypoints[currentWaypoint];
    float dx = target.x - x;
    float dy = target.y - y;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    if (distance < 5.0f) {
        std::cout << "Reached waypoint " << currentWaypoint << std::endl;
        ++currentWaypoint;
    } else {
        float moveX = speed * (dx / distance) * deltaTime;
        float moveY = speed * (dy / distance) * deltaTime;
        
        x += moveX;
        y += moveY;
    }
}
void Enemy::render(SDL_Renderer* renderer) {
    SDL_FRect rect = { x - 8, y - 8, 16, 16 };
    SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
    SDL_RenderFillRect(renderer, &rect);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderRect(renderer, &rect);
}