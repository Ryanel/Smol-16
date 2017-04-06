#include <config.h>
#include <string>
#include <cstdio>
#include <iostream>
#include <spdlog/spdlog.h>

#include "includes/file.hpp"
#include "includes/config.hpp"

void Assemble_Step1(AsmFile * file);

int main(int argc, char *argv[]) {
    // Init logging
    spdlog::set_pattern("[%n] %v");
    spdlog::set_level(spdlog::level::debug);
    // Process arguments
    ProcessArgs(argc, argv);

    g_config.fileName = "test.asm";
    if (g_config.fileName == "") {
        printf("No file!\n");
        return 1;
    }

    AsmFile * file = new AsmFile(g_config.fileName);
    file->Tokenize();

    Assemble_Step1(file);
    return 0;
}
