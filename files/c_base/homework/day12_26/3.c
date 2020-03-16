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
	
	//判断平年闰年
	if (year % 4 ==0 && year % 100 != 0 || year % 400 == 0)
		//闰年,2月29天
		Feb = 29;
	else
		//平年,2月28天
		Feb = 28;

	//计算天数
	switch (month)
	{
		//1, 3, 5, 7, 8, 10, 12 => 31
		//4, 6, 9, 11 => 30
		case 1:
			count = day;
			break;
		case 2:
			count = 31 + day;
			break;
		case 3:
			count = 31 + Feb + day;
			break;
		case 4:
			count = 31 + Feb + 31 + day;
			break;
		case 5:
			count = 31 + Feb + 31 + 30 + day;
			break;
		case 6:
			count = 31 + Feb + 31 + 30 + 31 + day;
			break;
		case 7:
			count = 31 + Feb + 31 + 30 + 31 + 30 + day;
			break;
		case 8:
			count = 31 + Feb + 31 + 30 + 31 + 30 + 31 + day;
			break;
		case 9:
			count = 31 + Feb + 31 + 30 + 31 + 30 + 31 + 31 + day;
			break;
		case 10:
			count = 31 + Feb + 31 + 30 + 31 + 30 + 31 + 31 + 30 + day;
			break;
		case 11:
			count = 31 + Feb + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + day;
			break;
		case 12:
			count = 31 + Feb + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + day;
			break;
		default:
			printf("输入有误请重新输入\n");
			break;
	}
	
	printf("%d年%d月%d日是%d年的第%d天\n", year, month, day, year, count);

	return 0;
}


