#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include <color.h>
#include <config.h>
const int PALETTE_BASE = 0x1F000;
const int VRAM_BASE = 0x10000;

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
    color_t * Render();
    static void LuaClear();
};
