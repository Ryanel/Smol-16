#pragma once
#include <string>
#include <vector>

typedef uint16_t address_t;
typedef struct {
    address_t offset;
    std::string str;
    bool populated = false;
} symbol_t;

enum TokenType {
    TOKEN_INSTRUCTION_BODY,
    TOKEN_SYM_DEF,
    TOKEN_SYM_USE,
    TOKEN_SET_ORIGIN,
    TOKEN_DATA_WORD,
    TOKEN_DATA_BYTE,
};

#define FSM_INS 0x0
#define FSM_REG 0x1
#define FSM_LIT 0x2
#define FSM_ADDR 0x4
#define FSM_DAT 0x8
#define FSM_COND 0x10

#define TOKEN_PLACEHOLDER 0x10000

typedef struct {
    TokenType type;
    std::string str;
    int rega = TOKEN_PLACEHOLDER;
    int regb = TOKEN_PLACEHOLDER;
    int lit  = TOKEN_PLACEHOLDER;
    int addr = TOKEN_PLACEHOLDER;
    int cond = 0xE; // Always by default
} token_t;

typedef struct {
    std::string str;
    int next;
    int after;
} fsm_type_t;

class AsmFile {
private:
    std::string location;
public:
    AsmFile(std::string loc);
    std::vector<std::string> lines;
    std::vector<symbol_t*> symbols;
    std::vector<token_t*> tokens;

    //FSM state here
    int fsm_expected = FSM_INS;
    int fsm_nextexpected = 0; // Not set unless explicitaly needed

    void LoadAndSanitize();
    void Tokenize();
};

#define ADVANCE_FSM \
    fsm_expected = FSM_INS; \
    if(fsm_nextexpected != 0) { \
        fsm_expected = fsm_nextexpected; \
        fsm_nextexpected = 0; \
    }

#define PUSHTOKEN(t, str) token_t * _tok = new token_t; \
    _tok->type = (t); \
    _tok->str = (str); \
    tokens.push_back(_tok);


extern std::vector<fsm_type_t> valid_instructions;
