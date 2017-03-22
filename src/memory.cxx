#include <memory.hpp>
#include <smol16.hpp>
#include <config.h>
#include <spdlog/spdlog.h>
CMemory *CMemory::m_instance = NULL;

CMemory *CMemory::instance()
{
    if (!m_instance)
    {
        m_instance = new CMemory();
    }
    return m_instance;
}


CMemory::CMemory()
{
    _log = spdlog::stdout_color_mt("mem");
    ram  = new uint8_t[CONFIG_RAMSIZE]; // Allocate RAM buffer
    memset(ram, 0, CONFIG_RAMSIZE);
    getGlobalNamespace(CSystem::instance()->L)
       .beginNamespace("mem")
       .addFunction("poke8", &CMemory::Lua_Poke8)
       .addFunction("poke16", &CMemory::Lua_Poke16)
       .addFunction("peek8", &CMemory::Lua_Peek8)
       .addFunction("peek16", &CMemory::Lua_Peek16)
       .endNamespace();
    _log->debug("Memory initialised");
}


void CMemory::Poke8(address_t address, uint8_t data)
{
    mem_accesses++;
    ram[address] = data;
}


void CMemory::Poke16(address_t address, uint16_t data)
{
    Poke8(address + 1, (unsigned char)(data & 0x00ff));
    Poke8(address + 0, (unsigned char)((data & 0xff00) >> 8));
}


uint8_t CMemory::Peek8(address_t address)
{
    mem_accesses++;
    return ram[address];
}


uint16_t CMemory::Peek16(address_t address)
{
    uint8_t a = Peek8(address);
    uint8_t b = Peek8(address + 1);

    return (uint16_t)((a << 8) | (b & 0xff));
}


/*! Writes a 8bit value to address*/
void CMemory::Lua_Poke8(int address, int data)
{
    m_instance->lua_mem_accesses++;
    return m_instance->Poke8(address, data);
}


/*! Writes a 16bit value to address*/
void CMemory::Lua_Poke16(int address, int data)
{
    m_instance->lua_mem_accesses++;
    return m_instance->Poke16(address, data);
}


/*! Reads a 8bit value from address*/
int CMemory::Lua_Peek8(int address)
{
    m_instance->lua_mem_accesses++;
    return m_instance->Peek8(address);
}


/*! Reads a 16bit value from address*/
int CMemory::Lua_Peek16(int address)
{
    m_instance->lua_mem_accesses++;
    return m_instance->Peek16(address);
}
