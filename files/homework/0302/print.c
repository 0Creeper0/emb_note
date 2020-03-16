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

static int id = -1, flag;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_t pth[THR_N] = {};

static void sig_handler(int s);
static void *pth_job(void *arg);
int main(void)
{
	int err;
	struct sigaction act, oldact;

	act.sa_handler = sig_handler;
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, &oldact);
	alarm(5);
	// 创建线程
	for (int i = 0; i < THR_N; i++)
	{
		err = pthread_create(pth+i, NULL, pth_job, NULL);
		if (err != 0)
		{
			fprintf(stderr, "pthread_create() %s\n", strerror(err));
			exit(1);
		}
	}

	while (1)
	{
		pthread_mutex_lock(&mutex);
		while(flag != 0)
		{
			pthread_mutex_unlock(&mutex);
			sched_yield();
			pthread_mutex_lock(&mutex);
		}
		flag = 1;
		id ++;
		pthread_mutex_unlock(&mutex);
	}
	
	exit(0);
}

static void sig_handler(int s)
{
	for (int i = 0; i < THR_N; i++)
	{
		pthread_cancel(pth[i]);
	}
	pthread_mutex_destroy(&mutex);
	exit(0);
}

static void *pth_job(void *arg)
{
	// 1就循环打印a
	pthread_t tid = pthread_self();
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if (flag == 0)
		{
			pthread_mutex_unlock(&mutex);
			sched_yield();
			continue;
		}
		for (int i = 0; i < 5; i++)
		{
			if (pthread_equal(tid, pth[i]) != 0 && id % 5 == i)
			{
				flag = 0;
				printf("%c", 'a'+i);
				break;
			}
		}
		pthread_mutex_unlock(&mutex);
	}
}
