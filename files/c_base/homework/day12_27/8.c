#include <stdio.h>

int main()
{
	int male, female, sum = 0, count = 0;
	float child;

	for (male = 0; male <= 36; male++)
	{
		for (female = 0; female <= 36; female++)
		{
			for (child = 0; child <= 36; child++)
			{
				sum = male + female + child;
				if (male * 4 + female * 3 + child * 1 / 2 == 36 && sum == 36)
				{
					printf ("男%d人	女%d人	小儿%d人\n", male, female, (int)child);
					count++;
					
				}
			}
		}
	}

	printf ("共有%d组解\n", count);
	return 0;
}

