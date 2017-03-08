#include <cstring>
#include <color.h>
#include <smol/memory.h>
#include <smol/display.h>
#include <smol/smol16.h>
#include <font.h>
const uint8_t defaultPalette[256 * 3] = {
    //R    G     B
    0X00,0X00,0X00,
    0x1D,0x2B,0x53,
    0x7E,0x25,0x53,
    0x00,0x87,0x51,
    0xAB,0x52,0x36,
    0x5F,0x57,0x4F,
    0xC2,0xC3,0xC7,
    0xFF,0xF1,0xE8,
    0xFF,0x00,0x4D,
    0xFF,0xA3,0x00,
    0xFF,0xEC,0x27,
    0x00,0xE4,0x36,
    0x29,0xAD,0xFF,
    0x83,0x76,0x9C,
    0xFF,0x77,0xA8,
    0xFF,0xCC,0xAA
};

Display * Display::m_instance;

Display * Display::instance()
{
   if(!m_instance) {m_instance = new Display();}
   return m_instance;
}

Display::Display() {
    pixels = new color_t[width * height]; // Framebuffer of RGBA8888 pixel data.
    sys->Register("screenWidth", width);
    sys->Register("screenHeight", height);
    sys->Register("cls", Display::LuaClear);
}

void Display::Clear() {
    memset(pixels, 0, width * height * sizeof(color_t));
    memset(Memory::instance()->ram + VRAM_BASE, 0, width * height);
}

void Display::LuaClear() {
    instance()->Clear();
}
color_t * Display::Render() {
    Memory * mem = Memory::instance();

    //TODO: Cache Palette
    color_t palette[256];
    for(int i = 0; i < 256; i++) {
        int pi = mem->Peek8(PALETTE_BASE + i);
        palette[i] = Color::RGBAFromRGB(defaultPalette[(pi * 3) + 0],defaultPalette[(pi * 3) + 1],defaultPalette[(pi * 3) + 2]);
    }
    for (size_t i = 0; i < width * height; i++) {
        pixels[i] = palette[mem->Peek8(i + VRAM_BASE)];
    }
    return pixels;
}
