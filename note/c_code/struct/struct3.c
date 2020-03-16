#include <stdio.h>

typedef struct test_st {
	int a;
	char b;
	short c;
	char name[10];
}s;

int main(void)
{
	// 已知结构体中某个元素的地址，如何求得这个结构体首元素地址 

	// 求得元素偏移量
	printf("%d\n", (int)(&((struct test_st *)0)->name));

	return 0;
}

