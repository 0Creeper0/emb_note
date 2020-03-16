#if 0
2.读入用户输入的10个学生的成绩，求得10学生成绩分布
有一个学生在此分数段则打印一个*
例如:
100: **
90~99:*
80~89:*****
.......
0~9:*
#endif
#include <stdio.h>

int main()
{
	int num;
	int arr_int[11] = {0};
	for (int i = 0; i < 10; i++)
	{
		do {
			scanf("%d", &num);
		} while (!(num <= 100 && num >= 0));		
		arr_int[num/10]++;
	}

	for (int i = 0; i < 11; i++)
	{
		if (i == 0)
		{
			printf ("0~9: ");
		}
		else if (i == 10)
		{
			printf ("100: ");
		}
		else
		{
			printf ("%d0~%d9: ", i, i);
		}

		for (int j = 0; j < arr_int[i]; j++)
			printf("*");
		printf("\n");
	}
	return 0;
}
