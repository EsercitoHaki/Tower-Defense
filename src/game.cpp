#include "game.h"
#include <iostream>

Game::Game() : 
    m_isRunning(false), 
    m_window(nullptr), 
    m_renderer(nullptr), 
    m_lastTick(0),
    m_deltaTime(0.0) {

}

Game::~Game() {
    clear();
}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        SDL_Log("SDL could not initilize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    m_window = SDL_CreateWindow("Test Game", width, height, 0);

    if (m_window == nullptr) {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    m_renderer = SDL_CreateRenderer(m_window, nullptr);

    if (m_renderer == nullptr) {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    m_isRunning = true;
    m_lastTick = SDL_GetPerformanceCounter();
    return true;
}

void Game::handleEvents() {
    
}

void Game::update() {
    Uint64 currentTick = SDL_GetPerformanceCounter();
    m_deltaTime = (double)((currentTick - m_lastTick) * 1000 / (double)SDL_GetPerformanceCounter()) / 1000.0f;
    m_lastTick = currentTick;
}

void Game::render() {
    SDL_RenderClear(m_renderer);
}

void Game::clear() {
    
}