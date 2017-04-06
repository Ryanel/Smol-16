#include <cpu/interpreter.hpp>

DEF_INS(jp) {
    LOG_INS(jp);
    bool shouldJump = false;

    // What kind of jump are we doing?
    uint8_t opcode_flags = opcode & 0x000F;
    switch (opcode_flags) {
        case OPCODE_FLAG_AL:
            shouldJump = true;
            break;
        default:
            break;
    }
    if(shouldJump) {
        cpu->regs[15].val = cpu->sys->mem->ReadShort(cpu->regs[15].val + 2);
    }

    END_OPCODE();
}
