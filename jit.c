#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stddef.h>
#include <sys/syscall.h>

unsigned char code[] = { 0x8d, 0x04, 0x37, 0xc3 };
int main(){
    void *mem = syscall(SYS_mmap,NULL,sizeof(char)*4,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
    
}

