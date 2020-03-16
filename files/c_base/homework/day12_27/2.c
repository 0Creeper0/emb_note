#include <stdio.h>

int main()
{
	int count = 0, num = 0;

	for (int i = 100; i <= 999; i++)
	{
		num = 0;
		num += (i % 10) * (i % 10) * (i % 10);
		num += (i / 10 % 10) * (i / 10 % 10) * (i / 10 % 10);
		num += (i / 100) * (i / 100) * (i / 100);
		if (i == num)
		{
			printf("%d	", i);
			count++;
		}
	}
	printf("\n个数:%d\n", count);

	return 0;
}
