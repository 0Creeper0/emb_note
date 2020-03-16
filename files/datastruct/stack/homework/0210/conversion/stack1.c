#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "stack1.h"

// stack init
stack_t *stack_init(int size, int maxnmemb)
{
	stack_t *s = NULL;
	s = malloc(sizeof(stack_t));
	if (NULL == s)
		return NULL;

	s->base = calloc(maxnmemb, size);
	if (NULL == s->base)
		return NULL;
	s->top = s->base;
	s->size = size;
	s->maxnmemb = maxnmemb;
	return s;
}

// stack_isempty
int stack_isempty(stack_t *s)
{
	return s->base == s->top;
}

// stack_isfull
int stack_isfull(stack_t *s)
{
	return ((char *)s->top - (char *)s->base) / sizeof(char) == 8;
}

// stack push
int stack_push(stack_t *s, const void *data)
{
	if (stack_isfull(s))
		return 1;

	memcpy(s->top, data, s->size);
	s->top = (char *)s->top + s->size;
	return 0;
}

// stack pop
int stack_pop(stack_t *s, void *data)
{
	if (stack_isempty(s))
		return 1;

	s->top = (char *)s->top - s->size;
	memcpy(data, s->top, s->size);
	return 0;
}

// stack destroy
void stack_destroy(stack_t *s)
{
	free(s->base);
	free(s);
}

// conversion
void conversion(stack_t *s, int data, int key)
{
	int num;
	while (data > 0)
	{
		num = data % key;
		stack_push(s, &num);
		data /= key;
	}
}
