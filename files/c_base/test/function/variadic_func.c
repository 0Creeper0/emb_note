//变参函数
#include <stdio.h>

int main()
{
	volatile int n = 5; // 如果不加volatile 编译器就会进行优化
	printf("%d %d %d\n", n++, n++, n);// 优化后会变成6 5 7, 实际上应该是6 5 5,传参的时候是自右向左

	return 0;
}
