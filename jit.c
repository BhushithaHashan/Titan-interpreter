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
    int op;
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
        return INT_MIN;
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
int add(int a,int b){
    return a+b;
}
static int (*op[])(int,int)={add};
void traverse(struct Node *n,int *ptr){
    if (n->right==NULL)
    {
        return;
    }
    if (n->op==0)
    {
        traverse(n->right,ptr);
    }
    if (n->op==1)
    {
        int result = op[0](n->left->val,n->right->val);
        *ptr = result;
        return;
    }
    
    
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

    printf("%d\n",fac(5));
    
    struct Node op,left,right;
    op.op = 1;
    left.val = 5;
    right.val = 10;
    left.op = 0;
    right.op = 0;
    op.right = &right;
    op.left = &left;
    left.right= &op;
    left.left = NULL;
    right.left = &op;
    right.right = NULL;
    int result = 0;
    traverse(&left,&result);
    printf("%d\n",result);

}

