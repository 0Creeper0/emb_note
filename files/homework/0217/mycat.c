#include <stdio.h>
#include <string.h>

#define BUFSIZE 	100

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;
	
	FILE *f;
	char buf[BUFSIZE];

	// open
	f = fopen(argv[1], "r");
	if (NULL == f)
	{
		perror("fopen()");
		return 1;
	}

	while (1)
	{
		memset(buf, '\0', BUFSIZE);
		if (fgets(buf, BUFSIZE, f) == NULL)
			break;
		fputs(buf, stdout);
	}

	fclose(f);

	return 0;
}
