#if 0
2. 定义一个函数，通过参数将一个整型数组的最大值和最小值返回
#endif
#include <stdio.h>

int arr_max_min(int *arr, int a);
int main()
{
	int arr_int[] = {89, 1, 2, 5, 29};

	printf("%d\n", arr_max_min(arr_int, 1));

	return 0;
}

int arr_max_min(int *arr, int a)
{
	// 0 max, 1 min
	int max, min, n;
	max = min = *arr;
	n = sizeof(arr) / sizeof(*arr);
	for (int i = 0; i < n; i++)
	{
		if (max < *(arr + i))
			max =  *(arr + i);
		if (min > *(arr + i))
			min = *(arr + i);
	}
	if (a == 0)
		return max;
	if (a == 1)
		return min;
}
