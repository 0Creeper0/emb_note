#include <stdio.h>

int main()
{
	int i, j, k, count = 0;

	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 5; j++)
		{
			for (k = 0; k <= 10; k++)
			{
				if (i * 50 + j * 20 + k * 10 == 100)
				{
					printf ("%d张50的,%d张20的,%d张10的\n", i, j, k);
					count++;
				}
			}
		}
	}
	printf ("有%d种方式\n", count);

	return 0;
}

