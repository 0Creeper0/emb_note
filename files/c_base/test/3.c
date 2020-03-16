#include <stdio.h>

int main()
{
	char *p;
	int *p2;

	printf("%p %p\n%p %p\n", p, p + 1, p2, p2 + 1);

	return 0;
}
