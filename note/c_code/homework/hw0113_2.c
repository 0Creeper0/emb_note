#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *alloc_memery(void);
void string_cat(const char *s1, const char *s2, char *res, int n);
int main(void)
{
	char *p;

	p = alloc_memery();
	string_cat("good", "morning", p, 1024);
	puts(p);

	return 0;
}

char *alloc_memery(void)
{
	char *p = malloc(1024);
	if (NULL == p)
		return p;
	memset(p, '\0', 1024);

	return p;
}

void string_cat(const char *s1, const char *s2, char *res, int n)
{
	strncpy(res, s1, n);
	strncat(res, s2, n-strlen(s1));
}

