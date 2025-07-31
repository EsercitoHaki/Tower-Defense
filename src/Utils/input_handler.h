#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL3/SDL.h>
#include <map>

class InputHandler {
public:
    InputHandler();
    ~InputHandler();

    void update();
    bool isKeyDown(SDL_Keycode key) const;
    bool isMouseButtonDown(Uint8 button) const;
    SDL_FPoint getMousePosition() const;

private:
    std::map<SDL_Keycode, bool> m_keyStates;
    std::map<Uint8, bool> m_mouseButtonStates;
    SDL_FPoint m_mousePosition;
};

#endif