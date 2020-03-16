#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFERSIZE 	100

int main(int argc, char *argv[])
{
	if (argc < 3)
		return 1;

	int src, dest;
	int c;
	char buf[BUFFERSIZE];
	char *str;

	// 打开
	src = open(argv[1], O_RDONLY);
	if (src == -1)
	{
		perror("src open()");
		return 1;
	}
	dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (dest == -1)
	{
		perror("dest open()");
		return 1;
	}

	// 读写
	// 一行
	while (1)
	{
		str = fgets(buf, BUFFERSIZE, argv[1]);
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
