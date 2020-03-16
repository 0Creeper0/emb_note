#include <stdio.h>

int sumn(int n);
int fib(int n);
int main(void)
{
	printf("%d\n", sumn(100));

	for (int i = 1; i <= 20; i++)
		printf("%d ", fib(i));
	printf("\n");

	return 0;
}

int sumn(int n)
{
	if (n == 0)
		return 0;

	return n + sumn(n-1);
}

int fib(int n)
{
	if (n == 1 || n == 2)
		return 1;
	return fib(n-1) + fib(n-2);
}

