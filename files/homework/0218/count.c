#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 	100

int main(int argc, char *argv[])
{
	if (argc < 3)
		return 1;

	int fd, len, count, sum = 0;
	char buf[BUFSIZE] = {};

	len = strlen(argv[2]);

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open()");
		return 1;
	}
	while (1)
	{
		count = read(fd, buf, len);
		if (count < len)
			break;
		if (count == -1)
		{
			perror("read()");
			goto ERROR;
		}
		if (strcmp(buf, argv[2]) == 0)
			sum ++;

		lseek(fd, -(len-1), SEEK_CUR);
	}
	printf("sum:%d\n", sum);
	close(fd);

	return 0;
ERROR:
	close(fd);
	return 1;
}
