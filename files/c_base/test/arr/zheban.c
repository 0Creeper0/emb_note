#include <stdio.h>

int main()
{
	int arr_int[9] = {1, 2, 5, 8, 11, 15, 18, 23, 27};
	int mid, i = 0, j = 8;
	int n;

	printf("输入要查找的数:");
	scanf("%d", &n);
	while (i <= j)
	{
		mid = (i + j) / 2;
		if (arr_int[mid] > n)
		{
			j = mid - 1;
		}
		else if (arr_int[mid] < n)
		{
			i = mid + 1;
		}
		else
		{
			printf("在第%d个\n", mid+1);
			return 0;
		}
	}
	
	printf("没有找到\n");

	return -1;
}
