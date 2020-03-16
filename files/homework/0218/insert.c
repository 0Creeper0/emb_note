#include <stdio.h>
#include <stdlib.h>
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

	int fd, count, pos, posend, len = 0, sum = 0, line = 0;
	char buf[BUFSIZE] = {};
	char *p, *buftmp;
	FILE *tmp;

	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		perror("open()");
		return 1;
	}
	while (1)
	{
		count = read(fd, buf, 1);
		if (count == 0)
			break;
		if (count == -1)
		{
			perror("read()");
			goto ERROR;
		}
		if (*buf == '\n')
			line ++;

		if (line == 2)
			break;
	}

	pos = lseek(fd, 0, SEEK_CUR);
	posend = lseek(fd, 0, SEEK_END);

	buftmp = malloc(posend-pos);
	if (NULL == buftmp)
		return 1;

	lseek(fd, pos, SEEK_SET);
	count = read(fd, buftmp, posend-pos);
	if (count == -1)
	{
		perror("read()");
		goto ERROR;
	}
	lseek(fd, pos, SEEK_SET);
	write(fd, argv[2], strlen(argv[2]));
	write(fd, buftmp, count);

	close(fd);
	free(buftmp);

	return 0;
ERROR:
	close(fd);
	return 1;
}
