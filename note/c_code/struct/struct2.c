#include <stdio.h>

// 指定对齐字节个数
#pragma pack(4)

struct test_st {
	char a;
	short c;
	int d;
	long b;
	char e;
	short f;
	int g;
	char h;
}/*__attribute__((packed))*/;

int main(void)
{
	struct test_st test;

	printf("%ld\n", sizeof(struct test_st));

	printf("%p %p %p %p %p %p\n", \
			&test.a, &test.c, &test.d, &test.b, &test.e, &test.f);

	return 0;
}

