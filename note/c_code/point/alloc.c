#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mygets(char **ptr);
int main(void)
{
	char *p = NULL;
	int size;

#if 0
//	p = malloc(100);
	p = calloc(100, 1);
	if (NULL == p)
		return 1;

	fgets(p, 100, stdin);	
	puts(p);
	p = realloc(p, 200);

	puts(p);

	free(p);
#endif

	size = mygets(&p);

	puts(p);
	printf("len:%d\n", size);

	free(p);

	return 0;
}

int mygets(char **ptr)
{
	char *p, *q;
	p = q = NULL;
	int i = 0;
	char ch;

	do {
		ch = getchar();
		p = realloc(p, i+1);
		p[i++] = ch;
	} while(ch != '\n');
	p[i-1] = '\0';

	*ptr = p;

	return i-1;
}


