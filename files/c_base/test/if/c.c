#include <stdio.h>

int main()
{
	int x = 11, y, z;

	if (x++>11)
		printf("a\n");
	else
		printf("%d\n", x--);
		printf("%d\n", x);


	return 0;
}
