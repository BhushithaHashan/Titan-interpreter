#define _GNU_SOURCE
#include <stdio.h>
#include <ctype.h>
#include "token.h"
#include "lexer.h"
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include "memalloc.h"

void lexer_init(Lexer *lexer,char *src){
    lexer->src = src;
    lexer->pos = 0;
    lexer->current_pointed_char = src[0];
    lexer->line_number = 1;
    lexer->col_num = 1;
}
static void advance(Lexer *lexer){
    if (lexer->current_pointed_char == '\n') {
        lexer->line_number++;
        lexer->col_num = 1;
    } else {
        lexer->col_num++;
    }

    lexer->pos++;

    if (lexer->src[lexer->pos] != '\0')
        lexer->current_pointed_char = lexer->src[lexer->pos];
    else
        lexer->current_pointed_char = '\0';
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
static char peek(Lexer *lexer){
    if (lexer->src[lexer->pos+1]=='\0')
    {
        return '\0';
    }
    return lexer->src[lexer->pos+1];

}
static Token read_number(Lexer *lexer){
    int number = 0;
    Token token;
    token.type = TOKEN_NUMBER;
    token.line_number = lexer->line_number;
    token.col_num = lexer->col_num;
    const char *start = lexer->src+lexer->pos;
    char *numberstr;
    int count = 0;
    while (1)
    {
        if (isdigit(lexer->src[lexer->pos]))
        {
            count++;
            advance(lexer);
        }else{     
            break;
        } 
    }
    void *mem =(void *)syscall(SYS_mmap,NULL,sizeof(char)*count+1,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
    if (mem== (void *)-1)
    {   
        perror("mmap failed\n");
        exit(1);
    }
    numberstr = mem;
    memcpy(numberstr,start,count);
    numberstr[count] = '\0';
    token.lexeme = numberstr;
    token.size_lexeme =count+1;
    for (size_t i = 0; i < count; i++)
    {
        int digit =numberstr[i]-48;
        number = number * 10 + digit;  
    }
    token.value = number;
    return token;
}
static Token read_identifier(Lexer *lexer) {
    Token token;
    token.line_number = lexer->line_number;
    token.col_num = lexer->col_num;
    const char *start = lexer->src + lexer->pos;
    int len = 0;

    while (isalnum(lexer->current_pointed_char) || lexer->current_pointed_char == '_') {
        len++;
        advance(lexer);
    }

    void *mem = (void *)syscall(SYS_mmap, NULL, sizeof(char) * (len + 1),
                                PROT_READ | PROT_WRITE,
                                MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (mem == (void *)-1) {
        perror("mmap error\n");
        exit(1);
    }

    char *identifier = mem;
    memcpy(identifier, start, len);
    token.lexeme = identifier;
    token.size_lexeme = sizeof(char) * (len + 1);
    identifier[len] = '\0';

    // Quick first-letter dispatch
    switch (identifier[0]) {
        case 'l':
            if (strcmp(identifier, "let") == 0) {
                token.type = TOKEN_LET;
                return token;
            }
            break;
        case 'i':
            if (strcmp(identifier, "if") == 0) {
                token.type = TOKEN_IF;
                return token;
            }
            break;
        case 'e':
            if (strcmp(identifier, "else") == 0) {
                token.type = TOKEN_ELSE;
                return token;
            }
            break;
        case 'w':
            if (strcmp(identifier, "while") == 0) {
                token.type = TOKEN_WHILE;
                return token;
            }
            break;
        case 'f':
            if (strcmp(identifier, "function") == 0) {
                token.type = TOKEN_FUNCTION;
                return token;
            }
            break;
        case 'r':
            if (strcmp(identifier, "return") == 0) {
                token.type = TOKEN_RETURN;
                return token;
            }
            break;
        case 'p':
            if (strcmp(identifier, "print") == 0) {
                token.type = TOKEN_PRINT;
                return token;
            }
            break;
    }

    // If none of the keywords matched, it’s a normal identifier
    token.type = TOKEN_IDENTIFIER;
    return token;
}
static Token read_string(Lexer *lexer){
    advance(lexer);
    Token token;
    token.line_number = lexer->line_number;
    token.col_num = lexer->col_num;
    const char *start = lexer->src+lexer->pos;
    int str_len = 0;
    while (lexer->current_pointed_char!='"' && lexer->current_pointed_char!='\0')
    {
        str_len++;
        advance(lexer);
    }
    advance(lexer);
    void *mem = memalloc(str_len+1,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS);
    if (mem==(void *)-1)
    {
        exit(1);
    }
    char *string_val = mem;
    memcpy(string_val,start,str_len);
    string_val[str_len] = '\0';
    printf("%s\n",string_val);
    token.type = TOKEN_STRING;
    token.lexeme = string_val;
    token.size_lexeme = str_len+1;
    return token;

}
Token lexer_next_token(Lexer *lexer){
    skip_white_spaces(lexer);

    if (isdigit(lexer->current_pointed_char))
        return read_number(lexer);

    if (isalnum(lexer->current_pointed_char) || lexer->current_pointed_char == '_')
        return read_identifier(lexer);

    if (lexer->current_pointed_char == '"')
        return read_string(lexer);

    Token token;
    token.col_num = lexer->col_num;
    token.line_number = lexer->line_number;
    token.lexeme = NULL;
    token.size_lexeme = 0;
    token.value = 0;

    // =
    if (lexer->current_pointed_char == '=') {
        if (peek(lexer) == '=') {
            token.type = TOKEN_EQEQ;
            advance(lexer);
            advance(lexer);
            return token;
        }
        token.type = TOKEN_EQUAL;
        advance(lexer);
        return token;
    }

    // !
    if (lexer->current_pointed_char == '!') {
        if (peek(lexer) == '=') {
            token.type = TOKEN_NEQ;
            advance(lexer);
            advance(lexer);
            return token;
        }
        printf("Unexpected character ! at %d:%d\n", lexer->line_number, lexer->col_num);
        exit(1);
    }

    // <
    if (lexer->current_pointed_char == '<') {
        if (peek(lexer) == '=') {
            token.type = TOKEN_LTEQ;
            advance(lexer);
            advance(lexer);
            return token;
        }
        token.type = TOKEN_LT;
        advance(lexer);
        return token;
    }

    // >
    if (lexer->current_pointed_char == '>') {
        if (peek(lexer) == '=') {
            token.type = TOKEN_GTEQ;
            advance(lexer);
            advance(lexer);
            return token;
        }
        token.type = TOKEN_GT;
        advance(lexer);
        return token;
    }

    // Single character tokens
    switch (lexer->current_pointed_char) {
        case '+':
            token.type = TOKEN_PLUS;
            advance(lexer);
            return token;

        case '-':
            token.type = TOKEN_MINUS;
            advance(lexer);
            return token;

        case '*':
            token.type = TOKEN_STAR;
            advance(lexer);
            return token;

        case '/':
            token.type = TOKEN_SLASH;
            advance(lexer);
            return token;

        case '(':
            token.type = TOKEN_LPAREN;
            advance(lexer);
            return token;

        case ')':
            token.type = TOKEN_RPAREN;
            advance(lexer);
            return token;

        case '{':
            token.type = TOKEN_LBRACE;
            advance(lexer);
            return token;

        case '}':
            token.type = TOKEN_RBRACE;
            advance(lexer);
            return token;

        case ';':
            token.type = TOKEN_SEMICOLON;
            advance(lexer);
            return token;

        case ',':
            token.type = TOKEN_COMMA;
            advance(lexer);
            return token;

        case '\0':
            token.type = TOKEN_EOF;
            return token;
    }

    printf("Unknown character: %c at %d:%d\n",
           lexer->current_pointed_char,
           lexer->line_number,
           lexer->col_num);
    exit(1);
}

int main() {
    char *src =
        "let x = 10;\n"
        "if (x >= 5) {\n"
        "    print(\"hello\");\n"
        "}\n";

    Lexer lexer;
    lexer_init(&lexer, src);

    while (1) {
        Token t = lexer_next_token(&lexer);

        printf("Token type: %d", t.type);

        if (t.lexeme != NULL)
            printf(" | lexeme: %s", t.lexeme);

        if (t.type == TOKEN_NUMBER)
            printf(" | value: %d", t.value);

        printf(" | line: %d col: %d\n", t.line_number, t.col_num);

        if (t.type == TOKEN_EOF)
            break;
    }

    return 0;
}