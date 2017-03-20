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
#define MEM_VRAM_FONT 0x1F000
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

    // Memory functions inlined to save performance! It genuinely saves alot
    inline void Poke8(int address, uint8_t data) {
        ram[address] = data;
    }
    inline void Poke16(int address, uint16_t data) {
        Poke8(address + 1, (unsigned char)(data & 0x00ff));
        Poke8(address, (unsigned char)((data & 0xff00) >> 8));
    }
    inline uint8_t  Peek8  (address_t address) {
        return ram[address];
    }
    inline uint16_t  Peek16 (address_t address) {
        uint8_t a = Peek8(address);
        uint8_t b = Peek8(address + 1);
        return (uint16_t)((a << 8) | (b & 0xff));
    }


    // Static versions for Lua
    static void Lua_Poke8  (address_t address, int data);
    static void Lua_Poke16 (address_t address, int data);
    static int  Lua_Peek8  (address_t address);
    static int  Lua_Peek16 (address_t address);
};
