#if 0
2. 动态开辟, 将命令行所有的参数拼接到一个连续的地址空间中(堆)
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sumstr(char **res, char *str);
int main(int argc, char *argv[])
{
	char *res = NULL;
	int num;
	for (int i = 1; argv[i] != NULL; i++)
		num = sumstr(&res, argv[i]);
	printf("string:%s\nnum:%d\n", res, num);

	return 0;
}

int sumstr(char **res, char *str)
{
	static int n = 0;

	*res = realloc(*res, (n + 1)*sizeof(char *));

	*res = strcat(*res, str);

	n ++;
	return n;
}
