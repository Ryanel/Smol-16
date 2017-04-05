#pragma once
#include <cstdint>
#include <cstddef>
#include <spdlog/spdlog.h>

typedef uint16_t address_t;

class CMemoryDevice {
public:
    std::string name;
    virtual uint8_t  ReadByte  (address_t address) = 0;
    virtual uint16_t ReadShort (address_t address) = 0;
    virtual void     WriteByte (address_t address, uint8_t  data) = 0;
    virtual void     WriteShort(address_t address, uint16_t data) = 0;
    virtual uint64_t GetSize() = 0;
};

typedef struct mem_map {
	/// The device that is mappped
	CMemoryDevice * dev;
	/// Where its domain starts
	address_t start;
	/// Where its domain ends
	address_t end;
} mem_map_t;


class CMemoryController {
private:
    static CMemoryController *m_instance;
    std::shared_ptr<spdlog::logger> _log;
    CMemoryController();
public:
    static CMemoryController *instance();
    long stat_mem_accesses     = 0;

    void Map(CMemoryDevice * device, address_t start);
    void Unmap(mem_map_t * device);
    static address_t TranslateAddress(mem_map_t * dev, address_t address);
    mem_map_t * GetDeviceForAddress(address_t address);
    static bool compareMappings(mem_map_t * a, mem_map_t * b);

    uint8_t  ReadByte  (address_t address);
    uint16_t ReadShort (address_t address);
    void     WriteByte (address_t address, uint8_t  data);
    void     WriteShort(address_t address, uint16_t data);

    std::vector<CMemoryDevice*> visible_devices;
    std::vector<mem_map_t*> mappings;
};
