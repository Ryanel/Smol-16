#pragma once
#include <cpu/cpu.hpp>
#include <system.hpp>

#define ADVANCE_PC(x) cpu->regs[15].val += x * 2
#define END_OPCODE() cpu->instructions_total++;  cpu->cycles += 1
#define CALL_INS(x) CPU_OP_##x(this, this->sys->mem->ReadShort(this->regs[15].val))
#define DEF_INS(x) void CPU_OP_##x (CCpu * cpu, uint16_t opcode)
#define PRO_INS(x) void CPU_OP_##x (CCpu * cpu, uint16_t opcode)
#define DO_CYCLES(x) cpu->cycles += x;
#define USE_OPCODE opcode = opcode;

#define LOG_INSTRUCTION(x) cpu->_log->debug("0x{0:04X}: {1}", cpu->regs[15].val,#x)
#define LOG_INSTRUCTION_OP1(x, y) cpu->_log->debug("0x{0:04X}: {1} 0x{2:04}", cpu->regs[15].val,#x, y)
#define LOG_INSTRUCTION_REG_OP1(x,r,y)  cpu->_log->debug("0x{0:04X}: {1:s} r{2:d}, 0x{3:04x}", cpu->regs[15].val,#x, r, y)

#define OPCODE_FLAG_EQ 0
#define OPCODE_FLAG_NE 1
#define OPCODE_FLAG_HS 2
#define OPCODE_FLAG_LO 3
#define OPCODE_FLAG_MI 4
#define OPCODE_FLAG_PL 5
#define OPCODE_FLAG_VS 6
#define OPCODE_FLAG_VC 7
#define OPCODE_FLAG_HI 8
#define OPCODE_FLAG_LS 9
#define OPCODE_FLAG_GE 10
#define OPCODE_FLAG_LT 11
#define OPCODE_FLAG_GT 12
#define OPCODE_FLAG_LE 13
#define OPCODE_FLAG_AL 14
#define OPCODE_FLAG_RS 15

#define OPCODE_FLAG_ADDRESS 0
#define OPCODE_FLAG_LITERAL 1

PRO_INS(unknown);
PRO_INS(nop);
PRO_INS(hlt);
PRO_INS(jp);
