#include <stdio.h>

int main()
{
	int pos, year, month, day, sum = 0;

	do
	{
		printf ("输入年月(yyyy-mm):");
		scanf ("%d-%d", &year, &month);
	} while (!(year > 0 && month > 0 ));

	for (int i = 1900; i < year; i++)
	{
			if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
				//闰年
				sum += 366;
			else
				//平年
				sum += 365;
	}

	for (int i = 1; i < month; i++)
	{
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
			sum += 31;
		else if (i == 4 || i == 6 || i == 9 || i == 11)
			sum += 30;
		else
		{
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
				//闰年
				sum += 29;
			else
				//平年
				sum += 28;
		}
	}
	
	// 这个月第一天是星期几 
	// 5 => 六 6 => 日 0 => 一 1 => 二
	pos = sum % 7;

	// 当月天数
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		day = 31;
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		day = 30;
	else
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			//闰年
			day = 29;
		else
			//平年
			day = 28;
	}

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

	return 0;
}

