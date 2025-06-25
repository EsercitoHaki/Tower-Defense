#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <vector>
#include "../Utils/InputHandler.h"
#include "Entity.h"
#include "Player.h"
#include "../Graphics/AssetManager.h"

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height); // Removed xpos, ypos, fullscreen
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
    std::vector<Entity*> m_entities; // Store all entities (including player, towers, enemies)

    // Delta time
    Uint64 m_lastTick;
    double m_deltaTime;

    // Direct pointer to the player for easy access
    Player* m_player;
};

#endif // GAME_H