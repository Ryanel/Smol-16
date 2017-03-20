#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include <color.h>
#include <config.h>
#include <smol/memory.h>

class Display {
private:
    static Display * m_instance;
    static Memory * mem_instance;
    Display();
public:
    static const int width = SCREEN_WIDTH; // 256
    static const int height = SCREEN_HEIGHT; // 224
    static int scale;
    static Display *instance();

    color_t * pixels;
    // Methods
    void Clear(uint8_t);
    void PaletteReset();
    inline void PutPixel(int x, int y, uint8_t color) {
        if(MEMORY_BOUNDS_CHECKS) {
            if(x < 0 || x >= SCREEN_WIDTH)  { return; }
            if(y < 0 || y >= SCREEN_HEIGHT) { return; }
        }
        mem_instance->ram[MEM_VRAM + (y * 256) + x] = color;
    }

    color_t * Render();
    static void Lua_Clear(int);
    static void Lua_PaletteReset();
    static int Lua_RGBToBGR15(int r, int g, int b) ;
    static void Lua_DrawRect(int x, int y, int w, int h, int color);
    static void Lua_PutPixel(int x, int y, int c);
};
