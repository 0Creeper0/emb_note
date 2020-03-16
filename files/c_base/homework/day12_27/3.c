#include <stdio.h>

int main()
{
	int count = 0;

	for (int i = 1; i <= 999; i++)
	{
		if(i % 3 == 0 && (i % 10 == 5 || i / 10 % 10 == 5 || i / 100 == 5))
		{
			printf ("%d	", i);
			count++;
		}
	}
	printf ("\n个数:%d\n", count);

	return 0;
}
