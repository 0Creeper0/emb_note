/*
 1. 能排序任意数组的函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp_int(const void *data1, const void *data2)
{
	const int *d1 = data1;
	const int *d2 = data2;
	
	return *d2 - *d1;
}

int comp_char(const void *data1, const void *data2)
{
	const char *d1 = data1;
	const char *d2 = data2;

	return *d2 - *d1;
}

void sort(void *arr, int num, int size, int (*comp)(const void *, const void *));
int main()
{
	int arr_int[] = {3, 5, 24, 13, 8, 2};
	char arr_char[] = "jshenglakjsdfao";

	sort(arr_char, sizeof(arr_char)/sizeof(*arr_char), sizeof(char), comp_char);

	for (int i = 0; i < sizeof(arr_char)/sizeof(*arr_char); i++)
		printf("%c ", arr_char[i]);
	printf("\n");

	return 0;
}

void sort(void *arr, int num, int size, int (*comp)(const void *, const void *))
{
	char *p = calloc(1, size);

	// 排序
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = 0; j < num - i - 1; j++)
		{
			if (comp((char *)arr + (j + 1) * size, (char *)arr + j * size) > 0)
			{
				// 交换
				memcpy(p, (char *)arr + (j + 1) * size, size);
				memcpy((char *)arr + (j + 1) * size, (char *)arr + j * size, size);
				memcpy((char *)arr + j * size, p, size);
			}
		}
	}

	free(p);
}

