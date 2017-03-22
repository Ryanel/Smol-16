#pragma once
#include <string>

class CConfig {
public:
    std::string cart_path;
    bool enableDebugging;
    bool noGraphics;
    bool standalone;
    int window_width  = 256 * 3;
    int window_height = 224 * 3;
    std::string std_path;
    void Init();
    void Load();
};

extern CConfig g_config;
