#include <string.h>
#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "includes/file.hpp"
#include "includes/preprocess.hpp"
using namespace std;

static const string whitespaces = " ,";

bool CompareSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

void TrimRight (string& str, const string& trimChars = whitespaces) {
    string::size_type pos = str.find_last_not_of( trimChars);
    str.erase(pos + 1);
}

void TrimLeft (string& str, const string& trimChars = whitespaces) {
    string::size_type pos = str.find_first_not_of( trimChars );
    str.erase(0, pos);
}

/// Remove extra whitespaces
void PreprocessLine (string& str)
{
    TrimRight(str);
    TrimLeft(str);

    std::string::iterator new_end = std::unique(str.begin(), str.end(), CompareSpaces);
    str.erase(new_end, str.end());
    // Make everything lowercase
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    // Delete comments
    size_t nFPos = str.find_first_of(";");
    if(nFPos != std::string::npos) {
        for(unsigned int i = nFPos; i < str.length(); i++) {
            str[i] = 0;
        }
    }


    // Delete commas
    while (true) {
        nFPos = str.find_first_of(",");
        if(nFPos != std::string::npos) {
            str.erase(nFPos, 1);
        } else {
            break;
        }
    }

}
