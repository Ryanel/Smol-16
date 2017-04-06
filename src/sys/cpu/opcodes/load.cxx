#include <cpu/interpreter.hpp>

DEF_INS(ldw_n) {
    uint8_t reg = (opcode & 0x00F0) >> 4;
    uint16_t val = cpu->sys->mem->ReadShort(cpu->regs[15].val + 2);
    LOG_INS_REG_1OP(ldw, reg, val,"#");

    cpu->regs[reg].val = val;
    ADVANCE_PC(2);
    DO_CYCLES(2);
    END_OPCODE();
}

DEF_INS(ldw_a) {
    uint8_t reg = (opcode & 0x00F0) >> 4;
    uint16_t val = cpu->sys->mem->ReadShort(cpu->regs[15].val + 2);
    LOG_INS_REG_1OP(ldw, reg, val, "$");
    val = cpu->sys->mem->ReadShort(val);
    cpu->regs[reg].val = val;
    ADVANCE_PC(2);
    DO_CYCLES(4);
    END_OPCODE();
}

DEF_INS(ldw_r) {
    uint8_t rega = (opcode & 0x00F0) >> 4;
    uint8_t regb = opcode & 0x000F;

    LOG_INS_2REG(ldw, regb, rega);

    cpu->regs[regb].val = cpu->regs[rega].val;

    ADVANCE_PC(1);
    DO_CYCLES(1);
    END_OPCODE();
}

DEF_INS(stw) {
    uint8_t reg = (opcode & 0x00F0) >> 4;
    uint16_t val = cpu->sys->mem->ReadShort(cpu->regs[15].val + 2);

    LOG_INS_REG_1OP(stw, reg, val,"#");

    cpu->sys->mem->WriteShort(val, cpu->regs[reg].val);
    ADVANCE_PC(2);
    DO_CYCLES(2);

    END_OPCODE();
}
