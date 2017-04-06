#include "includes/file.hpp"
#include "includes/assembler.hpp"

// Recognized instructions
std::vector<fsm_type_t> valid_instructions = {
    {"dw" , FSM_LIT,0},
    {"hlt", FSM_INS,0},
    {"nop", FSM_INS,0},
    {"ldw", FSM_REG,  FSM_REG | FSM_LIT | FSM_ADDR},
    {"str", FSM_ADDR, FSM_REG },
    {"xor", FSM_REG,  FSM_REG | FSM_LIT},
    {"or" , FSM_REG,  FSM_REG | FSM_LIT},
    {"and", FSM_REG,  FSM_REG | FSM_LIT},
    {"jp" , FSM_ADDR | FSM_COND, FSM_REG | FSM_ADDR | FSM_INS},
    {"shr", FSM_REG, FSM_LIT | FSM_REG},
    {"shl", FSM_REG, FSM_LIT | FSM_REG},
};

std::vector<opcode_mapping_t> opcodes = {
    {0x00,"nop", FLAG_NOARGS},

    {0x01,"ldw", FLAG_REG1 | FLAG_LITERAL},
    {0x03,"ldw", FLAG_REG1 | FLAG_ADDR},
    {0x05,"ldw", FLAG_REG1 | FLAG_REG2},

    {0x20,"jp",  FLAG_COND | FLAG_ADDR},
    {0x21,"jp",  FLAG_COND | FLAG_REG1},

    {0x74,"shr", FLAG_REG1 | FLAG_LITERAL},
    {0x75,"shr", FLAG_REG1 | FLAG_REG2},
    {0x76,"shl", FLAG_REG1 | FLAG_LITERAL},
    {0x77,"shl", FLAG_REG1 | FLAG_REG2},

    {0x82,"and", FLAG_REG1 | FLAG_LITERAL},
    {0x83,"and", FLAG_REG1 | FLAG_REG2},
    {0x84,"xor", FLAG_REG1 | FLAG_LITERAL},
    {0x85,"xor", FLAG_REG1 | FLAG_REG2},
    {0x86,"or" , FLAG_REG1 | FLAG_LITERAL},
    {0x87,"or" , FLAG_REG1 | FLAG_REG2},

    {0xFF,"hlt", FLAG_NOARGS},
};
