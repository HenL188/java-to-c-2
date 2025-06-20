#pragma once
#include <fstream>
#include "Lexer.h"
class Writer {
    std::ofstream main;
public:
    Writer();
    ~Writer();
    void FuncArgs(Lexer& lexer, int& tok, FILE* file);
};

