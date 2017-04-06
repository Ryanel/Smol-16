#include <memory.hpp>
#include <mem/ram.hpp>
#include <system.hpp>
#include <cpu/cpu.hpp>

#include <fstream>
#include <iostream>
#include <cstdio>

using namespace std;

CSystem *CSystem::m_instance = NULL;

CSystem *CSystem::instance()
{
    if (!m_instance)
    {
        m_instance = new CSystem();
    }
    return m_instance;
}

CSystem::CSystem()
{
    _log = spdlog::stdout_color_mt("sys");
    _log->debug("Starting...");

    mem = CMemoryController::instance();
    cpu = new CCpu();
    cpu->sys = this;
}

void CSystem::Init() {
    // Initialise hardware devices.
    cpu->Init();

    // Map system memory
    Memory_RAM * wram = new Memory_RAM(0x4000,"wram0");
    mem->Map(wram, 0x0);

    std::ifstream fin("code.bin", ios::in | ios::binary);

    if ( !fin.is_open() ) {
          exit(1);
    }
    char buffer[10];

    int ptr = 0;
    while(fin.good()) {
        fin.read(buffer, 1);
        mem->WriteByte(ptr++, buffer[0]);
    }
    fin.close();
    _log->info("Initialised");
}

void CSystem::Tick() {
    cpu->Tick();
}
