#pragma once
#include <config.h>
#include <memory.hpp>
#include <color.hpp>
#include <spdlog/spdlog.h>

#ifdef BACKEND_SDL
class CBackend_SDL;
#include <sdl_backend.hpp>
#endif

class CPPU {
private:
    static CPPU * _instance;
    CPPU();
    uint8_t * memory;
    std::shared_ptr<spdlog::logger> _log;
    #ifdef BACKEND_SDL
    CBackend_SDL * sdl;
    #endif
public:
    color_t * pixel_buffer;
    static CPPU * instance();
    void Init();

    void DoRender();

    void Poke8(address_t address, uint8_t data);
    void Poke16(address_t address, uint16_t data);
    uint8_t  Peek8  (address_t address);
    uint16_t  Peek16 (address_t address);

    static void Lua_WriteColorPalette(address_t index,address_t color);
    static int  Lua_ReadColorPalette(address_t index);
    static void Lua_ResetColorPalette();
    static void Lua_ClearScreen(int color);

    static void Lua_Poke8  (address_t address, int data);
    static void Lua_Poke16 (address_t address, int data);
    static int  Lua_Peek8  (address_t address);
    static int  Lua_Peek16 (address_t address);

    static void Lua_PutPixel(int x, int y, uint8_t color);
    static void Lua_DrawRect(int x0, int y0, int x1, int y1, int color);
};
