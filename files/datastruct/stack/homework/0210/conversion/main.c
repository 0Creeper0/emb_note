#include <stdio.h>

#include "stack1.h"

int main()
{
	stack_t *s = NULL;
	int size = sizeof(char);
	int maxnmemb = 10;
	int res, data = 17, key = 16;

	printf("%d(%d):", data, key);
	s = stack_init(size, maxnmemb);

	conversion(s, data, key);

	while (stack_pop(s, &res) == 0)
	{
		printf("%d", res);
	}
	printf("\n");

	return 0;
}
