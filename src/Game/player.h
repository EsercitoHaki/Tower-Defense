#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "../Utils/input_handler.h"

class Player : public Entity {
public:
    Player(SDL_Renderer* renderer, const std::string& texturePath, float x, float y, float w, float h, float speed);
    ~Player();

    void update(double deltaTime) override;
    void render() override;

    void setInputHandler(InputHandler* inputHandler) { m_inputHandler = inputHandler; }

private:
    float m_speed;
    InputHandler* m_inputHandler;
};

#endif