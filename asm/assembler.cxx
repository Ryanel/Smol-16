#include "includes/file.hpp"
#include "includes/assembler.hpp"
#include <string.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <spdlog/spdlog.h>

using namespace std;
static std::shared_ptr<spdlog::logger> _log;

uint32_t address_counter = 0;

std::vector<uint8_t> code;

int CompileInstruction(opcode_mapping_t * ins, token_t * token) {
    // Lets start processing the instruction body
    int instruction_length = 2;
    if(ins->flags & FLAG_LITERAL || ins->flags & FLAG_ADDR) {
        instruction_length = 4;
    }

    // Now generate the byte code.
    if (instruction_length == 2) {
        uint16_t bytecode = ins->opcode << 8;
        if(ins->flags & FLAG_REG1) {
            uint16_t reg = (token->rega & 0xF) << 4;
            bytecode = bytecode | reg;
        }
        if(ins->flags & FLAG_REG2) {
            uint16_t reg = (token->regb & 0xF);
            bytecode = bytecode | (reg & 0xF);
        }
        if(ins->flags & FLAG_COND) {
            uint16_t reg = (token->cond & 0xF);
            bytecode = bytecode | (reg & 0xF);
        }
        _log->debug("0x{0:04X}: {1:>5s} 0x{2:04X}", address_counter ,token->str, bytecode);
        code.push_back((uint8_t)(bytecode >> 8));
        code.push_back((uint8_t)(bytecode & 0xFF));

    } else {
        uint32_t bytecode = ins->opcode << 24;
        if(ins->flags & FLAG_REG1) {
            uint32_t reg = (token->rega & 0xF) << 20;
            bytecode = bytecode | reg;
        }
        if(ins->flags & FLAG_REG2) {
            uint32_t reg = (token->regb & 0xF) << 16;
            bytecode = bytecode | (reg & 0xF);
        }
        if(ins->flags & FLAG_COND) {
            uint32_t reg = (token->cond & 0xF) << 16;
            bytecode = bytecode | reg;
        }
        if(ins->flags & FLAG_LITERAL) {
            uint32_t val = (token->lit & 0xFFFF);
            bytecode = bytecode | val;
        }
        if(ins->flags & FLAG_ADDR) {
            uint32_t val = (token->addr & 0xFFFF);
            bytecode = bytecode | val;
        }

        _log->debug("0x{0:04X}: {1:>5s} 0x{2:08X}", address_counter ,token->str, bytecode);
        code.push_back((uint8_t)(bytecode >> 24));
        code.push_back((uint8_t)(bytecode >> 16));
        code.push_back((uint8_t)(bytecode >> 8));
        code.push_back((uint8_t)(bytecode & 0xFF));

    }
    return instruction_length;
}

void Assemble_Step1(AsmFile * file) {
    _log = spdlog::stdout_color_mt("asm");
    for(size_t i = 0; i < file->tokens.size(); i++) {
        token_t * token = file->tokens[i];
        symbol_t * sym;
        opcode_mapping_t * ins;

        switch (token->type) {
            case TOKEN_INSTRUCTION_BODY:
                ins = nullptr;
                for(size_t j = 0; j < opcodes.size(); j++) {
                    opcode_mapping_t ins_in = opcodes[j];
                    if(ins_in.name == token->str) {
                        // Potential match!
                        if((bool)(ins_in.flags & FLAG_REG1)    != (token->rega != TOKEN_PLACEHOLDER)) {continue;}
                        if((bool)(ins_in.flags & FLAG_REG2)    != (token->regb != TOKEN_PLACEHOLDER)) {continue;}
                        if((bool)(ins_in.flags & FLAG_ADDR)    != (token->addr != TOKEN_PLACEHOLDER)) {continue;}
                        if((bool)(ins_in.flags & FLAG_LITERAL) != (token->lit  != TOKEN_PLACEHOLDER)) {continue;}

                        ins = &opcodes[j];
                        break;
                    }
                }
                if (ins == nullptr) {
                    _log->error("Instruction {0:s} is not valid", token->str); exit(1);
                }
                address_counter += CompileInstruction(ins, token);
                break;
            case TOKEN_SYM_DEF:
                sym = nullptr;
                // Find symbol and assign address
                for(size_t j = 0; j < file->symbols.size(); j++) {
                    if(file->symbols[j]->str == token->str) {
                        sym = file->symbols[j];
                        sym->populated = true;
                        sym->offset = address_counter;
                        //_log->debug("Symbol {0:s} assigned address 0x{1:04x}", sym->str, sym->offset);
                    }
                }
                if (sym == nullptr) {
                    _log->error("Unable to assign address to symbol {0:s}", token->str);  exit(1);
                }

                break;
            default:
                _log->error("Unable to process token {0:s}", token->str);  exit(1);
                break;
        }
    }

    // Write file
    ofstream fout("code.bin", ios::out | ios::binary);
    fout.write((char*)&code[0], code.size() * sizeof(uint16_t));
    fout.close();
}
