#include "Lexer.h"
#include <iostream>

int Lexer::GetToken(FILE* f) {
    while (isspace(last_char))
        last_char = fgetc(f);
    if (last_char == '/') {
        last_char = fgetc(f);
        if (last_char == '/') {
            do
                last_char = fgetc(f);
            while (last_char != EOF && last_char != '\n' && last_char != '\r');
            if (last_char != EOF)
                return GetToken(f);
        }
    }
    if (isalpha(last_char) || last_char == '_' || last_char == '.') {
        id_str = last_char; // Store the first character
        while (isalnum(last_char = fgetc(f)) || last_char == '.')
            id_str += last_char;
        if (id_str == "void") {
            last_char = fgetc(f);
            id_str = last_char;
            while (isalnum(last_char = fgetc(f)))
                id_str += last_char;
            func_name.push_back(id_str);
            func_type.emplace_back("void");
            return tok_function;
        }
        if (id_str == "String" || id_str == "string") {
            return tok_string;
        }else if (id_str == "int") {
            return tok_int;
        }else if (id_str == "float") {
            return tok_float;
        }else if (id_str == "char") {
            return tok_char;
        } else if (id_str == "bool") {
            return tok_bool;
        } else if (id_str == "null") {
            return tok_null;
        }else if (id_str == "true") {
            return tok_true;
        }
        else if (id_str == "false") {
            return tok_false;
        }
        else if (id_str == "return") {
            return tok_return;
        }
        return tok_identifier;
    }
    if (isdigit(last_char) || last_char == '.') {
        std::string NumStr; // Buffer for the number string
        do {
            NumStr += last_char;
            last_char = fgetc(f);
        } while (isdigit(last_char) || last_char == '.');

        num_val = strtod(NumStr.c_str(), nullptr);
        return tok_number;
    }
    switch (last_char) {
        case 40:
            last_char = fgetc(f);
            return tok_left_paren;
        case 41:
            last_char = fgetc(f);
            return tok_right_paren;
        case '{':
            last_char = fgetc(f);
            return tok_left_bracket;
        case '}':
            last_char = fgetc(f);
            return tok_right_bracket;
        case '[':
            last_char = fgetc(f);
            return tok_left_brace;
        case ']':
            last_char = fgetc(f);
            return tok_right_brace;
        case '"':
            last_char = fgetc(f);
            return tok_double_quote;
        case '\'':
            last_char = fgetc(f);
            return tok_single_quote;
        case ';':
            last_char = fgetc(f);
            return tok_semi_colon;
        default:
            break;
    }

    if (last_char == EOF)
        return tok_eof;

    // Otherwise, return the character as its ASCII value
    int ThisChar = last_char;
    last_char = fgetc(f);
    return ThisChar;
}
