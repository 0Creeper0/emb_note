#include <stdio.h>

int main()
{
#if 0
	// 找出数组中最大数和最小数并将其交换
	int index_max, index_min, max = arr[0], min = arr[0];

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (max < arr[i])
		{
			max = arr[i];
			index_max = i;
		}
		if (min > arr[i])
		{
			min = arr[i];
			index_min = i;
		}
	}

	arr[index_max] = arr[index_max] ^ arr[index_min];
	arr[index_min] = arr[index_max] ^ arr[index_min];
	arr[index_max] = arr[index_max] ^ arr[index_min];

	for (int i = 0; i < 11; i++)
	{
		printf ("%d ", arr[i]);
	}
	printf("\n");
#endif
#if 0
	//冒泡排序
	int arr[] = {3,2,1,6,7,9,5,6,2,8,10};
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
	for (int i = 0; i < n; i++)
	{
		printf ("%d ", arr[i]);
	}
	printf("\n");
#endif 
#if 0
	//选择排序
	int arr[] = {3,2,1,6,7,9,5,6,2,8,10,0};
	int n;
	n = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (arr[i] > arr[j])
			{
				arr[i] = arr[i] ^ arr[j];
				arr[j] = arr[i] ^ arr[j];
				arr[i] = arr[i] ^ arr[j];
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		printf ("%d ", arr[i]);
	}
	printf("\n");
#endif 
	//直接插入
	int arr[] = {3,2,1,6,7,9,5,6,2,8,10};
	int n, tmp;
	n = sizeof(arr) / sizeof(arr[0]);

	for (int i = 1; i < n; i++)
	{
		tmp = arr[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (arr[j] > tmp)
			{
				arr[j+1] = arr[j];
				if (j == 0)
					arr[j] = tmp;
			}
			else
			{
				arr[j+1] = tmp;
				break;
			}
			printf("arr j :%d ", arr[j]);
		}
		/*
		 * for (int j = i - 1; j >= 0; j--)
		 * {
		 * 		if (arr[j] > tmp)
		 * 		{
		 * 			arr[j+1] = arr[j];
		 * 		}
		 * 		else
		 * 			break;
		 * }
		 * arr[j+1] = tmp;
		 *
		 * */
		for (int i = 0; i < n; i++)
		{
			printf ("%d ", arr[i]);
		}
		printf("\n");
	}

	return 0;
}
