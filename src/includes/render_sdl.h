#pragma once
#include <SDL.h>
#include <spdlog/spdlog.h>
class SDLRenderer {
private:
    static std::shared_ptr<spdlog::logger> _logger;
public:
    static SDL_Window *win;
    static SDL_Renderer *ren;
    static SDL_Texture *display;

    static void Init();
    static void EventLoop();
    static void Flip();
    static void Cleanup();
    static void LoadFont();
    static void HandleInput(SDL_Event e);
    static void HandleTextInput(SDL_Event e);
};
