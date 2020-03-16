#include <stdio.h>

/*
 局部变量 
 	函数内
	作用域:
		从定义开始到所在函数结束
	生存周期:
		从定义开始到所在函数结束
		static延长局部变量生存周期
	存储在栈区,未初始化，值随机值
		
 全局变量
 	函数体外
	作用域:
		整个进程(多文件)
		static 限制全局变量的作用域只在所在文件
	生存周期:
		从定义开始到进程结束	
	未初始化，存在bss段，值为0
	初始化，在data段
 块变量
 	语句块内 if for while...
	作用域:
		在语句块内
	生存周期:
		语句块结束

 修饰变量关键字:
 	auto  auto不能修饰全局变量
	static  静态变量
	const	保护变量	
	register 寄存器变量
	volatile 易失变量 防止编译优化
	extern
 */

int g;
static int g2; //限制此全局变量只能在本文件中使用
static void test(void);
int main(void)
{
	const int n = 100;
	register int r;
	volatile int num = 80;
	int num2 = 80;

	num2 == num2;//一定为真
	num == num; // 不一定为真	

	// printf("%p\n", &r); 寄存器变量不能取地址

	// n = 190; 只读变量

	test();
	test();
	test();
	test();
	test();

	return 0;
}

static void test(void)
{
	int var = 100;
	static int n;// 局部静态变量 未初始化存储在bss段
	static int m = 100; // .data

	var ++;
	m ++;
	printf("var:%d, m:%d\n", var, m);

	return ;
}
