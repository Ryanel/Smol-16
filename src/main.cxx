#include <config.h>
#include <iostream>
#include <cxxopts.hpp>
#include <smol_timer.h>
#include <render_sdl.h>
#include <smol/smol16.h>
#include <smol/sound.h>
#include <spdlog/spdlog.h>
Timer fpsCapTimer;
void Init() {
    sys = new Smol16();
    sys->Init();

    SDLRenderer::Init();
    Sound * snd = Sound::instance();
    snd->Init();
    SDLRenderer::LoadFont();
}

void MainLoop() {
    // Main loop
    sys->Call("_init");
    SDLRenderer::Flip();

    while(sys->isRunning) {
        fpsCapTimer.Start();
        sys->input->Update();
        SDLRenderer::EventLoop();
        sys->Call("_update");
        sys->Call("_draw");
        // Calculate FPS
        if(sys->CheckRender()) {
            SDLRenderer::Flip();
        }



        // Calculate CPU usage and frame delay.
        int frameTicks = fpsCapTimer.GetTicks();
        float margin = TICKS_PER_FRAME - frameTicks;
        if( frameTicks <= TICKS_PER_FRAME ) {
            SDL_Delay( TICKS_PER_FRAME - frameTicks );
        }
        else {
            margin = abs(margin);
        }
        float cpu = (float)((TICKS_PER_FRAME - frameTicks));    // > 0 == < 100% cpu
                                                                // < 0 == > 100% cpu
        if(cpu >= 0) {
            float val = 16 - cpu;
            if(val < 1) {val = 1;}
            val = 100 / val;
            cpu = val;
        } else {
            float val = abs(cpu);
            val = val * TICKS_PER_FRAME;
            cpu = val;
        }
        sys->cpu_usage = cpu;
        //printf("CPU: %2.2f%\n", cpu);
    }
}

int main (int argc, char *argv[]) {
    auto main = spdlog::stdout_color_mt("main");
    auto lua =  spdlog::stdout_color_mt("lua");
    auto sdl =  spdlog::stdout_color_mt("sdl");
    spdlog::set_pattern("[%H:%M:%S] [%n] %v");
    // Parse command line options.
    cxxopts::Options options("smol16", "A 16bit style fantasy console");
    options.add_options()
        ("d,debug", "Enable debugging")
        ("help", "Print help")
        ("i,input", "Input", cxxopts::value<std::string>())
        ;

    options.parse_positional({"input", "output", "positional"});
    options.parse(argc, argv);

    if (options.count("help")) { // Display helpt
        std::cout << options.help({""}) << std::endl;
        exit(0);
    }

    std::string file;

    if (options.count("input")) { // Get cart name
        main->info("Loading cart {}",options["input"].as<std::string>());
        file = options["input"].as<std::string>();
    } else {
        file = "carts/editor";
    }

    Init();
    sys->LoadCart(file);
    // Enter the main loop!
    MainLoop();
    // And now cleanup.
    SDLRenderer::Cleanup();
    return 0;
}
