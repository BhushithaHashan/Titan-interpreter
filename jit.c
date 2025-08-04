#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stddef.h>
#include <string.h>
#include <sys/syscall.h>
#include <limits.h>
struct Node{
    int val;
    struct Node *left;
    struct Node *right;
};
struct Node* create_node(int val){
    void *mem = (void*)syscall(SYS_mmap,NULL,sizeof(struct Node),PROT_READ|PROT_WRITE,MAP_ANON|MAP_PRIVATE,-1,0);
    if (mem = (void *)-1)  
    {
        return NULL;
    }
    struct Node *node = mem;
    node->val = val;
    node->left = node->right = NULL;
}
int sum(struct Node *n){
    if (n==NULL)return 0;
    return n->val+sum(n->left)+sum(n->right);
    
}
int find_max(struct Node *n){
    if (n==NULL)
    {
        return;
    }
    int max_lft = find_max(n->left);
    int max_right  = find_max(n->right);
    int max= (n->val>max_lft)?n->val:(max_lft>max_right)?max_lft:max_right;
    return max;
}
unsigned char code[] = { 0x8d, 0x04, 0x37, 0xc3 };
int fac(int n){
    if (n<0)
    {
        return -1;
    }
    
    if (n==1 || n==0)
    {
        return 1;
    }
    return n*fac(n-1);
}
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

    printf("%d",fac(5));
    if (5>NULL) 
    {
        printf("hello\n");
    }
    
    

}

