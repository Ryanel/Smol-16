#include <sys_config.hpp>
CConfig g_config;

void CConfig::Init()
{
    this->enableDebugging = false;
    this->noGraphics      = false;
    this->std_path        = "./data/std/std.lua";
}
