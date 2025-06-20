#include "Writer.h"
#include <iostream>

Writer::Writer() {
    main.open("main.txt");
    if (!main) {
        std::cerr << "Error opening main.txt" << std::endl;
    }
}

Writer::~Writer() {
    main.close();
}

void Writer::FuncArgs(Lexer &lexer, int& tok, FILE* file) {
    if (tok == lexer.tok_left_paren) {
        std::cout << "Token: " << tok << std::endl;
        lexer.id_str.clear();
        main << "(";
        int pass = 1;
        std::string str;
        while ((tok = lexer.GetToken(file)) != lexer.tok_right_paren) {
            if (tok == lexer.tok_identifier) {
                if (pass == 1) main << lexer.id_str;
                else main << " " << lexer.id_str;
            } else {
                switch (tok) {
                    case lexer.tok_string: str = "string"; break;
                    case lexer.tok_int: str = "int"; break;
                    case lexer.tok_float: str = "float"; break;
                    case lexer.tok_bool: str = "bool"; break;
                    case lexer.tok_char: str = "char"; break;
                    default: break;
                }
                if (pass == 1) main << str;
                else main << " " << tok;
            }
            pass++;
        }
        main << ")" << "{" <<std::endl;
        // for (int i = 0; i < lexer.func_args.size(); i++) {
        //     main << "(" << lexer.func_args[i] << ")" << "{" <<std::endl;
        // }
        for (auto &x : lexer.func_args) {
            std::cout << "Args: " << x << std::endl;
        }
       lexer.func_args.clear();
    }
}
