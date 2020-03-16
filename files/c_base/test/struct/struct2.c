#include <stdio.h>

struct st
{
	int a;
	char b;
	long c;
	char d;
	long e;
};

int main()
{
	struct st s;
	printf("%ld\n", sizeof(struct st));
	printf("%p, %p, %p, %p, %p\n", &s.a, &s.b, &s.c, &s.d, &s.e);

	return 0;
}
