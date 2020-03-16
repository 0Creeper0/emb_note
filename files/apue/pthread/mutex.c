#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sched.h>

#define LEFT	100
#define RIGHT	300

#define THR_N 	4

/*
 * job == 0		还有任务但是没法放
 * job == -1	任务发放完成
 * iob > 0		待发放的任务
 */

static int job;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *pth_job(void *arg);
int main(void)
{
	pthread_t pth[THR_N] = {};
	int err;

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

	// 任务发放
	for (int i = LEFT; i <= RIGHT; i++)
	{
		pthread_mutex_lock(&mutex);
		while (job != 0)
		{
			pthread_mutex_unlock(&mutex);
			sched_yield(); // 优先调度其他进程
			pthread_mutex_lock(&mutex);
		}
		
		job = i;
		pthread_mutex_unlock(&mutex);
	}

	
	pthread_mutex_lock(&mutex);
	while(job > 0)
	{
		pthread_mutex_unlock(&mutex);
		sched_yield();
		pthread_mutex_lock(&mutex);
	}
	job = -1;
	pthread_mutex_unlock(&mutex);

	// 收尸
	for (int i = 0; i < THR_N; i++)
	{
		pthread_join(pth[i], NULL);
	}
	
	pthread_mutex_destroy(&mutex);

	exit(0);
}

static int _isprime(int n)
{
	for (int i = 2; i < n; i++)
	{
		if (n % i == 0)
			return 0;
	}
	return 1;
}

// 线程工作
static void *pth_job(void *arg)
{
	int j;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if (job == -1)
		{
			pthread_mutex_unlock(&mutex);
			pthread_exit((void *)0);
		}
		if (job == 0)
		{
			pthread_mutex_unlock(&mutex);
			sched_yield();
			continue;
		}

		j = job;
		job = 0; // 抢到了任务要把job置0
		pthread_mutex_unlock(&mutex);

		if (_isprime(j))
			printf("%d\n", j);
	}
}
