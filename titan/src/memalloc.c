#define _GNU_SOURCE
#include "memalloc.h"
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <stdio.h>

void *memalloc(int size,int permission,int behavior){
    void *mem =(void *)syscall(SYS_mmap,NULL,size,permission,behavior,-1,0);
    if (mem==(void *)-1)
    {
        perror("mem alloc failed\n");
    }
    return mem;
    
}