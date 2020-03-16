#include <stdio.h>

int add(int a, int b)
{
	return a + b;
}
int sub(int a, int b)
{
	return a - b;
}

int multi(int a, int b)
{
	return a * b;
}

int div(int a, int b)
{
	return a / b;
}

void test(int m, int n, int (*f)(int, int));
int main(void)
{
	test(1, 2, add);
	test(1, 2, sub);

	return 0;
}

void test(int m, int n, int (*f)(int, int))
{
	printf("%d\n", f(m, n));
}
