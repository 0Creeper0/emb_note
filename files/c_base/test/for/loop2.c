#include <stdio.h>

int main()
{
	int date, year, month, day, count = 0, Feb;

	printf("请输入日期,如20191226 : ");
	scanf("%d", &date);

	year = date / 10000;
	month = date % 10000 / 100;
	day = date % 100;
	
	//判断输入的正确性
	if (month >= 1 && month <= 12)
	{
		if (month == 2)
		{
			if (!(day >= 1 && day <= 29))
			{
				printf("输入错误\n");
				return 1;
			}
		}
		else
		{
			if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				if (!(day >= 1 && day <= 30))
				{
					printf("日输入错误\n");
					return 1;
				}
			}
			else
			{
				if (!(day >= 1 && day <= 31))
				{
					printf("日输入错误\n");
					return 1;
				}
			}
		}
	}
	else
	{
		printf("月输入错误\n");
		return 1;
	}

	for (int i = 1; i <= month; i++)
	{
		if (i == month)
		{
			count += day;
		}
		else
		{

			if (year % 4 ==0 && year % 100 != 0 || year % 400 == 0)
				//闰年,2月29天
				Feb = 29;
			else
				//平年,2月28天
				Feb = 28;
			if (i == 4 || i == 6 || i == 9 || i == 11)
				count += 30;
			else
			{
				if (i == 2)
				{
					count += Feb;
					continue;
				}
				else
					count += 31;
			}
		}
	}
	printf("%d年%d月%d日是%d年的第%d天\n", year, month, day, year, count);

	return 0;
}


