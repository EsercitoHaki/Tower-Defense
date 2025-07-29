#include "Game.h"
#include "TextureManager.h"
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Game::Game() : window(nullptr), renderer(nullptr), player(nullptr), isRunning(false), deltaTime(0.0), lastTick(0) {}

Game::~Game() {
    delete player;
}

bool Game::Init(const char* title, int width, int height) {
    // Khởi tạo SDL với nhiều hệ thống con
    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
    if (result != 0) {
        std::cerr << "SDL_Init failed with code " << result << ": " << SDL_GetError() << std::endl;
        
        // Thử khởi tạo lại chỉ với VIDEO
        result = SDL_Init(SDL_INIT_VIDEO);
        if (result != 0) {
            std::cerr << "SDL_Init VIDEO only also failed: " << SDL_GetError() << std::endl;
            return false;
        }
    }

    // Đặt hint cho driver video (tùy chọn)
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    
    // Tạo cửa sổ với các flag phù hợp (SDL3)
    window = SDL_CreateWindow(
        title, 
        width, height, 
        SDL_WINDOW_RESIZABLE
    );
    
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // Tạo renderer với hardware acceleration
    renderer = SDL_CreateRenderer(window, nullptr);
    
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        std::cerr << "Trying software renderer..." << std::endl;
        
        // Thử tạo renderer software nếu hardware không được
        renderer = SDL_CreateRenderer(window, nullptr);
        
        if (!renderer) {
            std::cerr << "Software renderer also failed: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }
    }

    // Thiết lập blend mode cho renderer
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    player = new Player(width / 2.0f - 100, height / 2.0f - 100, 200, 200, 200.0f);

    isRunning = true;
    lastTick = SDL_GetPerformanceCounter();

    std::cout << "SDL initialized successfully!" << std::endl;
    std::cout << "Video driver: " << SDL_GetCurrentVideoDriver() << std::endl;
    
    return true;
}

void Game::HandleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT)
            isRunning = false;
        if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE)
            isRunning = false;
    }
}

void Game::Update() {
    Uint64 currentTick = SDL_GetPerformanceCounter();
    deltaTime = (double)(currentTick - lastTick) / SDL_GetPerformanceFrequency();
    lastTick = currentTick;

    player->Update(deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    player->Render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Game::Run() {
    while (isRunning) {
        HandleEvents();
        Update();
        Render();
    }
}