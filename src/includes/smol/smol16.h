#pragma once
#include <cstdint>
#include <cstddef>
#include <smol/memory.h>
#include <smol/display.h>
#include <smol/input.h>
extern "C" {
    #include "lualib.h"
    #include "lauxlib.h"
    #include "lua.h"
}


#include <selene.h>

class Smol16 {
private:
    int stat_failedcalls = 0;

    bool isExecutionPaused = false;
public:
    int stat_statements_frame = 0;
    int maxStatementsPerFrame = 10;
    sel::State * lua;
    Memory * mem;
    Display * display;
    Input * input;
    bool isRunning;

    Smol16();
    ~Smol16();
    void Init();
    void Sleep();
    void Wake();
    bool CheckRender();

    // Lua functions
    void Call(const char * func);
    void LoadCart(const char * location);
    template <typename T> void Register(const char *name,T func) { (*lua)[name] = func; }
    static void LuaHook(lua_State *L, lua_Debug *ar);
};

extern Smol16 * sys;
