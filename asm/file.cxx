#include <string.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <spdlog/spdlog.h>

#include "includes/preprocess.hpp"
#include "includes/file.hpp"

static std::shared_ptr<spdlog::logger> _log;

using namespace std;

AsmFile::AsmFile(std::string loc) {
    this->location = loc;
    _log = spdlog::stdout_color_mt("tokenizer");
    LoadAndSanitize();
}

void AsmFile::LoadAndSanitize() {
    std::ifstream fp(location.c_str(), std::ios_base::in);
    std::string tmp;
    tmp.resize(256);
    while (fp.good()) {
        memset(&tmp[0], 0, 256);
        fp.getline(&tmp[0], 256);
        PreprocessLine(tmp);

        std::string news(tmp.c_str());
        if (news.length() > 0) {
            lines.push_back(news);
        }
    }
    fp.close();
}


vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

// LDW LIT LABEL:START XOR

void AsmFile::Tokenize() {
    std::string valid_literal_prefixes = "#0123456789";

    for (unsigned i = 0; i < lines.size(); i++) {
        std::string str = lines[i];
        // Pre-take any symbols so the tokenizer doesn't have to worry
        {
            size_t nFPos = str.find_first_of(":");
            if(nFPos != std::string::npos) {
                // Symbol found!
                for(unsigned int j = nFPos; j < str.length(); j++) {
                    str[j] = 0;
                }
                symbol_t * sym = new symbol_t; sym->str = str;
                symbols.push_back(sym);
                PUSHTOKEN(TOKEN_SYM_DEF, str);
                continue;
            }
        }

        // Tokenize line, turn it into a set of substrings
        token_t * tok = new token_t;
        bool emittingToken = false;
        std::vector<std::string> cur_line = split(str, " ");

        // Core tokenizer
        for(size_t j = 0 ; j < cur_line.size(); j++) {
            bool reg = false;
            bool lit = false;
            bool addr = false;
            bool isHex = false;
            bool cond = false;
            // Handle instructions
            if(fsm_expected == FSM_INS) {
                // Reset FSM state
                fsm_expected = FSM_INS;
                fsm_nextexpected = 0;

                bool found = false;
                fsm_type_t ins;
                for(size_t k = 0 ; k < valid_instructions.size(); k++) {
                    ins = valid_instructions[k];
                    if(ins.str == cur_line[j]) {
                        found = true;
                        break;
                    }
                }
                if(!found) {
                    printf("Line %d, invalid instruction \"%s\"\n", i, cur_line[j].c_str());
                    break;
                }
                tok->type = TOKEN_INSTRUCTION_BODY;
                tok->str = cur_line[j];
                emittingToken = true;
                if(ins.after != 0) {
                    fsm_expected = ins.next;
                    fsm_nextexpected = ins.after;
                }

                else {
                    fsm_expected = ins.next;
                }
                continue;
            }

            // Determine type now, because we know it's not an instruction
            reg  = cur_line[j][0] == 'r'; // Register
            addr = cur_line[j][0] == '$'; // Address
            cond = cur_line[j][0] == '%'; // Conditional
            for(size_t k = 0; k < valid_literal_prefixes.length(); k++) { // Literal
                if(cur_line[j][0] == valid_literal_prefixes[k]) {
                    lit = true;
                    isHex = k == 0;
                    break;
                }
            }
            if(!(lit && !isHex)) {
                cur_line[j].erase(0, 1); // Erase prefix character
            }

            // Now compare against the other kinds of tokens
            if((fsm_expected & FSM_REG) && reg) {
                if (tok->rega == TOKEN_PLACEHOLDER) {
                    tok->rega = strtol(cur_line[j].c_str(),0,10);
                } else {
                    tok->regb = strtol(cur_line[j].c_str(),0,10);
                }
                ADVANCE_FSM;
            } else if((fsm_expected & FSM_LIT) && lit) {
                if (isHex) {
                    tok->lit = strtol(cur_line[j].c_str(),0,16);
                } else {
                    tok->lit = strtol(cur_line[j].c_str(),0,10);
                }
                ADVANCE_FSM;
            } else if((fsm_expected & FSM_ADDR) && addr) {
                tok->addr = strtol(cur_line[j].c_str(),0,16);
                ADVANCE_FSM;
            } else if((fsm_expected & FSM_COND) && cond) {
                if(cur_line[j] == "eq") {
                    tok->cond = 0x0;
                }
                else if(cur_line[j] == "ne") {
                    tok->cond = 0x1;
                }
                else if(cur_line[j] == "hs") {
                    tok->cond = 0x2;
                }
                else if(cur_line[j] == "lo") {
                    tok->cond = 0x3;
                }
                else if(cur_line[j] == "mi") {
                    tok->cond = 0x4;
                }
                else if(cur_line[j] == "pl") {
                    tok->cond = 0x5;
                }
                else if(cur_line[j] == "vs") {
                    tok->cond = 0x6;
                }
                else if(cur_line[j] == "vc") {
                    tok->cond = 0x7;
                }
                else if(cur_line[j] == "hi") {
                    tok->cond = 0x8;
                }
                else if(cur_line[j] == "ls") {
                    tok->cond = 0x9;
                }
                else if(cur_line[j] == "ge") {
                    tok->cond = 0xA;
                }
                else if(cur_line[j] == "lt") {
                    tok->cond = 0xB;
                }
                else if(cur_line[j] == "gt") {
                    tok->cond = 0xC;
                }
                else if(cur_line[j] == "le") {
                    tok->cond = 0xD;
                }
                else if(cur_line[j] == "al") {
                    tok->cond = 0xE;
                }
                else if(cur_line[j] == "rs") {
                    tok->cond = 0xF;
                }
                else {
                    printf("Invalid conditional!\n");
                }
                ADVANCE_FSM;
            } else {
                printf("Invalid argument!\n");
            }
        }

        if (emittingToken) {
            tokens.push_back(tok);
        }
    }
}
