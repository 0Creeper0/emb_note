#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define LEFT	100
#define RIGHT	300

static void *ptd_job(void *arg)
{

	sleep(1);
	int num = (int)arg;
	for (int i = 2; i < num; i++)
	{
		if (num % i == 0)
		{
			pthread_exit((void *)0);
		}
	}
	printf("%d\n", num);
	pthread_exit((void *)0);

}

int main(void)
{
	pthread_t ptd[RIGHT-LEFT+1] = {};
	int err;

	for (int i = LEFT; i <= RIGHT; i++)
	{
		err = pthread_create(ptd+i-LEFT, NULL, ptd_job, (void *)i);
		if (err != 0)
		{
			fprintf(stderr, "pthread_create(): %s\n", strerror(err));
			exit(1);
		}
	}

	for (int i = LEFT; i <= RIGHT; i++)
		pthread_join(ptd[i-LEFT], NULL);

	exit(0);
}
