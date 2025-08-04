#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stddef.h>
#include <string.h>
#include <sys/syscall.h>

unsigned char code[] = { 0x8d, 0x04, 0x37, 0xc3 };
int main(){
    void *mem = (void *)syscall(SYS_mmap,NULL,sizeof(char)*4,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
    if (mem == (void *)-1)
    {
        perror("mem alloc failed\n");
        return -1;
    }
    memcpy(mem,code,sizeof(char)*4);
    int stat = syscall(SYS_mprotect,mem,sizeof(char)*4,PROT_READ|PROT_EXEC);
    if (stat!=-1)
    {
        printf("permission on mem changed\n");
    }
    int (*add)(int,int) = mem;
    int val = add(5,5);
    printf("%d\n",val);
    

}

