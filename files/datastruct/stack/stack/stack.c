#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

// 接口
stack_t *stack_init(int size, int maxnmemb)
{
	stack_t *p = NULL;
	p = malloc(sizeof(stack_t));
	if (NULL == p)
		return NULL;

	p->base = calloc(maxnmemb, size);
	if (NULL == p->base)
		return NULL;
	p->top = p->base;
	p->size = size;
	p->maxnmemb = maxnmemb;
	return p;
}

// 入
int stack_push(stack_t *s, const void *data)
{
	if (stack_isfull(s))
		return 1;

	memcpy(s->top, data, s->size);
	s->top = (char *)s->top + s->size;
	return 0;
}

// 出
int stack_pop(stack_t *s, void *data)
{
	if (stack_isempty(s))
		return 1;

	s->top = (char *)s->top - s->size;
	memcpy(data, s->top, s->size);
	return 0;
}

// 是否空栈
int stack_isempty(const stack_t *s)
{
	return s->top == s->base;
}

// 是否满
int stack_isfull(const stack_t *s)
{
	return ((char *)s->top - (char *)s->base) / s->size == s->maxnmemb;
}

// 销毁
void stack_destroy(stack_t *s)
{
	free(s->base);
	free(s);
}
