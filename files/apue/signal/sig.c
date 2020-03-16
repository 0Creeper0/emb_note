#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int s)
{
	for (int i = 0; i < 3; i++)
	{
		write(1, "!", 1);
		sleep(1);
	}
}

int main()
{
	signal(SIGINT, handler);

	while(1)
	{
		write(1, "*", 1);
		sleep(1);
	}
	exit(0);
}
