#ifndef __ALARM_TIMER_H
#define __ALARM_TIMER_H

#define ARRSIZE 	1024
// ADT
typedef void (*timefunc_t)(const char *str);

typedef struct
{
	int second;
	timefunc_t tfunc;
	char *str;
} at_t;

// 初始化(返回ad)
int alarm_timer_init();

int alarm_timer(int ad, int second, timefunc_t tfunc, char *str);

void alarm_timer_destroy(int ad);
#endif
