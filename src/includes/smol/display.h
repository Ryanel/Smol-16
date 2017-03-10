#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include <color.h>
#include <config.h>

class Display {
private:
    static Display * m_instance;
    Display();
public:
    static const int width = SCREEN_WIDTH; // 256
    static const int height = SCREEN_HEIGHT; // 224
    static Display *instance();

    color_t * pixels;
    // Methods
    void Clear();
    void PaletteReset();


    color_t * Render();
    static void Lua_Clear();
    static void Lua_PaletteReset();
    static int Lua_RGBToBGR15(int r, int g, int b) ;
};
