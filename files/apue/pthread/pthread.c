#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void *thr_job(void *arg)
{
	write(1, "new thread", 10);
	pthread_exit((void *)0);
}

int main()
{
	pthread_t ptd;
	pthread_create(&ptd, NULL, thr_job, NULL);

	pthread_join(ptd, NULL);
	printf("main, new thread end\n");

	exit(0);
}
