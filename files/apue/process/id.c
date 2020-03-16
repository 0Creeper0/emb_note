#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid;

	write(1, "hello", 5);
	printf("world");

	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(1);
	}

	if (pid == 0)
	{
		printf("c_pid:%d\n", getpid());
		while (1)
		{
			write(1, "child", 5);
			sleep(1);
		}

	}
	else
	{
		printf("p_pid:%d\n", getpid());
		while (1)
		{
			write(1, "parent", 6);
			sleep(1);
		}
	}

	return 0;
}
