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
    for (size_t i = 0; i < count; i++)
    {
        int digit =numberstr[i]-48;
        number = number * 10 + digit;  
    }
    token.value = number;
    return token;
}
Token lexer_next_token(Lexer *lexer);

int main(){
    char *src = "1234";
    Lexer lexer;
    lexer_init(&lexer,src);
    Token token = read_number(&lexer);
    printf("lexeme:%s\tvalue:%d\n",token.lexeme,token.value);
}