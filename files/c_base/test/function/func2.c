#include <stdio.h>

int func(int n);

int main()
{
	int num;
	scanf("%d", &num);
	printf("%d\n", func(num));

	return 0;
}

int func(int n)
{
	if (n <= 2)
		return 1;

	return func(n-1) + func(n-2);
}

