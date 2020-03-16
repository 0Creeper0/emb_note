#include <stdio.h>

int main()
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j < i; j++)
		{
			printf("%c ", 'A'+j);
		}
		printf("\n");
	}

	for (int i = 1; i <= 10; i++)
	{
		//空格
		for (int j = 0; j < 2 * (10 - i); j++)
		{
			printf(" ");
		}

		//字母
		for (int k = 0; k < i; k++)
			printf("%c ", 'A'+k);

		for (int l = i - 2; l >= 0; l--)
			printf("%c ", 'A'+l);

		printf("\n");
	}

	return 0;
}

