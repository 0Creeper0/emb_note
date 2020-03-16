#include <stdio.h>
#include <stdlib.h>
int main()
{
	char *ptr = NULL;
	size_t n = 0;
	int read;

	read = getline(&ptr, &n, stdin);
	printf("ptr:%s n:%d\n", ptr, n);
	printf("read:%ld\n", read);

	free(ptr);
	return 0;
}
