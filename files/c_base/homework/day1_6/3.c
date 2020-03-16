#if 0
3.定义一个由11个整型数组成的整型数组，随机初始化10个有序的整型,再读入用户输入的一个整型数，使得数组依然有序
并倒序输出
#endif

#include <stdio.h>

int main()
{
	int arr_int[11];
	int tmp, j, num;
	
	for (int i = 1; i < 10; i++)
	{
		tmp = arr_int[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (arr_int[j] > tmp)
				arr_int[j+1] = arr_int[j];
			else
				break;			
		}
		arr_int[j+1] = tmp;
	}
	scanf ("%d", &num);
	for (j = 9; j >= 0; j--)
	{
		if (arr_int[j] > num)
			arr_int[j+1] = arr_int[j];
		else
			break;
	}
	arr_int[j+1] = num;

	for (int i = 0; i < 11; i++)
		printf("%d ", arr_int[i]);
	printf("\n");
	return 0;
}

