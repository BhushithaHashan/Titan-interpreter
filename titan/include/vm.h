#ifndef TITAN_VM_H
#define TITAN_VM_H

typedef enum {
    OP_PUSH,   // Push literal 
    OP_ADD,    // +
    OP_SUB,    // -
    OP_MUL,    // *
    OP_DIV,    // /
    OP_STORE,  // Save variable
    OP_LOAD,   // Load variable
    OP_CALL,   // Start function
    OP_RET,    // End function
    OP_JMP,    // Loop/Jump
    OP_HALT    // Stop program
} OpCode;

// This represents the "State" of our language at any moment
typedef struct {
    unsigned char* code;    // The bytecode array
    int* heap;              // mmap'd memory
    int call_stack[256];         // math workspace
    int fp; 
    int data_stack[1024];
    int sp;                // stack pointer
    int pc;                 // program counter
} TitanVM;
void vm_init(TitanVM* vm, unsigned char* code);
void vm_run(TitanVM* vm);
#endif