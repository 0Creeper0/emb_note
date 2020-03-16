#include <stdio.h>

int main(void)
{
	int sum = 0;

	for (int i = 1; i < 100; i++) {
		if (i % 4 == 0)	
			continue; // 结束本次循环 继续下一次
		sum += i;
	}

	return 0;
}

