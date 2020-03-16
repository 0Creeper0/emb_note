#include <stdio.h>

int main(void)
{
	int year, month, day;
	int sumdays = 0;

	do {
		printf("请输入日期(y/m/d):");
		scanf("%d/%d/%d", &year, &month, &day);
	} while(!(year > 0 && (month > 0 && month <= 12) && (day > 0 && day <= 31)));

	sumdays = day;

#if 0
	// 1~month-1
	switch(month-1) {
		case 11:
			sumdays += 30;
		case 10:
			sumdays += 31;
		case 9:
			sumdays += 30;
		case 8:
			sumdays += 31;
		case 7:
			sumdays += 31;
		case 6:
			sumdays += 30;
		case 5:
			sumdays += 31;
		case 4:
			sumdays += 30;
		case 3:
			sumdays += 31;
		case 2:
			sumdays += (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) ? 29:28;
		case 1:
			sumdays += 31;
			break;
		default:
			break;
	}
#endif
	for (int i = 1; i < month; i++) {
		if (i == 1 || i == 3 || i == 5 || \
				i == 7 || i == 8 || i == 10 || i == 12)
			sumdays += 31;
		else if (i == 4 || i == 6 || i == 9 || i == 11)
			sumdays += 30;
		else 
			sumdays += (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) ? 29:28;
	}

	printf("%d/%d/%d是这一年的第%d天\n", year, month, day, sumdays);

	return 0;
}

