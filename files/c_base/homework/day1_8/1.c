#if 0
1. 尝试实现cal命令
通过命令查看1990.1.1是星期一，求得用户输入任意年月(90年后)对应的日历
#endif
#include <stdio.h>

// 声明
int func_year(int year);
int func_month(int year, int month);
int func_days(int year, int month);
void func_print(int year, int month);

int main()
{
	int year, month;

	do {
		printf("请输入年月(yyyy-mm):");
		scanf("%d-%d", &year, &month);
	} while (!(year >= 1990 && month >= 1 && month <= 12));

	func_print(year, month);

	return 0;
}

// 平年闰年
int func_year(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return 366;
	else
		return 365;
}

// 计算月天数
int func_month(int year, int month)
{
	int month_int[12];
	for (int i = 0; i < 12; i++)
	{
		if (i+1 == 4 || i+1 == 6 || i+1 == 9 || i+1 == 11)
			month_int[i] = 30;
		else if (i+1 == 2)
		{
			if (func_year(year) == 366)
				month_int[i] = 29;
			else
				month_int[i] = 28;
		}
		else
			month_int[i] = 31;
	}
	return month_int[month-1];
}

// 计算总天数
int func_days(int year, int month)
{
	int sum = 0;
	for (int i = 1990; i < year; i++)
	{
		sum += func_year(i);
	}
	for (int i = 1; i < month; i++)
	{
		sum += func_month(year, i);
	}
	return sum;
}

// 打印
void func_print(int year, int month)
{
	int pos, sum, day;

	day = func_month(year, month);

	printf("day:%d\n", day);
	sum = func_days(year, month);

	pos = sum % 7;

	printf ("\t\t%d年%d月\n", year, month);
	printf ("日\t一\t二\t三\t四\t五\t六\n");
	for (int i = 1; i < pos + 2; i++ )
	{
		if (pos == 6)
			break;
		printf (" \t");
	}
	
	for (int i = 1; i <= day; i++)
	{
		printf ("%d\t", i);
		if (pos % 7 == 5)
		{
			printf ("\n");
		}
		pos++;
		if (pos % 7 == 0)
			pos = 0;
		
	}
	printf("\n");
	return;
}
