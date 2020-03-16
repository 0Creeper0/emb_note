#include <stdio.h>

int main()
{
	int num, sum = 0;

	printf("请输入一个3位整数: ");
	scanf("%d", &num);

	//个位
	sum += (num % 10) * (num % 10) * (num % 10);
	//十位
	sum += ((num / 10) % 10) * ((num / 10) % 10) * ((num / 10) % 10);
	//百位
	sum += (num / 100) * (num / 100) * (num / 100);
	
	printf("结果为:%d\n", sum);

	return 0;
}
