#if 0
3. 动态开辟能容纳若干整型元素的数组，读入用户输入的整型数，依次存放到此数组中，使得
没插入的一个整型数组都是有序的
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(int *arr);
int main()
{
	int num, i;
	size_t n = 1;
	int *p = NULL;
	int *res, count = 0;

	int *dest, *src;

	while (getchar() != '\n')
	{
		scanf("%d", &num);
		count ++;
		p = realloc(p, n);
		p[n-1] = num;
		sort(p);
		n ++;
	}

	for (int i = 0; i < count; i++)
		printf("%d ", p[i]);
	printf("\n");

	free(p);
	return 0;
}

void sort(int *arr)
{
	int n;

	n = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			printf("%d ", arr[j+1]);
			if (arr[j] > arr[j+1])
			{
				arr[j] = arr[j] ^ arr[j+1];
				arr[j+1] = arr[j] ^ arr[j+1];
				arr[j] = arr[j] ^ arr[j+1];
			}
		}
	}
}
