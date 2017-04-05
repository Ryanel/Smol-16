#include <cpu/interpreter.hpp>

void CCpu::InterpretCycle() {

    uint8_t opcode = (sys->mem->ReadShort(regs[15].val) & 0xFF00) >> 8;
    //_log->debug("INTP 0x{0:04X}: 0x{1:04X} 0x{2:04X}", regs[15].val, sys->mem->ReadShort(regs[15].val), sys->mem->ReadShort(regs[15].val + 2));
    switch (opcode) {
        case 0x00: CALL_INS(nop); break;
        case 0x20: CALL_INS(jp); break;
        case 0xFE: CALL_INS(hlt); break;
        case 0xFF: CALL_INS(hlt); break;
        default: CALL_INS(unknown); break;
    }
}
