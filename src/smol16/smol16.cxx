#include <smol/smol16.h>
#include <smol/memory.h>
Smol16 * sys;

Smol16::Smol16() {
    lua = new sel::State(true);
    isRunning = true;
}

Smol16::~Smol16() {
    delete lua;
}

void Smol16::Init() {
    mem = Memory::instance();
    display = Display::instance();
    input = Input::instance();
    lua->Load("data/std.lua");
    //lua_sethook(lua->_l, &Smol16::LuaHook, LUA_MASKCOUNT, 100);
}

void Smol16::LuaHook(lua_State *L, lua_Debug *ar) {
    // This function is static! Access global context with sys
    if(ar->event == LUA_HOOKLINE)
    {
        //sys->Sleep();
        sys->stat_statements_frame++;
    }
}

void Smol16::Call(const char * func) {
    try {
        (*lua)[func]();
    } catch (...) {
        stat_failedcalls++;
    }
}

bool Smol16::CheckRender() {
    bool shouldRender = mem->Peek8(MEM_VRAM_REGISTER_BASE + 0x0) > 0;
    if(shouldRender) {
        mem->Poke8(MEM_VRAM_REGISTER_BASE + 0x0, 0x0);
    }
    return shouldRender;
}

void Smol16::LoadCart(const char * location) {
    try {
        lua->Load(location);
    } catch(...) {

    }

}
