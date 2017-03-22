#pragma once
#include <config.h>
#ifdef BACKEND_SDL
#include "SDL.h"
#include <color.hpp>
class CBackend_SDL {
private:
    static SDL_Window *win;
    static SDL_Renderer *ren;
    static SDL_Texture *display;
    static CBackend_SDL *_instance;
    CBackend_SDL();
    ~CBackend_SDL();
    void HandleInput(SDL_Event e);
    void HandleTextInput(SDL_Event e);

public:
    static CBackend_SDL *instance();
    void Init();
    void EventLoop();
    void Render(color_t *ppu);
    void Cleanup();
    void LoadFont();
};

#endif
