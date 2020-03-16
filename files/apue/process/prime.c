#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

static int _isprime(int n)
{
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return 0;
	return 1;
}

int main()
{
	pid_t pid1, pid2, pid3, pid4;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork(1)");
		exit(1);
	}

	if (pid1 == 0)
	{
		for (int i = 100; i <= 150; i ++)
		{
			if(_isprime(i))
			{
				printf("[%d]%d\n", getpid(), i);
			}
		}

	}
	else
	{
		pid2 = fork();
		if (pid2 == -1)
		{
			perror("fork(1)");
			exit(1);
		}
		if (pid2 == 0)
		{
			for (int i = 151; i <= 200; i ++)
			{
				if(_isprime(i))
				{
					printf("[%d]%d\n", getpid(), i);
				}
			}
		}
		else
		{
			pid3 = fork();
			if (pid3 == -1)
			{
				perror("fork(1)");
				exit(1);
			}

			if (pid3 == 0)
			{
				for (int i = 201; i <= 250; i ++)
				{
					if(_isprime(i))
					{
						printf("[%d]%d\n", getpid(), i);
					}
				}
			}
			else
			{
				pid4 = fork();
				if (pid4 == -1)
				{
					perror("fork(1)");
					exit(1);
				}

				if (pid4 == 0)
				{
					for (int i = 251; i <= 300; i ++)
					{
						if(_isprime(i))
						{
							printf("[%d]%d\n", getpid(), i);
						}
					}
				}
			}
		}
	}




	wait(NULL);
	exit(EXIT_SUCCESS);
}
