#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <render_sdl.h>
#include <smol/display.h>
#include <smol/smol16.h>
#include <smol/input.h>
SDL_Window *SDLRenderer::win;
SDL_Renderer *SDLRenderer::ren;
SDL_Texture *SDLRenderer::display;
std::shared_ptr<spdlog::logger> SDLRenderer::_logger;

uint8_t GetFromBuffer(uint32_t * buf, int x, int y, int width) {
    return buf[y * width + x];
}

void SDLRenderer::Init() {
    _logger = spdlog::get("sdl");
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
		_logger->error("Failed to init SDL");
        exit(1);
	}
	win = SDL_CreateWindow("Smol-16", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        Display::width * Display::scale, Display::height * Display::scale,
        SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    display = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, Display::width, Display::height);
    SDL_ShowCursor(SDL_DISABLE);

    _logger->info("Initialised");

}

void SDLRenderer::Cleanup() {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void SDLRenderer::Flip() {
    SDL_RenderClear(ren);

    Display * d = Display::instance();
    color_t * data = d->Render();
    int pitch;
    void* pixels;
    SDL_LockTexture(display, NULL, &pixels, &pitch );
    memcpy(pixels, data ,Display::width * Display::height * sizeof(color_t));
    SDL_UnlockTexture( display );

    SDL_RenderCopy(ren, display, NULL, NULL);
    SDL_RenderPresent(ren);
}

void SDLRenderer::LoadFont() {
    SDL_Surface* loadedSurface = IMG_Load( "data/font.png" );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", "font.png", IMG_GetError() );
        return;
    }

    loadedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_ARGB32, 0);
    // We now need to analyse the pixels! We're assuming a 128 x 18 pixel image, monochrome
    int wrap_x = 128;
    int cols = 32;
    int rows = 3;
    // We're encoding the pixel data into a character. Each char. becomes 3 bytes.
    int size = 3 * cols * rows;
    uint8_t * buffer = new uint8_t[size];
    uint32_t * pixels = reinterpret_cast<uint32_t*>(loadedSurface->pixels);

    int x_pos = 0;
    int y_pos = 0;
    uint32_t index = 0;
    //Each row
    for(int row = 0; row < rows; row++) {
        //Each character
        for(int col = 0; col < cols; col++) {
            x_pos = col * 4;
            y_pos = row * 6;

            // For each character
            // * Get the pixels in hline 1 and 2 (8px, 4 per hline)
            // * Decode, store as single byte. index++.
            //  0xFF means "White", 0x00 means "transparent"
            uint8_t byte_data[3][8];
            int byte_index = 0;
            //Line 1
            byte_data[byte_index][0] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][1] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][2] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][3] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            y_pos++; x_pos -= 4;
            byte_data[byte_index][4] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][5] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][6] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][7] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            y_pos++; x_pos -= 4; byte_index++;
            byte_data[byte_index][0] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][1] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][2] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][3] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            y_pos++; x_pos -= 4;
            byte_data[byte_index][4] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][5] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][6] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][7] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            y_pos++; x_pos -= 4; byte_index++;
            byte_data[byte_index][0] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][1] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][2] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][3] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            y_pos++; x_pos -= 4;
            byte_data[byte_index][4] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][5] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][6] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            byte_data[byte_index][7] = GetFromBuffer(pixels,x_pos++, y_pos, wrap_x);
            y_pos++; x_pos -= 4; byte_index++;

            for(int bi = 0; bi < 3; bi++) {
                uint8_t byte = 0x00;
                for (int i=0; i < 8; ++i) {
                    if (byte_data[bi][i] > 0) {
                        byte |= 1 << i;
                    }
                }
                buffer[index++] = byte;
            }
        }
    }
    Memory * mem = Memory::instance();
    for (uint32_t i = 0; i < index; i++) {
        mem->Poke8(MEM_VRAM_FONT + i, buffer[i]);
    }
    _logger->info("Font loaded from data/font.png");
}


void SDLRenderer::EventLoop() {

    const uint8_t *keys = SDL_GetKeyboardState(NULL);
    Input * input = Input::instance();
    SDL_Event e;
    while (SDL_PollEvent(&e)){
    	//If user closes the window
    	if (e.type == SDL_QUIT){
    		sys->isRunning = false;
    	}

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
    }
}
