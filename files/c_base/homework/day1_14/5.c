#if 0
5. 定义一个动态数组，实现数组的增删改查和遍历
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arr_add(int *p, int arg, int index);
int main()
{
	int *p;
	int arr[] = {1, 2};
	p = arr;
	arr_add(p, 3, 1);

	return 0;
}

int arr_add(int *p, int arg, int index)
{
	int n;

	n = sizeof(p) / sizeof(p[0]);
	printf("n:%d\n", n);

	if (index > n || index < 0)
	{
		printf("下标错误\n");
		return -1;
	}
	printf("1\n");
	p = realloc(p, (n + 1) * sizeof(int));
	if (NULL == p)
		return -1;

	printf("2\n");
	if (index != n)
		memmove(p + index + 1, p + index, n - index - 1);
	p[index] = arg;	
	return 0;
}
