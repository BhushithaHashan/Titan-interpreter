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
    // Leaf 3
    Node *leaf1 = malloc(sizeof(Node));
    leaf1->is_a_leaf = 1;
    leaf1->val = 3;
    leaf1->left = NULL;
    leaf1->right = NULL;

    // Leaf 4
    Node *leaf2 = malloc(sizeof(Node));
    leaf2->is_a_leaf = 1;
    leaf2->val = 4;
    leaf2->left = NULL;
    leaf2->right = NULL;

    // Leaf 5
    Node *leaf3 = malloc(sizeof(Node));
    leaf3->is_a_leaf = 1;
    leaf3->val = 5;
    leaf3->left = NULL;
    leaf3->right = NULL;

    // Multiply node (4 * 5)
    Node *mul = malloc(sizeof(Node));
    mul->is_a_leaf = 0;
    mul->op = '*';
    mul->left = leaf2;
    mul->right = leaf3;

    // Plus node (3 + (4 * 5))
    Node *plus = malloc(sizeof(Node));
    plus->is_a_leaf = 0;
    plus->op = '+';
    plus->left = leaf1;
    plus->right = mul;

    printf("%d\n", op(plus)); // Should print 23

    // Free memory
    free(leaf1);
    free(leaf2);
    free(leaf3);
    free(mul);
    free(plus);
}