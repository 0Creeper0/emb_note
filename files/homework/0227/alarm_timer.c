#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "alarm_timer.h"

static at_t *timer_arr[ARRSIZE] = {};
static int flag = 0;

static int get_free_pos(void)
{
	for (int i = 0; i < ARRSIZE; i++)
	{
		if (timer_arr[i] == NULL)
			return i;
	}
	return -1;
}

static void sig_handler(int s)
{
	alarm(1);
	for (int i = 0; i < ARRSIZE; i++)
	{
		if (timer_arr[i] != NULL)
		{
			timer_arr[i]->second --;
			if (timer_arr[i]->second == 0)
				if (timer_arr[i]->tfunc != NULL)
					(timer_arr[i]->tfunc)(timer_arr[i]->str);
		}
	}
}

static void getting_start(void)
{
	signal(SIGALRM, sig_handler);
	alarm(1);
}

// 初始化(返回ad)
int alarm_timer_init()
{
	at_t *t;
	int pos;

	t = malloc(sizeof(timer_t));
	if (NULL == t)
	{
		fprintf(stderr, "malloc() failed\n");
		return -1;
	}

	t->second = 0;
	t->tfunc = NULL;
	t->str = NULL;

	pos = get_free_pos();
	if (pos == -1)
	{
		fprintf(stderr, "no free memery\n");
		free(t);
		return -1;
	}

	if (flag == 0)
	{
		getting_start();
		flag = 1;
	}
	timer_arr[pos] = t;

	return pos;
}

int alarm_timer(int ad, int second, timefunc_t tfunc, char *str)
{
	if (ad < 0 || second < 0)
		return -1;
	timer_arr[ad]->second = second;
	timer_arr[ad]->tfunc = tfunc;
	timer_arr[ad]->str = str;

	return 0;
}

void alarm_timer_destroy(int ad)
{
	free(timer_arr[ad]);
	timer_arr[ad] = NULL;
}
