#pragma once
#include <stdint.h>
typedef uint32_t color_t;
namespace Color {
    inline color_t RGBAFromRGB(uint8_t r, uint8_t g, uint8_t b) {
        return 0xFF | (b << 8) | (g << 16) | (r << 24);
    }
    inline color_t RGBAFromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        return a | (b << 8) | (g << 16) | (r << 24);
    }
}
