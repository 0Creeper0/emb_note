#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>


#include "token.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static token_t *token_arr[ARRSIZE] = {};
static int flag = 0, job = 0;

static void *start_job(void *arg)
{
	printf("1\n");
	pthread_mutex_lock(&mutex);
//	while(job != 0)
//		pthread_cond_wait(&cond, &mutex);
//	job = 1;
	printf("1\n");
	for (int i = 0; i < ARRSIZE; i++)
	{
		if (token_arr[i] != NULL)
		{
			token_arr[i]->token += token_arr[i]->cps;
			if (token_arr[i]->token >= token_arr[i]->burst)
				token_arr[i]->token = token_arr[i]->burst;
		}
	}
	//job = 0;
	//pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
	sleep(1);
	start_job(NULL);
}

static void getting_start(void)
{
	int err;
	pthread_t pth_start;

	err = pthread_create(&pth_start, NULL, start_job, NULL);
}

static int get_free_pos(void)
{
	for (int i = 0; i < ARRSIZE; i++)
	{
		if (token_arr[i] == NULL)
			return i;
	}
	return -1;
}

// 初始化(返回td)
int token_init(int cps, int burst)
{
	token_t *t;
	int pos;
	
	pthread_mutex_lock(&mutex);
	//while(job != 0)
	//	pthread_cond_wait(&cond, &mutex);
	//job = 1;
	t = malloc(sizeof(token_t));
	if (NULL == t)
	{
		fprintf(stderr, "malloc() failed\n");
		return -1;
	}

	t->token = 0;
	t->cps = cps;
	t->burst = burst;

	pos = get_free_pos();
	if (pos == -1)
	{
		fprintf(stderr, "no more memery\n");
		free(t);
		return -1;
	}
	token_arr[pos] = t;

	//job = 0;
	//pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);

	printf("1\n");
	if (flag == 0)
	{
		getting_start();
		flag = 1;
	}

	printf("1\n");
	return pos;
}

// 取令牌
int token_get(int td, int token)
{
	int ret;

	if (td < 0 || token < 0)
		return -1;

	pthread_mutex_lock(&mutex);
	while (token_arr[td]->token <= 0)
		pause();

	if (token > token_arr[td]->token)
	{
		ret = token_arr[td]->token;
		token_arr[td]->token = 0;
	}
	else
	{
		ret = token;
		token_arr[td]->token -= token;
	}
	pthread_mutex_unlock(&mutex);
	
	return ret;
}

// 还令牌
int token_put(int td, int token)
{
	pthread_mutex_lock(&mutex);
	if (td < 0 || token < 0)
		return -1;

	token_arr[td]->token += token;
	if (token_arr[td]->token > token_arr[td]->burst)
		token_arr[td]->token = token_arr[td]->burst;
	pthread_mutex_unlock(&mutex);
	return 0;
}

// 销毁
void token_destroy(int td)
{
	free(token_arr[td]);
	token_arr[td] = NULL;
}
