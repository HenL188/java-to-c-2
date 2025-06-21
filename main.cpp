#include <iostream>
#include "Lexer.h"
#include <cstdio>
#include "Writer.h"

int main()
{
    Lexer lexer;
    FILE *file = fopen("main.java", "r");
    if (file == nullptr)
    {
        std::cerr << "Failed to open file" << std::endl;
    }
    int tok;
    Writer writer;
    while ((tok = lexer.GetToken(file)) != Lexer::tok_eof)
    {
        if (tok == Lexer::tok_function)
            writer.FuncName(lexer);
        writer.FuncArgs(lexer, tok, file);
        if (tok == Lexer::tok_number)
        {
            printf("Number: %f\n", lexer.num_val);
        }
        else if (tok == Lexer::tok_identifier)
        {
            std::cout << "ID: " << lexer.id_str << std::endl;
        }
        else
        {
            std::cout << "Token: " << tok << std::endl;
        }
    }
    return 0;
}