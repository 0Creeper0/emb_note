#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

static void handler(int s)
{
	;
}

int main()
{
	pid_t pid;

	signal(SIGINT, handler);

	pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(1);
	}
	if (pid == 0)
	{
		pause();
		write(1, "luck", 4);
		exit(0);
	}

	sleep(1);
	write(1, "good ", 5);

	kill(pid, SIGINT);
	wait(NULL);

	exit(0);
}
