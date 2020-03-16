#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int f;

	close(1);

	f = open("./test", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (f == -1)
	{
		perror("open()");
		return 1;
	}

	printf("hello\n");
	fflush(NULL);

	close(f);

	return 0;
}
