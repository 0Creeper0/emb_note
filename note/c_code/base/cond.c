#if 0
分支语句
if (condition) {

}

if (condition) {
	
} else {

}

if (cond1) {

} else if (cond2) {

} else if (cond3) {

} else {

}

switch (表达式) {
	case 常量:
		break;
	case 常量:
		break;
		......
	default:
		break;
}
#endif

#include <stdio.h>

int main(void)
{
#if 0
	int num;

	scanf("%d", &num);

	if (num >= 0) {
		printf("%d是一个正数\n", num);
	} else {
		printf("%d是一个负数\n", num);
	}
#endif
	int year;

	do {
		printf("请输入年份:");
		scanf("%d", &year);
	} while (year < 0);

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		printf("%d是闰年\n", year);
	else
		printf("%d是平年\n", year);

	return 0;
}

