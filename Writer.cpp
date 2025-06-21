#include "Writer.h"
#include <iostream>

Writer::Writer() {
    main.open("main.txt");
    if (!main) {
        std::cerr << "Error opening main.txt" << std::endl;
    }
    x = 0;
}

Writer::~Writer() {
    main.close();
}

void Writer::FuncName(const Lexer &lexer) {
    if (!lexer.func_name.empty())
        main << lexer.func_type[x] << lexer.func_name[x];
    x++;
}


void Writer::FuncArgs(Lexer &lexer, int& tok, FILE* file) {
    if (tok == Lexer::tok_left_paren) {
        std::cout << "Token: " << tok << std::endl;
        lexer.id_str.clear();
        main << "(";
        int pass = 1;
        std::string str;
        while ((tok = lexer.GetToken(file)) != Lexer::tok_right_paren) {
            if (tok == Lexer::tok_identifier) {
                if (pass == 1) main << lexer.id_str;
                else main << " " << lexer.id_str;
            } else {
                switch (tok) {
                    case Lexer::tok_string: str = "string"; break;
                    case Lexer::tok_int: str = "int"; break;
                    case Lexer::tok_float: str = "float"; break;
                    case Lexer::tok_bool: str = "bool"; break;
                    case Lexer::tok_char: str = "char"; break;
                    case Lexer::tok_left_brace: str = "["; break;
                    case Lexer::tok_right_brace: str = "]"; break;
                    default: break;
                }
                if (pass == 1) main << str;
                else main << " " << str;
            }
            pass++;
        }
        main << ")" << "{" <<std::endl;
    }
}
