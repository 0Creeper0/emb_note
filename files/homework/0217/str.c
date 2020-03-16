#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;
	
	FILE *f;
	char *buf;
	int size;

	// open
	f = fopen(argv[1], "w");
	if (NULL == f)
	{
		perror("fopen()");
		return 1;
	}

	size = strlen(argv[2]) + 1;
	buf = malloc(size);

	memcpy(buf, argv[2], size);
	buf[size-1] = '\n';

	fputs(buf, f);

	fclose(f);
	free(buf);

	return 0;
}
