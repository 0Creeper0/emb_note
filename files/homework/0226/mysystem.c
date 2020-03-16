#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int mysystem(const char *command);
int main()
{
	if(mysystem("ls -la"))
	{
		fprintf(stderr, "mysystem() error\n");
		exit(1);
	}

	exit(0);
}

int mysystem(const char *command)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		return 1;
	}
	
	if (pid == 0)
	{
		execl("/bin/sh", "sh", "-c", command, (char *) NULL);
		perror("execl()");
		return 1;
	}
	wait(NULL);
	return 0;
}

