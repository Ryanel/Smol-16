#pragma once

#define FLAG_NOARGS 0x1
#define FLAG_REG1 0x2
#define FLAG_REG2 0x4
#define FLAG_LITERAL 0x8
#define FLAG_ADDR 0x10
#define FLAG_COND 32
typedef struct {
    uint8_t opcode;
    std::string name;
    uint8_t flags;
} opcode_mapping_t;

extern std::vector<opcode_mapping_t> opcodes;
