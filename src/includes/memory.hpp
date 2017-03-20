#pragma once
#include <cstdint>
#include <cstddef>
#include <spdlog/spdlog.h>

/*
#define MEM_VRAM 0x10000
#define MEM_VRAM_FRAMEBUFFER 0x10000
#define MEM_VRAM_PCT 0x1E000
#define MEM_VRAM_SPT 0x1E200
#define MEM_VRAM_SAT 0x1EE00
#define MEM_VRAM_FONT 0x1F000
#define MEM_VRAM_REGISTER_BASE 0x1FF00
*/
typedef int address_t;
class CMemory {
private:
    static CMemory * m_instance;
    std::shared_ptr<spdlog::logger> _log;
    CMemory();
public:
    static CMemory *instance();
    uint8_t * ram;
    void Init();
    long mem_accesses = 0;
    long lua_mem_accesses = 0;
    // Memory functions inlined to save performance! It genuinely saves alot
    void Poke8(address_t address, uint8_t data);
    void Poke16(address_t address, uint16_t data);
    uint8_t  Peek8  (address_t address);
    uint16_t  Peek16 (address_t address);
    // Static versions for Lua
    static void Lua_Poke8  (address_t address, int data);
    static void Lua_Poke16 (address_t address, int data);
    static int  Lua_Peek8  (address_t address);
    static int  Lua_Peek16 (address_t address);
};
