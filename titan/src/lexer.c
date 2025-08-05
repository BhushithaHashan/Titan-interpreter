#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "lexer.h"

void lexer_init(Lexer *lexer,char *src){
    lexer->src = src;
    lexer->pos = 0;
    lexer->current_pointed_char = src[0];
}
static void advance(Lexer *lexer){
    lexer->pos++;
    if (lexer->src[lexer->pos]!='\0')
    {
        lexer->current_pointed_char = lexer->src[lexer->pos];
        return;
    }
    lexer->current_pointed_char = '\0';
    return;
    
}
static void skip_white_spaces(Lexer *lexer){
    while (1)
    {
        switch (lexer->current_pointed_char)
        {
        case '\0':
            return;
        case ' ':
            advance(lexer);
            break;
        case '\t':
            advance(lexer);
            break;
        case '\n':
            advance(lexer);
            break;
        case '\r':
            advance(lexer);
            break;
        default:
            return;
        }
        
    }
    
}
Token lexer_next_token(Lexer *lexer);