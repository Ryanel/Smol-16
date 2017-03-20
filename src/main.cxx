#include <string>
#include <iostream>
// Libraries
//#include <spdlog/spdlog.h>
//
#include <config.h>
#include <args.hpp>
#include <sys_config.hpp>
// Smol16
#include <smol16.hpp>
#ifdef BACKEND_SDL
#include <sdl_backend.hpp>
#endif

int main(int argc, char *argv[])
{
    // Initialise Logging
    spdlog::set_pattern("[%n] %v");
    spdlog::set_level(spdlog::level::debug);
    // Initialise the defaults
    g_config.Init();
    // Process command line arguments (results in g_config)
    ProcessArgs(argc, argv);
    // Now initialise the System
    CSystem *app = CSystem::instance();

    // Now, lets init based on the arguments
    if (!g_config.noGraphics)
    {
        #ifdef BACKEND_SDL
        CBackend_SDL * sdl = CBackend_SDL::instance();
        sdl->LoadFont();
        #endif
    }

    app->Init();
    app->Run();
}
