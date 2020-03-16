#include <stdio.h>

int main()
{
	// 1 1 2 3 5 8
	int a = 0, b = 1, c = 1;
	
	printf("%d	", c);
	for (int i = 1; i < 20; i++)
	{
		c = a + b;
		printf("%d	", c);
		a = b;
		b = c;
	}

	return 0;
}

