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
    lua->Load("data/std/std.lua");
    Register("stat_cpu", &Smol16::LuaGetCPU);
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

void Smol16::Call(std::string func) {
    try {
        (*lua)[func.c_str()]();
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

void Smol16::LoadCart(std::string location) {
    cartPath = location;
    std::string code_path = location + "/main.lua";
    (*lua)["_cart_path"] = location.c_str();
    LoadFile(code_path);
}

int Smol16::LuaGetCPU() {
    return sys->cpu_usage;
}

void Smol16::LoadFile(std::string location) {
    try {
        lua->Load(location);
    } catch(...) {

    }
}
