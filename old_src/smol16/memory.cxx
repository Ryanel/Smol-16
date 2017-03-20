#include <bit.h>
#include <smol/memory.h>
#include <smol/smol16.h>
#include <config.h>
#include <font.h>
#include <string.h>
Memory * Memory::m_instance;

Memory * Memory::instance()
{
   if(!m_instance) {m_instance = new Memory();}
   return m_instance;
}

Memory::Memory() {
    ram = new uint8_t[CONFIG_RAMSIZE]; // Allocate RAM buffer
    // Register functions
    sys->Register("poke8", &Memory::Lua_Poke8);
    sys->Register("poke16",&Memory::Lua_Poke16);
    sys->Register("peek8" ,&Memory::Lua_Peek8);
    sys->Register("peek16",&Memory::Lua_Peek16);
}

void Memory::Lua_Poke8(int address, int data) {
    return m_instance->Poke8(address, data);
}
/*! Writes a 16bit value to address*/
void Memory::Lua_Poke16(int address, int data) {
    return m_instance->Poke16(address, data);
}
/*! Reads a 8bit value from address*/
int Memory::Lua_Peek8(int address) {
    return m_instance->Peek8(address);
}
/*! Reads a 16bit value from address*/
int Memory::Lua_Peek16(int address) {
    return m_instance->Peek16(address);
}