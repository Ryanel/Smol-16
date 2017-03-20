#include <memory.hpp>
#include <smol16.hpp>
#include <config.h>
#include <spdlog/spdlog.h>
CMemory * CMemory::m_instance = NULL;

CMemory * CMemory::instance() {
   if(!m_instance) {m_instance = new CMemory();}
   return m_instance;
}

CMemory::CMemory() {
    _log = spdlog::stdout_color_mt("mem");
    ram = new uint8_t[CONFIG_RAMSIZE]; // Allocate RAM buffer
    getGlobalNamespace (CSystem::instance()->L)
    .beginNamespace ("mem")
        .addFunction ("poke8", &CMemory::Lua_Poke8)
        .addFunction ("poke16", &CMemory::Lua_Poke16)
        .addFunction ("peek8", &CMemory::Lua_Peek8)
        .addFunction ("peek16", &CMemory::Lua_Peek16)
    .endNamespace ();
    _log->debug("Memory initialised");
}

void CMemory::Poke8(address_t address, uint8_t data) {
    mem_accesses++;
}
void CMemory::Poke16(address_t address, uint16_t data) {
    mem_accesses++;
}
uint8_t  CMemory::Peek8  (address_t address) {
    mem_accesses++;
}
uint16_t  CMemory::Peek16 (address_t address) {
    mem_accesses++;
}
/*! Writes a 8bit value to address*/
void CMemory::Lua_Poke8(int address, int data) {
    m_instance->lua_mem_accesses++;
    return m_instance->Poke8(address, data);
}
/*! Writes a 16bit value to address*/
void CMemory::Lua_Poke16(int address, int data) {
    m_instance->lua_mem_accesses++;
    return m_instance->Poke16(address, data);
}
/*! Reads a 8bit value from address*/
int CMemory::Lua_Peek8(int address) {
    m_instance->lua_mem_accesses++;
    return m_instance->Peek8(address);
}
/*! Reads a 16bit value from address*/
int CMemory::Lua_Peek16(int address) {
    m_instance->lua_mem_accesses++;
    return m_instance->Peek16(address);
}
