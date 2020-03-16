#if 0
1. 尝试使用二维数组显示以下图形
[]
[]
[][]

[]
[][]
  []

[][][] 
  []
#endif

#include <stdio.h>

int main()
{
	char str[3][6];
	int n;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j == 0 || j % 2 == 0)
				str[i][j] = '[';
			else
				str[i][j] = ']';
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (i < 2)
			n = 2;
		else
			n = 4;
		for (int j = 0; j < n; j++)
		{
			printf("%c", str[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (int i = 0; i < 3; i++)
	{
		if (i < 2)
		{
			for (int j = 0; j < 2*i+2; j++)
			{
				printf("%c", str[i][j]);
			}
			printf("\n");
		}
		else
		{
			for (int j = 0; j < 2*i+2; j++)
			{
				if (j / 2 == 1)
					printf("%c", str[i][j]);
				else 
					printf(" ");
			}
			printf("\n");
		}
	}
	printf("\n");

	for (int i = 0; i < 3; i++)
	{
		if (i == 2)
			break;
		else
		{
			for (int j = 0; j < 6; j++)
			{
				if (i == 0)
					printf("%c", str[i][j]);
				else
				{
					if (j / 2 == 1)
						printf("%c", str[i][j]);
					else
						printf(" ");

				}
			}
			printf("\n");
		}
	}

	return 0;
}

