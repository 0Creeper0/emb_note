#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	int fd, count, pos = 0, posend;
	char *buf;

	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		perror("open()");
		return 1;
	}

	posend = lseek(fd, 0, SEEK_END);

	buf = malloc(posend);
	if (NULL == buf)
		return 1;

	lseek(fd, 0, SEEK_SET);
	count = read(fd, buf, posend);
	if (count == -1)
	{
		perror("read()");
		goto ERROR;
	}
	lseek(fd, 0, SEEK_SET);
	while (1)
	{
		if (pos > posend)
			break;
		write(fd, buf + (posend - pos), 1);
		pos ++;
	}

	close(fd);
	free(buf);

	return 0;
ERROR:
	close(fd);
	return 1;
}
