#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
	int fd, count = 0;
	struct stat res;
	char *str;
	char *p;

	if (argc < 2)
		exit(1);

	fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		perror("open()");
		exit(1);
	}

	if(stat(argv[1], &res) == -1)
	{
		perror("stat()");
		exit(1);
	}

	str = mmap(argv[1], res.st_size, PROT_READ, MAP_SHARED, fd, lseek(fd, 0, SEEK_SET));
	if (MAP_FAILED == str)
	{
		perror("mmap()");
		exit(1);
	}
	
	while(1)
	{
		str = strstr(str, argv[2]);
		if (str == NULL)
			break;
		str += strlen(argv[2]);
		count ++;
	}
	printf("count:%d\n", count);
	close(fd);
	exit(0);
}
