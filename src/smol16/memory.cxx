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

int Memory::GetAddress(int address) {
    while(address > CONFIG_RAMSIZE) {address -= CONFIG_RAMSIZE;}
    return address;
}

/*! Writes a 8bit value to address*/
void Memory::Poke8(int address, int data) {
    //address = GetAddress(address);
    ram[address] = ito8(data);
}
/*! Writes a 16bit value to address*/
void Memory::Poke16(int address, int data) {
    //address = GetAddress(address);
    Poke8(address + 1, (unsigned char)(data & 0x00ff));
    Poke8(address, (unsigned char)((data & 0xff00) >> 8));
    //Todo, store memory little endian
}
/*! Reads a 8bit value from address*/
uint8_t Memory::Peek8(int address) {
    //address = GetAddress(address);
    return ito8(ram[address]);
}
/*! Reads a 16bit value from address*/
uint16_t Memory::Peek16(int address) {
    //address = GetAddress(address);
    uint8_t a = Peek8(address);
    uint8_t b = Peek8(address + 1);
    uint16_t ret = (uint16_t)((a << 8) | (b & 0xff));
    return ret;
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
