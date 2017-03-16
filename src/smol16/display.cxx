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
    0xFF,0xCC,0xAA,
    0x00,0x00,0x00
};


Display * Display::m_instance;
Memory * Display::mem_instance;
int Display::scale = 1;
Display * Display::instance()
{
   if(!m_instance) {m_instance = new Display();}
   return m_instance;
}

Display::Display() {
    pixels = new color_t[width * height]; // Framebuffer of RGBA8888 pixel data.
    sys->Register("screenWidth", width);
    sys->Register("screenHeight", height);
    sys->Register("cls", Display::Lua_Clear);
    sys->Register("palette_reset", Display::Lua_PaletteReset);
    sys->Register("_to_bgr", Display::Lua_RGBToBGR15);
    sys->Register("gfx_hw_rect", Display::Lua_DrawRect);
    sys->Register("gfx_hw_pix", Display::Lua_PutPixel);
    mem_instance = Memory::instance();
}

void Display::Clear(uint8_t color) {
    memset(pixels, 0, width * height * sizeof(color_t));
    memset(mem_instance->ram + MEM_VRAM, color, width * height);
}

void Display::PaletteReset() {
    Memory * m = mem_instance;
    int arr_index = 0; // + 3

    for(int pal_index = 0; pal_index < 256; pal_index++) {
        // Convert RGB into BGR15
        uint8_t cr = defaultPalette[arr_index++];
        uint8_t cg = defaultPalette[arr_index++];
        uint8_t cb = defaultPalette[arr_index++];

        m->Poke16(MEM_VRAM_PCT + (pal_index * 2), Color::BGR15FromRGB(cr,cg,cb));

    }
}

color_t * Display::Render() {
    Memory * mem = mem_instance;
    //TODO: Cache Palette
    color_t palette[256];

    for(int i = 0; i < 256; i++) {
        // Convert BRG15 to RGB
        uint16_t c = mem->Peek16(MEM_VRAM_PCT + (i * 2));
        palette[i] = Color::RGBAFromBGR15(c);
    }

    for (size_t i = 0; i < width * height; i++) {
        pixels[i] = palette[mem->Peek8(i + MEM_VRAM)];
    }
    return pixels;
}
int Display::Lua_RGBToBGR15(int r, int g, int b) {
    return Color::BGR15FromRGB(r,g,b);
}
void Display::Lua_Clear(int color) {
    instance()->Clear(color & 0xFF);
}
void Display::Lua_PaletteReset() {
    instance()->PaletteReset();
}

void Display::Lua_DrawRect(int x0, int y0, int x1, int y1, int color) {
    for(int y = y0; y < y1; y++) {
        for(int x = x0; x < x1; x++) {
            m_instance->PutPixel(x, y, (uint8_t)color);
        }
    }
}

void Display::Lua_PutPixel(int x, int y, int color) {
    m_instance->PutPixel(x, y, (uint8_t)color);
}
