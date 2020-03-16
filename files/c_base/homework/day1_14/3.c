#if 0
3. 定义一个函数，可以给任意类型数组中元素按任意次序排序(从大到小　从小到大都要能兼容)	
	注意是一个函数（不管是整型数组，字符数组，还是指针数组都要兼容）
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_int(const void *data1, const void *data2)
{
	const int *d1 = data1;
	const int *d2 = data2;

	return *d2 - *d1;
}

int cmp_char(const void *data1, const void *data2)
{
	const char *d1 = data1;
	const char *d2 = data2;

	return *d2 - *d1;
}

void sort(void *arr, int num, int size, int (*cmp)(const void *, const void *));
int main()
{
	int arr_int[] = {5, 1, 3, 2, 4, 19, 3};
	char arr_char[] = "acdfasdf";
	char *d1 = arr_char + 1;
	char *d2 = arr_char + 2;

	sort(arr_char, sizeof(arr_char)/sizeof(*arr_char), sizeof(char), cmp_char);

	for (int i = 0; i < sizeof(arr_char)/sizeof(*arr_char); i++)
		printf("%c ",arr_char[i]);
	printf("\n");
	printf("%d\n", *d1 - *d2);
	return 0;
}

void sort(void *arr, int num, int size, int (*cmp)(const void *, const void *))
{
	char *p = calloc(size, 1);

	for (int i = 0; i < num - 1; i++)
	{
		for (int j = 0; j < num - i - 1; j++)
		{
			if (cmp((char *)arr + (j + 1) * size, (char *)arr + j * size) > 0)
			{
				memcpy(p, (char *)arr + (j + 1) * size, size);
				memcpy((char *)arr + (j + 1) * size, (char *)arr + j * size, size);
				memcpy((char *)arr + j * size, p, size);
			}
		}
	}

	free(p);
	return ;
}
