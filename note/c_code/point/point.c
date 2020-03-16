#include <stdio.h>
#if 0
指针:存储地址的变量
	定义
	赋值
	初始化

#endif

int main(void)
{
	int arr[] = {1,2,3};
	int *p;
	char *ptr = "good afternoon";
	char str[] = "good afternoon";

	// *ptr = 'm';
	str[0] = 'm';

	p = arr;

	printf("%d\n", *p);
	printf("%d\n", *(p+1));
	printf("%d\n", p[1]);
	p ++;
	printf("%d\n", *p);
	p = &arr[2];
	printf("%d\n", *p);

	return 0;
}
