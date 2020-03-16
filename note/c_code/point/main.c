#include <stdio.h>

void swap2num(int *m, int *n);
int main(void)
{
	int a, b;
	a = 5;
	b = 9;

	swap2num(&a, &b);
	printf("a:%d, b:%d\n", a, b);

	return 0;
}

// 交换两个整型
void swap2num(int *m, int *n)
{
	int t;

	t = *m;
	*m = *n;
	*n = t;
}


