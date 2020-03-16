#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define RESSIZE 	10

static char **str2args(char *str)
{
	char *s;
	static char *res[RESSIZE] = {};
	int i = 0;
	while (1)
	{
		s = strsep(&str, " \n");
		if (NULL == s)
			break;
		if (*s == '\0')
			continue;
		res[i++] = s;
	}
	res[i] = NULL;
	return res;
}

int main()
{
	pid_t pid;
	char *buf;
	char **arg;
	size_t n = 0;

	while(1)
	{
		printf("[user@localhost]$ ");

		if (getline(&buf, &n, stdin) == -1)
		{
			fprintf(stderr, "getline() error\n");
			exit(1);
		}
		if (!strcmp(buf, "exit\n"))
			break;

		arg = str2args(buf);

		pid = fork();
		if (pid == -1)
		{
			perror("fork()");
			exit(1);
		}

		if (pid == 0)
		{
			execvp(arg[0], arg);
			perror("execvp()");
			exit(1);
		}

		wait(NULL);
	}
	exit(0);
}
