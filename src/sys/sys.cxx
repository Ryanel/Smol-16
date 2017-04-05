#include <memory.hpp>
#include <mem/ram.hpp>
#include <system.hpp>
#include <cpu/cpu.hpp>
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
    _log->debug("Memory Mapped");
    _log->info("Initialised");

    mem->WriteShort(0x02, 0x01A1);
    mem->WriteShort(0x04, 0xABCD);
    mem->WriteShort(0x06, 0x0140);
    mem->WriteShort(0x08, 0x0002);


    mem->WriteShort(0x010, 0x6401);
}

void CSystem::Tick() {
    cpu->Tick();
}
