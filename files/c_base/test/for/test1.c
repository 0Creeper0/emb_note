#include <stdio.h>

int main()
{
	int a, b, c, res;

	printf ("输入a, b, c:");
	scanf ("%d%d%d", &a, &b, &c);

	for (res = 10; res <= 100; res++)
	{
		if ((res - a) % 3 == 0 && (res - b) % 5 == 0 && (res - c) % 7 == 0)
		{
			printf ("总人数:%d\n", res);
			return 0;
		}
	}
	printf ("No answer\n");
	return -1;
}
