#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>

#define THR_N 	5

/*
 * flag == 0 	没任务
 * flag == 1	有任务*/

static pthread_mutex_t mutex[THR_N] = {PTHREAD_MUTEX_INITIALIZER};
static pthread_t pth[THR_N] = {};

static void *pth_job(void *arg);
int main(void)
{
	int err;
	// 创建线程
	for (int i = 0; i < THR_N; i++)
	{
		err = pthread_create(pth+i, NULL, pth_job, (void *)i);
		if (err != 0)
		{
			fprintf(stderr, "pthread_create() %s\n", strerror(err));
			exit(1);
		}
	}
	pthread_mutex_unlock(mutex);
	for (int i = 0; i < THR_N; i++)
		sleep(1);
	for (int i = 0; i < THR_N; i++)
		pthread_mutex_destroy(mutex+i);
	
	exit(0);
}
static void *pth_job(void *arg)
{
	int id = (int)arg;
	char c = 'a'+id;
	while(1)
	{
		pthread_mutex_lock(mutex+id);
		putchar(c);
		fflush(NULL);
		pthread_mutex_unlock(mutex+(id+1)%5);
	}
}
