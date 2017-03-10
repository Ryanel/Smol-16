#pragma once
#include <cstdint>
#include <cstddef>

#define MEM_WRAM 0x0
#define MEM_VRAM 0x10000
#define MEM_VRAM_FRAMEBUFFER 0x10000
#define MEM_VRAM_PCT 0x1E000
#define MEM_VRAM_SPT 0x1E200
#define MEM_VRAM_BG0 0x1EA00
#define MEM_VRAM_SAT 0x1EE00
//TODO: I still have a whole 0x1000 here!
#define MEM_VRAM_REGISTER_BASE 0x1FF00
#define MEM_VRAM_SPRITES 0x20000

typedef int address_t;

class Memory {
private:
    static Memory * m_instance;
    Memory();
public:

    static Memory *instance();
    uint8_t * ram;
    void Init();

    static int GetAddress(int address);

    void Poke8  (address_t address, int data);
    void Poke16 (address_t address, int data);
    uint8_t  Peek8  (address_t address);
    uint16_t  Peek16 (address_t address);


    // Static versions for Lua
    static void Lua_Poke8  (address_t address, int data);
    static void Lua_Poke16 (address_t address, int data);
    static int  Lua_Peek8  (address_t address);
    static int  Lua_Peek16 (address_t address);
};
