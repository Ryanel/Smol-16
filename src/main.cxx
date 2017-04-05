#include <config.h>
#include <sys_config.hpp>
#include <string>
#include <iostream>
#include <spdlog/spdlog.h>
#include <system.hpp>
#include <args.hpp>

CSystem * sys;

int main(int argc, char *argv[]) {

    // Init logging
    spdlog::set_pattern("[%n] %v");
    spdlog::set_level(spdlog::level::debug);

    // Init config
    g_config.Init();
    // Process arguments
    ProcessArgs(argc, argv);

    // Init system
    sys = CSystem::instance();
    sys->Init();

    for (size_t i = 0; i < 16; i++) {
        sys->Tick();
        if (!sys->isRunning) {
            break;
        }
    }
    sys->cpu->StatusReport();



    return 0;
}
