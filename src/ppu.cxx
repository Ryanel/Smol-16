#include <ppu.hpp>
#include <smol16.hpp>
#include <color.hpp>
#include <spdlog/spdlog.h>

#ifdef BACKEND_SDL
#include <sdl_backend.hpp>
#endif

const uint8_t defaultPalette[256 * 3] =
{
    //R    G     B
    0X00, 0X00, 0X00,
    0x1D, 0x2B, 0x53,
    0x7E, 0x25, 0x53,
    0x00, 0x87, 0x51,
    0xAB, 0x52, 0x36,
    0x5F, 0x57, 0x4F,
    0xC2, 0xC3, 0xC7,
    0xFF, 0xF1, 0xE8,
    0xFF, 0x00, 0x4D,
    0xFF, 0xA3, 0x00,
    0xFF, 0xEC, 0x27,
    0x00, 0xE4, 0x36,
    0x29, 0xAD, 0xFF,
    0x83, 0x76, 0x9C,
    0xFF, 0x77, 0xA8,
    0xFF, 0xCC, 0xAA,
    0x00, 0x00, 0x00
};

CPPU *CPPU::_instance = NULL;
CPPU *CPPU::instance()
{
    if (!_instance)
    {
        _instance = new CPPU();
    }
    return _instance;
}


CPPU::CPPU()
{
    if (_log == NULL)
    {
        _log = spdlog::stdout_color_mt("ppu");
    }
    memory       = new uint8_t[0x20000];
    pixel_buffer = new color_t[256 * 224];     // 256 x 224 x 4 bytes, RGBA.

    _log->debug("PPU online");
    Init();
}


void CPPU::Init()
{
#ifdef BACKEND_SDL
    sdl = CBackend_SDL::instance();
#endif
    getGlobalNamespace(CSystem::instance()->L)
       .beginNamespace("ppu")
       .addFunction("pal_write", &CPPU::Lua_WriteColorPalette)
       .addFunction("pal_read", &CPPU::Lua_ReadColorPalette)
       .addFunction("pal_reset", &CPPU::Lua_ResetColorPalette)
       .addFunction("cls", &CPPU::Lua_ClearScreen)
       .addFunction("poke8", &CPPU::Lua_Poke8)
       .addFunction("poke16", &CPPU::Lua_Poke16)
       .addFunction("peek8", &CPPU::Lua_Peek8)
       .addFunction("peek16", &CPPU::Lua_Peek16)
       .addFunction("pixel", &CPPU::Lua_PutPixel)
       .addFunction("rect", &CPPU::Lua_DrawRect)
       .endNamespace();

    memset(memory, 0, 0x20000);
    memset(pixel_buffer, 0, 256 * 224 * sizeof(color_t));
}


void CPPU::DoRender()
{
    bool shouldRender = Peek8(0xFFF0) == 0;

    if (shouldRender && !g_config.noGraphics)
    {
        // Generate the pixel data, then send it off to the backend
        color_t palette[256];

        for (int i = 0; i < 256; i++)
        {
            // Convert BRG15 to RGB
            uint16_t c = Peek16(0xE000 + (i * 2));
            palette[i] = Color::RGBAFromBGR15(c);
        }

        for (size_t i = 0; i < 256 * 224; i++)
        {
            pixel_buffer[i] = palette[Peek8(i)];
        }

        // Now, inform the backend
#ifdef BACKEND_SDL
        sdl->Render(this->pixel_buffer);
#endif
    }
    Poke8(0xFFF0, 0); // Reset, regardless if we rendered or not
}


void CPPU::Poke8(int address, uint8_t data)
{
    memory[address] = data;
}


void CPPU::Poke16(int address, uint16_t data)
{
    Poke8(address + 1, (unsigned char)(data & 0x00ff));
    Poke8(address + 0, (unsigned char)((data & 0xff00) >> 8));
}


uint8_t CPPU::Peek8(address_t address)
{
    return memory[address];
}


uint16_t CPPU::Peek16(address_t address)
{
    uint8_t a = Peek8(address);
    uint8_t b = Peek8(address + 1);

    return (uint16_t)((a << 8) | (b & 0xff));
}


void CPPU::Lua_WriteColorPalette(address_t index, address_t color)
{
    color = color & 0xFFFF;
    index = index & 0xFF;
    _instance->Poke16(0xE000 + index, color);
}


int CPPU::Lua_ReadColorPalette(address_t index)
{
    return _instance->Peek16(0xE000 + index);
}


void CPPU::Lua_ResetColorPalette()
{
    int arr_index = 0; // + 3

    for (int pal_index = 0; pal_index < 256; pal_index++)
    {
        // Convert RGB into BGR15
        uint8_t cr = defaultPalette[arr_index++];
        uint8_t cg = defaultPalette[arr_index++];
        uint8_t cb = defaultPalette[arr_index++];
        _instance->Poke16(0xE000 + pal_index * 2, Color::BGR15FromRGB(cr, cg, cb));
    }
}


/*! Writes a 8bit value to address*/
void CPPU::Lua_Poke8(int address, int data)
{
    return _instance->Poke8(address, data);
}


/*! Writes a 16bit value to address*/
void CPPU::Lua_Poke16(int address, int data)
{
    return _instance->Poke16(address, data);
}


/*! Reads a 8bit value from address*/
int CPPU::Lua_Peek8(int address)
{
    return _instance->Peek8(address);
}


/*! Reads a 16bit value from address*/
int CPPU::Lua_Peek16(int address)
{
    return _instance->Peek16(address);
}


void CPPU::Lua_ClearScreen(int color)
{
    memset(_instance->memory, color & 0xFF, 256 * 224);
}


void CPPU::Lua_PutPixel(int x, int y, uint8_t color)
{
    if (MEMORY_BOUNDS_CHECKS)
    {
        if ((x < 0) || (x >= SCREEN_WIDTH))
        {
            return;
        }
        if ((y < 0) || (y >= SCREEN_HEIGHT))
        {
            return;
        }
    }
    _instance->Poke8((y * 256) + x, color);
}


void CPPU::Lua_DrawRect(int x0, int y0, int x1, int y1, int color)
{
    for (int y = y0; y < y1; y++)
    {
        for (int x = x0; x < x1; x++)
        {
            Lua_PutPixel(x, y, (uint8_t)color);
        }
    }
}
