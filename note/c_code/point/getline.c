#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *ptr = NULL;
	size_t n = 0;
	int readn;

	while (1) {
		readn = getline(&ptr, &n, stdin);
		printf("ptr:%s, n:%ld\n", ptr, n);
		printf("readn:%d\n", readn);
		free(ptr);
		ptr = NULL;
		n = 0;
	}

	return 0;
}
