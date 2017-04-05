#include <sys_config.hpp>
CConfig g_config;

void CConfig::Init()
{
    this->enableDebugging = true;
    this->enforceAlignedAccess = true;
}
