#include <mem/ram.hpp>
#include <cstring>
#include <cstdint>
#include <cstddef>

Memory_RAM::Memory_RAM(uint64_t size) {
	mem_size = size;
	memory = new uint8_t[mem_size];
	memset(memory, 0, size);
	//g_log->Log("MEM", "Unnamed RAM bank created (size 0x%X)", size);
}

Memory_RAM::Memory_RAM(uint64_t size, std::string dev_name) {
	mem_size = size;
	memory = new uint8_t[(size_t)mem_size];
	this->name = dev_name;
	memset(memory, 0, mem_size);
	//g_log->Log(this->name.c_str(), "RAM bank created (size 0x%X)", size);
}

Memory_RAM::~Memory_RAM()
{
	delete[] memory;
}

uint8_t Memory_RAM::ReadByte(address_t address) {
	if (address > mem_size) { return 0; }
	return memory[address];
}

uint16_t Memory_RAM::ReadShort(address_t address) {
	uint8_t a;
	uint8_t b;

	a = ReadByte(address);
	b = ReadByte(address + 1);

	uint16_t ret = (uint16_t)((a << 8) | (b & 0xff));
	return ret;
}
void Memory_RAM::WriteByte(address_t address, uint8_t data) {
	if (address > mem_size) { return; }
	memory[address] = data;
}

void Memory_RAM::WriteShort(address_t address, uint16_t data) {
	WriteByte(address + 1, (unsigned char)(data & 0x00ff));
	WriteByte(address, (unsigned char)((data & 0xff00) >> 8));
}

uint64_t Memory_RAM::GetSize() {
	return mem_size;
}
