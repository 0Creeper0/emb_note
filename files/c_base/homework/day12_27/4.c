#include <stdio.h>

int main()
{
	int num1, num2;

	printf ("输入两个整数:");
	scanf ("%d%d", &num1, &num2);

	if (num1 > num2)
	{
		num1 = num1 ^ num2;
		num2 = num1 ^ num2;
		num1 = num1 ^ num2;
	}

	//最大公约数
	for (int i = num1; i >= 1; i--)
	{
		if (num1 % i == 0 && num2 % i == 0)
		{
			printf ("最大公约数是%d\n", i);
			break;
		}
	}

	//最小公倍数
	for (int i = num2; ; i++)
	{
		if (i % num2 == 0 && i % num1 == 0)
		{
			printf ("最小公倍数是%d\n", i);
			break;
		}
	}

	return 0;
}

