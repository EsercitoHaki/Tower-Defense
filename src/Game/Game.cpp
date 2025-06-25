#include "Game.h"
#include <iostream>

Game::Game() : m_isRunning(false), m_window(nullptr), m_renderer(nullptr),
               m_lastTick(0), m_deltaTime(0.0), m_player(nullptr) {
}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow(
        title,
        width,
        height,
        SDL_WINDOW_RESIZABLE
    );
    if (m_window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (m_renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    AssetManager::getInstance(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    m_player = new Player(m_renderer, "",
                          (float)width / 2 - (width / 8),
                          (float)height / 2 - (height / 8),
                          (float)width / 4,
                          (float)height / 4,
                          200.0f);
    m_player->setInputHandler(&m_inputHandler);
    m_entities.push_back(m_player);

    m_entities.push_back(new Entity(m_renderer, "assets/Tower.png", 100, 100, 128, 256));
    m_entities.push_back(new Entity(m_renderer, "assets/Enemy.png", 500, 300, 192, 192));

    m_isRunning = true;
    m_lastTick = SDL_GetPerformanceCounter();
    return true;
}

void Game::handleEvents() {
    m_inputHandler.update();

    if (m_inputHandler.isKeyDown(SDLK_ESCAPE)) {
        m_isRunning = false;
    }
}

void Game::update() {
    Uint64 currentTick = SDL_GetPerformanceCounter();
    m_deltaTime = (double)((currentTick - m_lastTick) * 1000 / (double)SDL_GetPerformanceFrequency()) / 1000.0;
    m_lastTick = currentTick;

    for (Entity* entity : m_entities) {
        entity->update(m_deltaTime);
    }
}

void Game::render() {
    SDL_RenderClear(m_renderer);

    for (Entity* entity : m_entities) {
        entity->render();
    }

    SDL_RenderPresent(m_renderer);
}

void Game::clean() {
    for (Entity* entity : m_entities) {
        delete entity;
    }
    m_entities.clear();

    AssetManager::getInstance().clean();

    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_Quit();
    m_isRunning = false;
}