#include <stdio.h>

// 共用体 联合体
union stu_un{
	char a;
	int b;
}var;

/*
 小端存储:高字节存在高地址，　低字节存在低地址
 大端存储:高字节存在低地址，　低字节存在高地址
 0x12345678   0x78 / 0x12
 */
int main(void)
{
	var.a = 'a';
	var.b = 100;
	printf("%p, %p\n", &var.a, &var.b);

	printf("%d %d\n", var.a, var.b);

	var.b = 0x12345678;

	if (0x12 == var.a) {
		printf("大端\n");
	} else if (var.a == 0x78) {
		printf("小端\n");
	}

	int n = 0x12345678;
	char *p = (char *)&n;
	printf("%#x\n", *p);

	return 0;
}

