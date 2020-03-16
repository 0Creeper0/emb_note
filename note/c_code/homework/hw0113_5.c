#include <stdio.h>
#include <stdlib.h>

char *toBin(int n);
int main(void)
{
	int n;

	printf("输入整型数:");
	scanf("%d", &n);
	puts(toBin(n));

	return 0;
}

char *toBin(int n)
{
	int i;
	char *res = calloc(32, 1);
	if (NULL == res)
		return NULL;

	for (int i = 0; i < 32; i++)
		res[i] = '0';

	i = 31;
	while (n) {
		res[i--] = n % 2 + '0';
		n /= 2;
	}

	return res;
}

