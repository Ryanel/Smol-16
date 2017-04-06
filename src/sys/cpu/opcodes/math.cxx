#include <cpu/interpreter.hpp>

DEF_INS(inc_r) {
    uint8_t rega = (opcode & 0x00F0) >> 4;

    //LOG_INS_1REG(inc, rega);

    cpu->regs[rega].val++;

    ADVANCE_PC(1);
    DO_CYCLES(1);
    END_OPCODE();
}


DEF_INS(shl_n) {
    uint8_t rega = (opcode & 0x00F0) >> 4;
    uint16_t val = cpu->sys->mem->ReadShort(cpu->regs[15].val + 2);
    LOG_INS_REG_1OP(shl, rega, val, "#");

    cpu->regs[rega].val = cpu->regs[rega].val << val;

    ADVANCE_PC(2);
    DO_CYCLES(1);
    END_OPCODE();
}
DEF_INS(shr_n) {
    uint8_t rega = (opcode & 0x00F0) >> 4;
    uint16_t val = cpu->sys->mem->ReadShort(cpu->regs[15].val + 2);
    LOG_INS_REG_1OP(shl, rega, val, "#");
    cpu->regs[rega].val = cpu->regs[rega].val >> val;
    ADVANCE_PC(2);
    DO_CYCLES(1);
    END_OPCODE();
}


DEF_INS(shr_r) {
    uint8_t rega = (opcode & 0x00F0) >> 4;
    uint8_t regb = opcode & 0x000F;

    LOG_INS_2REG(xor, regb, rega);

    cpu->regs[regb].val = cpu->regs[rega].val >> cpu->regs[regb].val;

    ADVANCE_PC(1);
    DO_CYCLES(1);
    END_OPCODE();
}

DEF_INS(shl_r) {
    uint8_t rega = (opcode & 0x00F0) >> 4;
    uint8_t regb = opcode & 0x000F;

    LOG_INS_2REG(xor, regb, rega);

    cpu->regs[regb].val = cpu->regs[rega].val << cpu->regs[regb].val;

    ADVANCE_PC(1);
    DO_CYCLES(1);
    END_OPCODE();
}

DEF_INS(xor_n) {
    uint8_t rega = (opcode & 0x00F0) >> 4;
    uint16_t val = cpu->sys->mem->ReadShort(cpu->regs[15].val + 2);
    LOG_INS_REG_1OP(xor, rega, val, "#");

    cpu->regs[rega].val = cpu->regs[rega].val ^ val;

    ADVANCE_PC(2);
    DO_CYCLES(1);
    END_OPCODE();
}


DEF_INS(xor_r) {
    uint8_t rega = (opcode & 0x00F0) >> 4;
    uint8_t regb = opcode & 0x000F;

    LOG_INS_2REG(xor, regb, rega);

    cpu->regs[regb].val = cpu->regs[rega].val ^ cpu->regs[regb].val;

    ADVANCE_PC(1);
    DO_CYCLES(1);
    END_OPCODE();
}

DEF_INS(or_n) {
    uint8_t rega = (opcode & 0x00F0) >> 4;
    uint16_t val = cpu->sys->mem->ReadShort(cpu->regs[15].val + 2);
    LOG_INS_REG_1OP(xor, rega, val, "#");

    cpu->regs[rega].val = cpu->regs[rega].val | val;

    ADVANCE_PC(2);
    DO_CYCLES(1);
    END_OPCODE();
}

DEF_INS(or_r) {
    uint8_t rega = (opcode & 0x00F0) >> 4;
    uint8_t regb = opcode & 0x000F;

    LOG_INS_2REG(or, regb, rega);

    cpu->regs[regb].val = cpu->regs[rega].val | cpu->regs[regb].val;

    ADVANCE_PC(1);
    DO_CYCLES(1);
    END_OPCODE();
}

DEF_INS(and_n) {
    uint8_t rega = (opcode & 0x00F0) >> 4;
    uint16_t val = cpu->sys->mem->ReadShort(cpu->regs[15].val + 2);
    LOG_INS_REG_1OP(xor, rega, val, "#");

    cpu->regs[rega].val = cpu->regs[rega].val & val;

    ADVANCE_PC(2);
    DO_CYCLES(1);
    END_OPCODE();
}

DEF_INS(and_r) {
    uint8_t rega = (opcode & 0x00F0) >> 4;
    uint8_t regb = opcode & 0x000F;

    LOG_INS_2REG(and, regb, rega);

    cpu->regs[regb].val = cpu->regs[rega].val & cpu->regs[regb].val;

    ADVANCE_PC(1);
    DO_CYCLES(1);
    END_OPCODE();
}
