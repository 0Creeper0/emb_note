#include <stdio.h>

int main()
{
	int num;

	printf("请输入一个整数:");
	scanf("%d", &num);

	if (num % 2 == 0)
		printf("偶数\n");
	else
		printf("奇数\n");

	return 0;
}
