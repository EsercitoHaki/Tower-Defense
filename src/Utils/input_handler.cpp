#include "input_handler.h"
#include <iostream>

InputHandler::InputHandler() {
    m_mousePosition.x = 0.0f;
    m_mousePosition.y = 0.0f;
}

InputHandler::~InputHandler() {

}

void InputHandler::update() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_EVENT_QUIT) {
            m_keyStates[SDLK_ESCAPE] = true;
        } else if (e.type == SDL_EVENT_KEY_DOWN) {
            m_keyStates[e.key.key] = true;
        } else if (e.type == SDL_EVENT_KEY_UP) {
            m_keyStates[e.key.key] = false;
        } else if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            m_mouseButtonStates[e.button.button] = true;
        } else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            m_mouseButtonStates[e.button.button] = false;
        } else if (e.type == SDL_EVENT_MOUSE_MOTION) {
            m_mousePosition.x = (float)e.motion.x;
            m_mousePosition.y = (float)e.motion.y;
        }
    }
}

bool InputHandler::isKeyDown(SDL_Keycode key) const {
    auto it = m_keyStates.find(key);
    if (it != m_keyStates.end()) {
        return it->second;
    }
    return false;
}

bool InputHandler::isMouseButtonDown(Uint8 button) const {
    auto it = m_mouseButtonStates.find(button);
    if (it != m_mouseButtonStates.end()) {
        return it->second;
    }
    return false;
}

SDL_FPoint InputHandler::getMousePosition() const {
    return m_mousePosition;
}