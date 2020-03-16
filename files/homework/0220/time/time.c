#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFSIZE 	100

int main(int argc, char *argv[])
{
	int time_int = atoi(argv[1]);
	time_t tm;
	struct tm *tmp;
	char buf[BUFSIZE] = {};

	tm = time(NULL);

	tmp = localtime(&tm);
	if (NULL == tmp)
		return 1;

	strftime(buf, BUFSIZE, "%Y年%m月%d日", tmp);
	puts(buf);

	tmp->tm_mday += time_int;

	memset(buf, '\0', BUFSIZE);
	mktime(tmp);
	strftime(buf, BUFSIZE, "%Y年%m月%d日", tmp);

	puts(buf);

	return 0;
}
