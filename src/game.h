#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <vector>

class Game {
public:
    //Constructor
    Game();

    //Destructor
    ~Game();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clear();
    bool isRunning() const { return m_isRunning; }

private:
    bool m_isRunning;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    Uint64 m_lastTick;
    double m_deltaTime;
};

#endif