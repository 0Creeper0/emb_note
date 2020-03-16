#if 0
1.读入用户输入的整型数，求得其阶乘和前n项合

2.改写昨天作业第3题，用循环实现

3.读入一个整型数，判断其是否是质数
#endif

#include <stdio.h>

int main(void)
{
	int num;
	int sum = 0;
	int res = 1;
	int i;

	scanf("%d", &num);

#if 0
	for (i = 1; i <= num; i++) {
		sum += i;
		res *= i;
	}
	printf("阶乘:%d 前n项和:%d\n", res, sum);
#endif

	// 质数
	for (i = 2; i < num; i++) {
		if (num % i == 0)
			break;
	}
	if (i == num) {
		printf("%d是一个质数\n", num);
	}

	return 0;
}

