/*
 2. 命令行第二个参数倒序存放堆
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *p = argv[1];
	char *q = NULL;

	int len = strlen(p);
	
	q = calloc(len+1, sizeof(char));

	for (int i = len - 1; i >= 0; i--)
	{
		*q = *(p + i) ;
		q++;
	}
	*q = '\0';
	puts(q);

	return 0;
}
