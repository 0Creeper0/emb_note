#include <stdio.h>

#define BUFFERSIZE 	100

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	FILE *f;
	char buf[BUFFERSIZE];
	int c;

	f = fopen(argv[1], "r");
	if (NULL == f)
	{
		fprintf(stderr, "fopen() error\n");
		return 1;
	}

	while (1)
	{
		c = fgetc(f);
		if (c == EOF)
		{
			if (ferror(f))
			{
				fprintf(stderr, "ferror() error\n");
				printf("2");
				break;
			}
			break;
		}
		printf("%c", c);
		if (c == '\n')
			printf("1\n");
	}
	fclose(f);

	return 0;
}
