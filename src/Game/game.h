#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <vector>
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "../Utils/input_handler.h"
#include "../Graphics/asset_manager.h"
#include "../Map/map.h"

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning() const { return m_isRunning; }

private:
    bool m_isRunning;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    InputHandler m_inputHandler;
    std::vector<Entity*> m_entities; 
    Uint64 m_lastTick;
    double m_deltaTime;

    Map* m_map;
    Player* m_player;
    std::vector<Enemy*> m_enemies;
    std::vector<Path*> m_paths; // Optional: if you want to manage paths separately
};

#endif