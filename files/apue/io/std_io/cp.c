#include <stdio.h>

#define BUFFERSIZE 	100

int main(int argc, char *argv[])
{
	if (argc < 3)
		return 1;

	FILE *src, *dest;
	int c;
	char buf[BUFFERSIZE];
	char *str;

	// 打开
	src = fopen(argv[1], "r");
	if (NULL == src)
	{
		printf("fopen(src) error\n");
		return 1;
	}
	dest = fopen(argv[2], "w");
	if (NULL == dest)
	{
		printf("fopen(dest) error\n");
		return 1;
	}

	// 读写
#if 0
	// 字符
	while (1)
	{
		c = fgetc(src);
		if (c == EOF)
		{
			if (ferror(src))
			{
				printf("ferror() error\n");
				break;
			}
			break;
		}

		fputc(c, dest);
	}
#endif
	// 一行
	while (1)
	{
		str = fgets(buf, BUFFERSIZE, src);
		if (NULL == str)
			break;
		fputs(buf, dest);
	}
#if 0
	// 二进制
	while (1)
	{
		c = fread(buf, 1, BUFFERSIZE, src);
		if (c == 0)
			break;
		fwrite(buf, 1, c, dest);
	}
#endif

	if (fclose(src) != 0)
	{
		printf("src close failed\n");
	}
	if (fclose(dest) != 0)
	{
		printf("dest close failed\n");
	}
	return 0;
}
