#include <stdio.h>

int main(void)
{
	char str[] = "embedded";
	const char *p = str; // 指针常量
	// char const * p;
	char *const q = str; // 常量指针

	// *p = 'a';
	p++;

	*q = 'a';
	q ++;

	puts(p);
	puts(q);

	return 0;
}
