#ifndef __STACK1_H
#define __STACK1_H

// ADT
typedef struct
{
	void *top;
	void *base;
	int size;
	int maxnmemb;
} stack_t;

// stack init
stack_t *stack_init(int size, int maxnmemb);

// stack_isempty
int stack_isempty(stack_t *s);

// stack_isfull
int stack_isfull(stack_t *s);

// stack push
int stack_push(stack_t *s, const void *data);

// stack pop
int stack_pop(stack_t *s, void *data);

// stack destroy
void stack_destroy(stack_t *s);

// conversion
void conversion(stack_t *s, int data, int key);
#endif
