#pragma once
#include <sys_config.hpp>
#include "lua.hpp" // LuaJIT
#include <memory.hpp>
#include <ppu.hpp>
#include <string>
#include <spdlog/spdlog.h>

#include "LuaBridge.h"
using namespace luabridge;

class CSystem {
private:
    static CSystem * _instance;
    std::shared_ptr<spdlog::logger> _log;
    CMemory * _mem;
    CPPU * _ppu;
    CSystem();
    ~CSystem();
public:
    lua_State *L;
    bool paused = false;
    bool running = true;
    static CSystem * instance();
    void Init();
    void CalcCPU();
    void Export();
    void Run();
    void LoadFile(std::string path);
    void Call(std::string function);

    // Static functions
    static void StackDump (lua_State *L);
};
