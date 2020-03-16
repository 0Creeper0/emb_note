#include <stdio.h>
#include <string.h>

#define BUFSIZE 	100

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;
	
	FILE *f, *tmpf;
	char buf[BUFSIZE];
	int c, offset = -1;

	// open
	f = fopen(argv[1], "r");
	if (NULL == f)
	{
		perror("fopen()");
		return 1;
	}
	tmpf = tmpfile();
	if (NULL == tmpf)
	{
		perror("tmpfile()");
		return 1;
	}

	while (1)
	{
		memset(buf, '\0', BUFSIZE);
		if (fgets(buf, BUFSIZE, f) == NULL)
			break;
		fputs(buf, tmpf);
	}
	fclose(f);

	f = fopen(argv[1], "w");
	if (NULL == f)
	{
		perror("fopen()");
		return 1;
	}
	while (1)
	{
		fseek(tmpf, --offset, SEEK_END);
		if (ftell(tmpf) == 0)
		{
			c = fgetc(tmpf);
			if (c == EOF)
				return 1;
			fputc(c, f);
			break;
		}
		c = fgetc(tmpf);
		if (c == EOF)
			return 1;
		fputc(c, f);
	}
	fseek(f, 0, SEEK_END);
	fputc(10, f); // 文件结尾放\n
	fclose(f);

	return 0;
}
