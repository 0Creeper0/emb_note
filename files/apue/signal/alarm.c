#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int s)
{
	alarm(3);
	write(1, "!", 1);
}

int main()
{
	signal(SIGALRM, handler);
	alarm(3);

	while(1)
	{
		write(1, "*", 1);
		sleep(1);
	}
	exit(0);
}
