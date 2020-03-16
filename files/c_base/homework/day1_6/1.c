//1.读入用户输入的10个整型数，存储到一个整型的数组中，求出10个元素的平均值
#include <stdio.h>

int main()
{
	int arr_int[10], sum = 0;

	printf("输入十个数:");

	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &arr_int[i]);
		sum += arr_int[i];
	}
	printf ("average:%.2f\n", (float)sum/10);

	return 0;

}
