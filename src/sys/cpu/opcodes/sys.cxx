#include <cpu/interpreter.hpp>

/// Instruction: No-op
DEF_INS(nop) {
    LOG_INS(nop);
    USE_OPCODE;
    ADVANCE_PC(1);
    END_OPCODE();
}

DEF_INS(unknown) {
    LOG_INS(unknown);
    USE_OPCODE;
    cpu->Stop();
    cpu->sys->isRunning = false;
}

DEF_INS(hlt) {
    LOG_INS(hlt);
    USE_OPCODE;
    cpu->Stop();
    cpu->sys->isRunning = false;
    ADVANCE_PC(1);
    END_OPCODE();
}
