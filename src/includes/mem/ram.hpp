#pragma once
#include <memory.hpp>
#include <cstdint>
#include <cstddef>

class Memory_RAM : public CMemoryDevice {
private:
	uint8_t * memory = NULL;
	uint64_t mem_size = 0;
protected:
	Memory_RAM();
public:
	explicit Memory_RAM(uint64_t size);
	Memory_RAM(uint64_t size, std::string dev_name);
	~Memory_RAM();

    uint8_t  ReadByte  (address_t address);
    uint16_t ReadShort (address_t address);
    void     WriteByte (address_t address, uint8_t  data);
    void     WriteShort(address_t address, uint16_t data);
	uint64_t GetSize();
};
