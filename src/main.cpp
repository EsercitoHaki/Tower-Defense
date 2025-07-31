#include "Game/game.h"
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {
    Game game;

    if (game.init("SDL3 Tower Defense", SCREEN_WIDTH, SCREEN_HEIGHT)) {
        while (game.isRunning()) {
            game.handleEvents();
            game.update();
            game.render();
        }
    } else {
        std::cerr << "Failed to initialize game!" << std::endl;
        return 1;
    }

    std::cout << "Game exited cleanly." << std::endl;
    return 0;
}