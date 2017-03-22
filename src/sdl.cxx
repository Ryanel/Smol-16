#include <config.h>
#include <sys_config.hpp>
#ifdef BACKEND_SDL
#include <sdl_backend.hpp>
#include "SDL.h"
#include <SDL_image.h>
#include <smol16.hpp>
#include <ppu.hpp>
#include <input.hpp>
class CPPU;

CBackend_SDL *CBackend_SDL::_instance = NULL;
SDL_Window   *CBackend_SDL::win       = NULL;
SDL_Renderer *CBackend_SDL::ren       = NULL;
SDL_Texture  *CBackend_SDL::display   = NULL;

uint8_t GetFromBuffer(uint32_t *buf, int x, int y, int width)
{
    return buf[y * width + x];
}


CBackend_SDL *CBackend_SDL::instance()
{
    if (!_instance)
    {
        _instance = new CBackend_SDL();
    }
    return _instance;
}


CBackend_SDL::CBackend_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        exit(1);
    }
    Init();
}


void CBackend_SDL::Init()
{
    if (g_config.noGraphics)
    {
        return;
    }
    win = SDL_CreateWindow("Smol16", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                           g_config.window_width, g_config.window_height,
                           SDL_WINDOW_SHOWN);
    ren     = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    display = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 256, 224);
    SDL_ShowCursor(SDL_DISABLE);
}


const uint8_t *keys;

void CBackend_SDL::EventLoop()
{
    keys = SDL_GetKeyboardState(NULL);
    //Input * input = Input::instance();
    SDL_Event e;
    while (SDL_PollEvent(&e) == 1)
    {
        switch (e.type)
        {
        case SDL_QUIT:
            CSystem::instance()->running = false;
            break;

        case SDL_TEXTINPUT:
            //HandleTextInput(e);
            break;
        }
        HandleInput(e);
    }
}


void CBackend_SDL::Render(color_t *ppu)
{
    if (g_config.noGraphics)
    {
        return;
    }
    SDL_RenderClear(ren);
    int  pitch;
    void *pixels;
    SDL_LockTexture(display, NULL, &pixels, &pitch);
    memcpy(pixels, ppu, 256 * 224 * sizeof(color_t));
    SDL_UnlockTexture(display);

    SDL_RenderCopy(ren, display, NULL, NULL);
    SDL_RenderPresent(ren);
}


void CBackend_SDL::HandleTextInput(SDL_Event ev)
{
    SDL_Event e = ev;

    if (!(((e.text.text[0] == 'c') || (e.text.text[0] == 'C')) &&
          ((e.text.text[0] == 'v') || (e.text.text[0] == 'V')) &&
          SDL_GetModState() & KMOD_CTRL))
    {
        //Append character
        Input::input_text += e.text.text;
    }
}


void CBackend_SDL::HandleInput(SDL_Event ev)
{
    Input *input = Input::instance();

    input->SetButton(BUTTON_UP, keys[SDL_SCANCODE_UP]);
    input->SetButton(BUTTON_RIGHT, keys[SDL_SCANCODE_RIGHT]);
    input->SetButton(BUTTON_DOWN, keys[SDL_SCANCODE_DOWN]);
    input->SetButton(BUTTON_LEFT, keys[SDL_SCANCODE_LEFT]);
    input->SetButton(BUTTON_A, keys[SDL_SCANCODE_Z]);
    input->SetButton(BUTTON_B, keys[SDL_SCANCODE_X]);
    input->SetButton(BUTTON_X, keys[SDL_SCANCODE_A]);
    input->SetButton(BUTTON_Y, keys[SDL_SCANCODE_S]);
    input->SetButton(BUTTON_LMB, (SDL_GetMouseState(&input->mouseX,
                                                    &input->mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT)) > 0);

    if (keys[SDL_SCANCODE_RETURN])
    {
        Input::lastchar_submit = true;
    }
}


void CBackend_SDL::LoadFont()
{
    SDL_Surface *loadedSurface = IMG_Load("data/font.png");

    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", "font.png", IMG_GetError());
        return;
    }

    loadedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_ARGB32, 0);
    // We now need to analyse the pixels! We're assuming a 128 x 18 pixel image, monochrome
    int wrap_x = 128;
    int cols   = 32;
    int rows   = 3;
    // We're encoding the pixel data into a character. Each char. becomes 3 bytes.
    int      size    = 3 * cols * rows;
    uint8_t  *buffer = new uint8_t[size];
    uint32_t *pixels = reinterpret_cast<uint32_t *>(loadedSurface->pixels);

    int      x_pos = 0;
    int      y_pos = 0;
    uint32_t index = 0;
    //Each row
    for (int row = 0; row < rows; row++)
    {
        //Each character
        for (int col = 0; col < cols; col++)
        {
            x_pos = col * 4;
            y_pos = row * 6;

            // For each character
            // * Get the pixels in hline 1 and 2 (8px, 4 per hline)
            // * Decode, store as single byte. index++.
            //  0xFF means "White", 0x00 means "transparent"
            uint8_t byte_data[3][8];
            int     byte_index = 0;
            //Line 1
            byte_data[byte_index][0] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][1] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][2] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][3] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            y_pos++;
            x_pos -= 4;
            byte_data[byte_index][4] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][5] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][6] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][7] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            y_pos++;
            x_pos -= 4;
            byte_index++;
            byte_data[byte_index][0] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][1] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][2] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][3] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            y_pos++;
            x_pos -= 4;
            byte_data[byte_index][4] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][5] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][6] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][7] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            y_pos++;
            x_pos -= 4;
            byte_index++;
            byte_data[byte_index][0] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][1] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][2] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][3] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            y_pos++;
            x_pos -= 4;
            byte_data[byte_index][4] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][5] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][6] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            byte_data[byte_index][7] = GetFromBuffer(pixels, x_pos++, y_pos, wrap_x);
            y_pos++;
            x_pos -= 4;
            byte_index++;

            for (int bi = 0; bi < 3; bi++)
            {
                uint8_t byte = 0x00;
                for (int i = 0; i < 8; ++i)
                {
                    if (byte_data[bi][i] > 0)
                    {
                        byte |= 1 << i;
                    }
                }
                buffer[index++] = byte;
            }
        }
    }
    CPPU *ppu = CPPU::instance();
    for (uint32_t i = 0; i < index; i++)
    {
        ppu->Poke8(0xF000 + i, buffer[i]);
    }
}


#endif
