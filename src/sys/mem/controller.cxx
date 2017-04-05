#include <algorithm>
#include <memory.hpp>
#include <config.h>
#include <spdlog/spdlog.h>
#include <sys_config.hpp>

CMemoryController *CMemoryController::m_instance = NULL;

CMemoryController *CMemoryController::instance() {
    if (!m_instance) {
        m_instance = new CMemoryController();
    }
    return m_instance;
}


CMemoryController::CMemoryController() {
    _log = spdlog::stdout_color_mt("mmu");
    _log->debug("Initialised");
}

bool CMemoryController::compareMappings(mem_map_t * a, mem_map_t * b) {
    return a->start < b->start;
}

void CMemoryController::Map(CMemoryDevice * device, address_t start) {
	mem_map_t * mapping = new mem_map_t;
	mapping->dev = device;
	mapping->start = start;
	mapping->end = device->GetSize() + start - 1;
	visible_devices.push_back(device);

	mappings.push_back(mapping);

	std::sort(mappings.begin(), mappings.end(), compareMappings);
    if (g_config.enableDebugging) {
        _log->info("Mapped {0:6s} to 0x{1:04X} => 0x{2:04X}", mapping->dev->name, mapping->start, mapping->end); return;
    }

}

void CMemoryController::Unmap(mem_map_t * device) {
    // We just find and erase to avoid resorting.
    auto dev = std::find(mappings.begin(), mappings.end(), device);
    if(dev != mappings.end()) {
        mappings.erase(dev);
    } else {
        _log->error("Attempted to unmap invalid region 0x{0:X} => 0x{1:X}!", device->start, device->end); return;
        if(g_config.abortOnError) {exit(1);}
    }
}

mem_map_t * CMemoryController::GetDeviceForAddress(address_t address) {
	for (mem_map_t * dev: mappings) {
		if (address >= dev->start && address <= dev->end) {
			return dev;
		}
	}
	return nullptr;
}

address_t CMemoryController::TranslateAddress(mem_map_t * dev, address_t address) {
	return address - dev->start;
}

uint8_t CMemoryController::ReadByte (address_t address) {
    mem_map_t * dev = GetDeviceForAddress(address);
    if (dev == nullptr) {
        _log->warn("Unmapped read (byte) to 0x{0:X}!", address); return 0;
        if(g_config.abortOnError) {exit(1);}
    }
    return dev->dev->ReadByte(TranslateAddress(dev, address));
}
uint16_t CMemoryController::ReadShort (address_t address) {
    mem_map_t * dev = GetDeviceForAddress(address);
    if (dev == nullptr) {
        _log->warn("Unmapped read (short) to 0x{0:X}!", address); return 0;
        if(g_config.abortOnError) {exit(1);}
    }
    return dev->dev->ReadShort(TranslateAddress(dev, address));
}
void CMemoryController::WriteByte (address_t address, uint8_t  data) {
    mem_map_t * dev = GetDeviceForAddress(address);
    if (dev == nullptr) {
        _log->warn("Unmapped write (byte) to 0x{0:X}!", address); return;
        if(g_config.abortOnError) {exit(1);}
    }
    dev->dev->WriteByte(TranslateAddress(dev, address), data);
}
void CMemoryController::WriteShort(address_t address, uint16_t data) {
    mem_map_t * dev = GetDeviceForAddress(address);
    if (dev == nullptr) {
        _log->warn("Unmapped write (short) to 0x{0:X}!", address); return;
        if(g_config.abortOnError) {exit(1);}
    }

    dev->dev->WriteShort(TranslateAddress(dev, address), data);
}
