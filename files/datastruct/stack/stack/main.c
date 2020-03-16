#include <stdio.h>

#include "stack.h"

int main()
{
	stack_t *s = NULL;
	int size = sizeof(int);
	int maxnmemb = 10;
	int data;

	s = stack_init(size, maxnmemb);

	for (int i = 0; i < 20; i++)
	{
		stack_push(s, &i);
	}
	while (stack_pop(s, &data) == 0)
	{
		printf("%d\n", data);
	}

	return 0;
}
