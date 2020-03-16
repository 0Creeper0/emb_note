#include <stdio.h>

int main(void)
{
	char str[] = "02468";
	char *p;

	p = str;
	printf("%c\n", *p);
	printf("%c\n", *p++);
	printf("%c\n", *(p++));
	printf("%c\n", (*p)++);
	puts(p);

	printf("%c\n", --*p);
	printf("%c\n", --(*p));
	printf("%c\n", *(++p));

	return 0;
}

