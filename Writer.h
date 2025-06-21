#pragma once
#include <fstream>
#include "Lexer.h"
class Writer {
    std::ofstream main;
public:
    Writer();
    ~Writer();
    int x;
    void FuncName(const Lexer& lexer);
    void FuncArgs(Lexer& lexer, int& tok, FILE* file);
};

