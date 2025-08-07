#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char op;
    int val;
    int is_a_leaf;
    struct Node *left;
    struct Node *right;
} Node;
int op(Node *node){
    if (node==NULL)
    {
        exit(1);
    }
    if (node->is_a_leaf)
    {
        return node->val;
    }
    if (node->op=='+')
    {
        return op(node->left)+op(node->right);
        
    }
    if (node->op == '*')
    {
        return op(node->left) * op(node->right);
    }
    
}
int main() {
    // Leaf nodes
    Node *leaf1 = malloc(sizeof(Node));
    leaf1->is_a_leaf = 1;
    leaf1->val = 3;
    leaf1->left = NULL;
    leaf1->right = NULL;

    Node *leaf2 = malloc(sizeof(Node));
    leaf2->is_a_leaf = 1;
    leaf2->val = 4;
    leaf2->left = NULL;
    leaf2->right = NULL;

    // Operator node
    Node *plus = malloc(sizeof(Node));
    plus->is_a_leaf = 0;
    plus->op = '*';
    plus->left = leaf1;
    plus->right = leaf2;

    // Now `plus` is the root of the tree for "3 + 4"

    printf("Root op: %c, left: %d, right: %d\n",
           plus->op, plus->left->val, plus->right->val);
    
    printf("%d\n",op(plus));
    // Free memory
    free(leaf1);
    free(leaf2);
    free(plus);
}