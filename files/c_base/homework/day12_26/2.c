#include <stdio.h>

int main()
{
	float month;

	printf("请输入月份\n");
	scanf("%f", &month);

	if (month == 3 || month == 4 || month == 5)
		printf("春季\n");
	else if (month == 6 || month == 7 || month == 8)
		printf("夏季\n");
	else if (month == 9 || month == 10 || month == 11)
		printf("秋季\n");
	else if (month == 12 || month == 1 || month == 2)
		printf("冬季\n");
	else
		printf("输入错误,重新输入\n");
	
	return 0;
}
