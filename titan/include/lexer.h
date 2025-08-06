#ifndef TITAN_LEXER_H
#define TITAN_LEXER_H
#include "token.h"
typedef struct{
    const char *src;
    int pos;
    char current_pointed_char;
    int line_number;
    int col_num;
}Lexer;
void lexer_init(Lexer *lexer,char *src);
Token lexer_next_token(Lexer *lexer);
#endif 