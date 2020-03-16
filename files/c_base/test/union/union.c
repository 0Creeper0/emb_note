#include <stdio.h>

union u1
{
	char a;
	int b;
}var;
// 大端存储: 低地址存高字节,	高地址存低字节
// 小端存储: 低地址存低字节,	高地址存高字节

int main()
{
	var.b = 0x12345678;
	printf("%x\n", var.a);

	return 0;
}
