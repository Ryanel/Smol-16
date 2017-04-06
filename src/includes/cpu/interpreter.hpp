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

#define LOG_INS(op) cpu->_log->debug("{0:04X}: {1}", cpu->regs[15].val, #op)
#define LOG_INS_1OP(op, val, type) cpu->_log->debug("{0:04X}: {1:s} {2:s}{3:04x}", cpu->regs[15].val,#op,#val,#type)
#define LOG_INS_REG_1OP(op, reg, val, type) cpu->_log->debug("{0:04X}: {1:s} r{2:<2d}, {4:s}{3:04x}", cpu->regs[15].val, #op,reg,val,type)
#define LOG_INS_2REG(op, reg1, reg2) cpu->_log->debug("{0:04X}: {1:s} r{2:<2d}, r{3:<2d}", cpu->regs[15].val, #op,reg1,reg2)


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
