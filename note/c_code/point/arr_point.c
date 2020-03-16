#include <stdio.h>

int main(void)
{
	int arr[3] = {12,3,4};
	int a[2][4] = {};

	// 数组指针
	int (*p)[3] = &arr;
	int (*q)[4] = a;

	printf("%p\n", p);
	printf("%p\n", p+1);

	printf("%p\n", q);
	printf("%p\n", q+1);

	return 0;
}

