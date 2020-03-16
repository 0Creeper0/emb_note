#include <stdio.h>

// 枚举
enum {ADD=1, DEL, UPD=7, TRA}a;

int main(void)
{
	printf("%d %d %d %d\n", ADD, DEL, UPD, TRA);

	return 0;
}

