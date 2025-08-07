#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include "memalloc.h"
#include "token.h"

int push_token(Token token,Token_Array *arr){
    int arr_cap = arr->capasity;
    int arr_cnt = arr->count;
    if (arr_cap==arr_cnt)
    {
        void *mem = memalloc(sizeof(Token)*arr_cap*2,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS);
        if (mem==(void *)-1)
        {
            perror("mem alloc failed in token array!\n");
            exit(1);
        }
        arr->tokens = mem;
        arr->capasity = arr_cap*2;
    }
    arr->tokens[arr_cnt] = token;
    arr_cnt++;
    arr->count = arr_cnt;
    
}


