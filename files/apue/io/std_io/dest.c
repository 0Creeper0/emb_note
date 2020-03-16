#include <stdio.h>

int main(int arvc, char *argv[])
{
	FILE *f;
	int c;
	f = fopen(argv[1], "r");
	if (NULL == f)
	{
		printf("fopen() error\n");
		return 1;
	}

	while (1)
	{
		c = fgetc(f);
		if (c == EOF)
		{
			if (ferror(f))
			{
				printf("ferror() error\n");
				break;
			}
			break;
		}
		printf("%c", c);
	}

	if (fclose(f) != 0)
	{
		printf("close failed\n");
	}
	return 0;
}
