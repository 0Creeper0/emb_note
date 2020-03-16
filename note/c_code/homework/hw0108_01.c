#include <stdio.h>

int is_leap(int y);
int day_month(int m, int y);
int main(void)
{
	int y, m;
	int sumdays = 0;
	int week, monthdays;
	char monthstr[12][20] = {"January", "February", "March", "April",\
	"May", "June", "July", "August", "September", "October", "November",\
	"December"};

	do {
		printf("你想看哪年哪月的日历(y/m):");
		scanf("%d/%d", &y, &m);
	} while (y < 1990 || m > 12 || m < 1);

	// 1990~y-1
	for (int i = 1990; i < y; i++)
		sumdays += (365+is_leap(i));
	// y.1.1~y.m-1
	for (int i = 1; i < m; i++) {
		sumdays += day_month(i, y);
	}
	// y.m.1
	sumdays += 1;
	week = sumdays % 7;	
	// printf("week:%d\n", week);

	// m月有多少天
	monthdays = day_month(m, y);

	printf("%11s %d\n", monthstr[m-1], y);
	printf("Su Mo Tu We Th Fr Sa\n");
	for (int i = 0; i < week; i++)
		printf("   ");
	for (int i = 1; i <= monthdays; i++) {
		printf("%2d%c", i, (week+i)%7?' ':'\n');
	}
	printf("\n");

	return 0;
}

// 判断给定年份是否为闰年
int is_leap(int y)
{
	return y % 4 == 0 && y % 100 != 0 || y % 400 == 0; 
}

// 计算给定的月份有多少天
int day_month(int m, int y)
{
	int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int d;

	d = days[m];
	if (m == 2 && is_leap(y))
		d ++;
		
	return d;
}



