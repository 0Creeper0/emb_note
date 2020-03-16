#include <stdio.h>

#if 0
函数:
	定义
		返回值类型 函数名(参数列表) 
		{
			函数实现;	
		}
	声明
		返回值类型 函数名(参数列表类型);
	调用
		存储返回值的变量 = 函数名(参数值)

详谈变量:
	修饰变量关键字
	作用域和生存周期---》局部变量 全局变量

宏定义
#endif

// 声明
int sum_n(int n);
int reverse_num(int n);
int max2num(int m, int n);
int main(void)
{
	int num = 10;
	int num2 = -1;
	// 调用
	printf("%d\n", sum_n(num));

	printf("%d\n", max2num(num, num2));

	printf("%d\n", reverse_num(-8589));

	return 0;
}

// 定义
int sum_n(int n)
{
	int res = 0;

	for (int i = 1; i <= n; i++)
		res += i;

	return res;
}

// 得到两个整型变量中较大的
int max2num(int m, int n)
{
	return m > n ? m : n;
}

// 得到一个整型数的倒序数
int reverse_num(int n)
{
	int flag = 1;
	int res = 0;

	if (n == 0)
		return n;
	else if (n < 0) {
		flag = -1;
		n = -n;
	}

	while (n > 0) {
		res = res * 10 + n % 10;	
		n /= 10;
	}
	return res * flag;
}







