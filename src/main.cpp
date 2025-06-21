#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <map>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_ERROR: " << SDL_GetError() << std::endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cerr << "Unable to create texture from " << path << "! SDL_ERROR: " << SDL_GetError() << std::endl;
        }
        SDL_DestroySurface(loadedSurface);
    }

    return newTexture;
} 

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL3 Red Square Game",
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    Uint64 lastTick = SDL_GetPerformanceCounter();
    double deltaTime = 0.0;

    float squareX = SCREEN_WIDTH / 2 - (SCREEN_WIDTH / 8);
    float squareY = SCREEN_HEIGHT / 2 - (SCREEN_HEIGHT / 8);
    float squareWidth = SCREEN_WIDTH / 4;
    float squareHeight = SCREEN_HEIGHT / 4;
    float squareSpeed = 200.0f;

    std::map<SDL_Keycode, bool> keyStates;

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        Uint64 currentTick = SDL_GetPerformanceCounter();
        deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency()) / 1000.0;
        lastTick = currentTick;

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            } else if (e.type == SDL_EVENT_KEY_DOWN) {
                keyStates[e.key.key] = true;
            } else if (e.type == SDL_EVENT_KEY_UP) {
                keyStates[e.key.key] = false;
            }
        }
        
        if (keyStates[SDLK_ESCAPE]) {
            quit = true;
        }
        if (keyStates[SDLK_UP] || keyStates[SDLK_W]) {
            squareY -= squareSpeed * deltaTime;
        }
        if (keyStates[SDLK_DOWN] || keyStates[SDLK_S]) {
            squareY += squareSpeed * deltaTime;
        }
        if (keyStates[SDLK_LEFT] || keyStates[SDLK_A]) {
            squareX -= squareSpeed * deltaTime;
        }
        if (keyStates[SDLK_RIGHT] || keyStates[SDLK_D]) {
            squareX += squareSpeed * deltaTime;
        }

        if (squareX < 0) squareX = 0;
        if (squareY < 0) squareY = 0;
        if (squareX + squareWidth > SCREEN_WIDTH) squareX = SCREEN_WIDTH - squareWidth;
        if (squareY + squareHeight > SCREEN_HEIGHT) squareY = SCREEN_HEIGHT - squareHeight;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_FRect fillRect = { squareX, squareY, squareWidth, squareHeight };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &fillRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Game exited cleanly." << std::endl;
    return 0;
}