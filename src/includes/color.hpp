#pragma once
#include <stdint.h>
typedef uint32_t   color_t;
namespace Color {
inline color_t RGBAFromRGB(uint8_t r, uint8_t g, uint8_t b)
{
    return 0xFF | (b << 8) | (g << 16) | (r << 24);
}


inline color_t RGBAFromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return a | (b << 8) | (g << 16) | (r << 24);
}


inline uint16_t BGR15FromRGB(uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t cr = r / 8;
    uint8_t cg = g / 8;
    uint8_t cb = b / 8;

    return (uint16_t)((cr) | (cg << 5) | (cb << 10));
}


inline color_t RGBAFromBGR15(uint16_t c)
{
    uint16_t r = ((c) % 32) * 8;
    uint16_t g = ((c / 32) % 32) * 8;
    uint16_t b = ((c / 1024) % 32) * 8;

    // We lost a bit of precision. Extend the range of RGB so white is 0xFFFFFF
    r += r / 32;
    g += g / 32;
    b += b / 32;
    return RGBAFromRGB(r, g, b);
}
}
