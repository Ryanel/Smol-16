#pragma once
#include <cstdint>
#include <cstddef>

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
    int  Peek8  (address_t address);
    int  Peek16 (address_t address);


    // Static versions for Lua
    static void Lua_Poke8  (address_t address, int data);
    static void Lua_Poke16 (address_t address, int data);
    static int  Lua_Peek8  (address_t address);
    static int  Lua_Peek16 (address_t address);
};
