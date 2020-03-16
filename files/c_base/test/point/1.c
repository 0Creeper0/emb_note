#include <stdio.h>
#include <stdlib.h>

// (void *)是万能指针
int main()
{
	char *a = NULL;
	int n = 0;
	char c;
	
	while ((c = getchar()) != '\n')
	{
		a = realloc(a, n);
		a[n++] = c;
	}
	//a = realloc(a, --n);

	puts(a);

	free(a);

	return 0;
}
