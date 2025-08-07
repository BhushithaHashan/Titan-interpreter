#ifndef TITAN_TOKEN_H
#define TITAN_TOKEN_H

typedef struct Token Token;
typedef enum {
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_IDENTIFIER,

    TOKEN_LET,
    TOKEN_FUNCTION,
    TOKEN_RETURN,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_PRINT,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,

    TOKEN_EQUAL,     // =
    TOKEN_EQEQ,      // ==
    TOKEN_NEQ,       // !=
    TOKEN_LT,        // <
    TOKEN_LTEQ,      // <=
    TOKEN_GT,        // >
    TOKEN_GTEQ,      // >=

    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,

    TOKEN_EOF
} TokenType;

struct Token{
    TokenType type;
    char * lexeme;
    int size_lexeme;
    int value;
    int line_number;
    int col_num;
    Token *next_token;
};
typedef struct{
    Token *head;
    Token *tail;
    int count;
}Token_List;

int push_token(Token token,Token_List *list);
int token_list_init(Token_List *list);
#endif
