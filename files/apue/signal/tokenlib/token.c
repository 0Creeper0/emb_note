#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


#include "token.h"

static token_t *token_arr[ARRSIZE] = {};
static int flag = 0;

static void sig_handler(int s)
{
	alarm(1);
	for (int i = 0; i < ARRSIZE; i++)
	{
		if (token_arr[i] != NULL)
		{
			token_arr[i]->token += token_arr[i]->cps;
			if (token_arr[i]->token >= token_arr[i]->burst)
				token_arr[i]->token = token_arr[i]->burst;
		}
	}
}

static void getting_start(void)
{
	signal(SIGALRM, sig_handler);
	alarm(1);
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

	if (flag == 0)
	{
		getting_start();
		flag = 1;
	}

	return pos;
}

// 取令牌
int token_get(int td, int token)
{
	int ret;

	if (td < 0 || token < 0)
		return -1;

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
	
	return ret;
}

// 还令牌
int token_put(int td, int token)
{
	if (td < 0 || token < 0)
		return -1;

	token_arr[td]->token += token;
	if (token_arr[td]->token > token_arr[td]->burst)
		token_arr[td]->token = token_arr[td]->burst;
	return 0;
}

// 销毁
void token_destroy(int td)
{
	free(token_arr[td]);
	token_arr[td] = NULL;
}
