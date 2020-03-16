#include <stdio.h>

int large(int, int);
int invert(int);

int main()
{
	int num1, num2;
	int num3;
	scanf("%d%d", &num1, &num2);

	printf("较大的是: %d\n", large(num1, num2));

	scanf("%d", &num3);

	printf("倒序数是: %d\n", invert(num3));
	return 0;
}

//得到两个整型变量中较大的
int large(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

//得到整型数的倒序数
int invert(int a)
{
	int b = 0;
	while(a != 0)
	{
		b = b * 10 + (a % 10);
		a /= 10;
	}
	return b;
}

