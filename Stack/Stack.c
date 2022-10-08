#include <stdio.h>

/*Defenition of Boolean_type*/
typedef enum Boolean_type
{
    false,
    true
} Boolean_type;

/* Error: print error message and terminate the program. */
void Error(char *s)
{
    fprintf(stderr, "Error!\n", s);
    exit(1);
}

/*Max stack capacity is defined by customer*/
#define MAXSTACK 10

/*Item_type held by node is defined by customer for example we use simple int*/
typedef struct Item_type
{
    int data;

} Item_type;

/*Definition of stack*/
typedef struct stack_tag
{
    int top;
    Item_type entry[MAXSTACK];
} Stack_type;

/* Push: push an item onto the stack. */
void Push(Item_type item, Stack_type *stack_ptr)
{
    if (stack_ptr->top >= MAXSTACK)
        Error("Stack is full");
    else
        stack_ptr->entry[stack_ptr->top++] = item;
}

/* Pop: pop an item from the stack. */
void Pop(Item_type *item_ptr, Stack_type *stack_ptr)
{
    if (stack_ptr->top <= 0)
        Error("Stack is empty");
    else
        *item_ptr = stack_ptr->entry[--stack_ptr->top];
}

/* Empty: returns non-zero if the stack is empty. */
Boolean_type Empty(Stack_type *stack_ptr) { return stack_ptr->top <= 0; }

/* Full: returns non-zero if the stack is full. */
Boolean_type Full(Stack_type *stack_ptr) { return stack_ptr->top >= MAXSTACK; }

/* Initialize: initialize stack. */
void Initialize(Stack_type *stack_ptr) { stack_ptr->top = 0; }