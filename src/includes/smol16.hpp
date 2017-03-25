#pragma once
#include <sys_config.hpp>
#include "lua.hpp" // LuaJIT
#include <memory.hpp>
#include <ppu.hpp>
#include <string>
#include <spdlog/spdlog.h>
#include <timer.hpp>

#include "LuaBridge.h"
using namespace luabridge;
struct cart_info {
    std::string path;
    std::string name;

    std::string start;
    std::string update;
    std::string irq_ppu;
    std::string irq_spu;
};

class CSystem {
private:
    static CSystem *_instance;
    Timer fpsCapTimer;
    std::shared_ptr<spdlog::logger> _log;
    CMemory *_mem;
    CPPU *_ppu;
    CSystem();
    ~CSystem();
public:
    lua_State *L;
    bool paused  = false;
    bool running = true;
    float cpu    = 0;
    struct cart_info loaded_cart;
    static CSystem *instance();
    void Init();
    void CalcCPU();
    void Export();
    void Run();
    void LoadFile(std::string path);
    void Call(std::string function);

    // Static functions
    static void StackDump(lua_State *L);
    static float Lua_GetCPU();
};
