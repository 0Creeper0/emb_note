#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "alarm_timer.h"

void put_str(const char *str)
{
	write(1, str, strlen(str));
}

int main(void)
{
	int ad;

	ad = alarm_timer_init();
	if (ad == -1)
	{
		exit(1);
	}
	alarm_timer(ad, 3, put_str, "hello");

	ad = alarm_timer_init();
	if (ad == -1)
	{
		exit(1);
	}
	alarm_timer(ad, 5, put_str, "world");

	ad = alarm_timer_init();
	if (ad == -1)
	{
		exit(1);
	}
	alarm_timer(ad, 2, put_str, "hi");

	while (1)
	{
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}
