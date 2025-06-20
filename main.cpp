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
    while ((tok = lexer.GetToken(file)) != lexer.tok_eof)
    {
        writer.FuncArgs(lexer,tok,file);
        if (tok == lexer.tok_right_paren) {
            std::cout << "Right" << "\n";
        }
        if (tok == lexer.tok_number)
        {
           printf("Number: %f\n", lexer.num_val);
        }
        else if (tok == lexer.tok_identifier)
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