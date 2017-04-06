#include <cpu/interpreter.hpp>

PRO_INS(unknown);
PRO_INS(nop);
PRO_INS(hlt);
PRO_INS(jp);

// Loads
PRO_INS(ldw_n);
PRO_INS(ldw_a);
PRO_INS(ldw_r);

// Shifts & Bits
PRO_INS(shr_n);
PRO_INS(shr_r);
PRO_INS(shl_n);
PRO_INS(shl_r);

// Math
PRO_INS(xor_r);
PRO_INS(xor_n);
PRO_INS(or_r);
PRO_INS(or_n);
PRO_INS(and_r);
PRO_INS(and_n);

void CCpu::InterpretCycle() {

    uint8_t opcode = (sys->mem->ReadShort(regs[15].val) & 0xFF00) >> 8;
    //_log->debug("INTP 0x{0:04X}: 0x{1:04X} 0x{2:04X}", regs[15].val, sys->mem->ReadShort(regs[15].val), sys->mem->ReadShort(regs[15].val + 2));
    switch (opcode) {
        case 0x00: CALL_INS(nop); break;
        case 0x01: CALL_INS(ldw_n); break;
        case 0x03: CALL_INS(ldw_a); break;
        case 0x05: CALL_INS(ldw_r); break;
        case 0x20: CALL_INS(jp); break;

        case 0x74: CALL_INS(shr_n); break;
        case 0x75: CALL_INS(shr_r); break;
        case 0x76: CALL_INS(shl_n); break;
        case 0x77: CALL_INS(shl_r); break;

        case 0x83: CALL_INS(and_r); break;
        case 0x84: CALL_INS(xor_n); break;
        case 0x85: CALL_INS(xor_r); break;
        case 0x87: CALL_INS(or_r); break;

        case 0xFE: CALL_INS(hlt); break;
        case 0xFF: CALL_INS(hlt); break;
        default: CALL_INS(unknown); break;
    }
}
