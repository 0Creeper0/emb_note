#if 0
1. 通过命令传参，实现四则运算
例如:
	./a.out 1 + 2
	计算出1+2结果
#endif
#include <stdio.h>

int add(int a, int b);
int sub(int a, int b);
int multi(int a, int b);
int div(int a, int b);
int str2int(char *str);
int main(int argc, char *argv[])
{
	int a, b;
	char symbol;

	a = str2int(argv[1]);
	b = str2int(argv[3]);
	symbol = *argv[2];
	printf("a:%d b:%d symbol:%c\n", a, b, symbol);
	if (symbol == '+')
		printf("%d\n", add(a, b));
	if (symbol == '-')
		printf("%d\n", sub(a, b));
	if (symbol == '*')
		printf("%d\n", multi(a, b));
	if (symbol == '/')
		printf("%d\n", div(a, b));

	return 0;
}

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int multi(int a, int b)
{
	return a * b;
}

int div(int a, int b)
{
	return a / b;
}

int str2int(char *str)
{
	int res = 0;
	while (*str != '\0')
	{
		res = res * 10 + (*str - '0');
		str ++;
	}
	return res;
}
