#include <stdio.h>

int main()
{
#if 0
	int num, j = 1, sum = 0;

	printf("输入一个整数:");
	scanf("%d", &num);

	for (int i = 1; i <= num; i++)
		j *= i;

	for (int i = 1; i <= num; i++)
		sum += i;

	printf("阶乘为%d	前n项和为%d\n", j, sum);
#endif

	int s = 3379;

	//while(s++%2+s%2)
	//{
	//	s++;

	for(x=0,y=10;(y>0)&&(x<4);x++,y-- )
		printf("a\n");

	printf("%d\n",(!(4)));
	printf("%d\n",(!(-4)));
	//}

	return 0;
}
