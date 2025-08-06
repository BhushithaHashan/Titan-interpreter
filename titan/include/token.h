#ifndef TITAN_TOKEN_H
#define TITAN_TOKEN_H
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
typedef struct{
    Token *tokens;
    int count;
    int capasity;
}Token_Array;
typedef struct{
    TokenType type;
    char * lexeme;
    int size_lexeme;
    int value;
    int line_number;
    int col_num;
}Token;

#endif
