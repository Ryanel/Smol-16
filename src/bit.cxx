#include <bit.h>
uint8_t ito8(int num) {
    // Chop off everything but the last byte
    return num & 0xFF;
}

uint16_t ito16(int num) {
    // Chop off everything but the last 2 bytes
    return num & 0xFFFF;
}
