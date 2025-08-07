#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include "memalloc.h"
#include "token.h"
#include <string.h>
#include <stdlib.h>

// int push_token(Token token,Token_Array *arr){
//     int arr_cap = arr->capasity;
//     int arr_cnt = arr->count;
//     if (arr_cap==arr_cnt)
//     {   
//         int size_of_new_arr = sizeof(Token)*arr_cap*2;
//         void *mem = memalloc(size_of_new_arr,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS);
//         if (mem==(void *)-1)
//         {
//             perror("mem alloc failed in token array!\n");
//             return -1;
//         }
//         memcpy(mem,arr->tokens,sizeof(Token)*arr_cap);
//         syscall(SYS_munmap,arr->tokens,arr_cap*sizeof(Token));
//         arr->tokens = mem;
//         arr->capasity = arr_cap*2;
//     }
//     arr->tokens[arr_cnt] = token;
//     arr_cnt++;
//     arr->count = arr_cnt;
//     return 1;
    
// }
int push_token(Token token,Token_List *list){
    void *new_token = memalloc(sizeof(Token),PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_PRIVATE);
        if (new_token==(void *)-1)
        {   
            perror("memalloc error at push token\n");
            exit(1);
        }
    token.next_token = NULL;
    *(Token *)new_token = token;
    if (list->head==NULL)
    { 
        list->head = new_token;
        list->count++;
        list->tail = new_token;
        return 1;
    }
    Token *current_pointed_token = list->tail;
    current_pointed_token->next_token = new_token;
    list->tail = new_token;
    list->count++;
    return 1;
}


