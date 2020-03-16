#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int reverse_string(const char *src, char **res);
int main(void)
{
	char *ptr = NULL;
	char *p = "hello world";

	printf("%d\n", reverse_string(p, &ptr));
	puts(ptr);

	free(ptr);

	return 0;
}

int reverse_string(const char *src, char **res)
{
	int i, j;
	int len;

	len = strlen(src);
		
	*res = calloc(len+1, 1);
	if (NULL == *res)
		return -1;

	for (i = 0, j = len-1; j >= 0; i++, j--) {
		(*res)[i] = src[j];
	}
	
	return len;
}


