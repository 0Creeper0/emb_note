#include <stdio.h>

// 变参函数
int test(int a, int b, int c);
int main(void)
{
	volatile int n = 5;
	test(n++, n++, n++);

	printf("%d %d\n", n++, n);

	return 0;
}

int test(int a, int b, int c)
{
	printf("a:%d, b:%d, c:%d\n", a, b, c);
	printf("&a:%p, &b:%p, &c:%p\n", &a, &b, &c);
}


