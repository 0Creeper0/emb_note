#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	FILE *f;
	int c;
	f = fopen(argv[1], "r");
	if (NULL == f)
	{
		//fprintf(stderr, "fopen():%s\n", strerror(errno));
		perror("fopen()");
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
