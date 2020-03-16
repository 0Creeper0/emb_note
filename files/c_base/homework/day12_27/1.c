#include <stdio.h>

int main()
{
	int count = 0;
	for (int i = 10000; i <= 30000; i++)
	{
		if (i % 3 == 0 && i % 5 == 0 && i % 7 == 0 && i % 23 == 0)
		{
			printf("%d	", i);
			count++;
		}
	}
	printf("\n数量:%d\n", count);

	return 0;
}
