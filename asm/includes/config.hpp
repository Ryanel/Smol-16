#pragma once
#include <string>
void ProcessArgs(int argc, char *argv[]);

class CConfig {
public:
    std::string fileName;
    std::string output;
};

extern CConfig g_config;
