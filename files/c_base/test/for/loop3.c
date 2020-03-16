#include <stdio.h>

int main()
{
	int num;

	printf("输入一个整数:");
	scanf("%d", &num);

	for (int i = 2; i <= num; i++)
	{
		if (num % i == 0)
		{
			if (i != num)
			{
				printf("%d不是质数\n", num);
				break;
			}
			else
			{
				printf("%d是质数\n", num);
			}
		}
	}
	if (num == 1)
		printf("%d不是质数\n", num);

	return 0;
}
