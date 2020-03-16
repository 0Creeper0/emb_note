#include <stdio.h>
/*
 预处理
#include 头文件
在gcc第一个阶段预处理时展开 -E
	 第二个阶段编译		-S
	 		.c 翻译成汇编代码
	 第三个阶段汇编		-c
	 		将汇编代码汇编成机器码
	 第四个阶段链接		-o
	 		链接动态库
 */

/*
c基本类型:
	计算机按位存储,用户是按字节申请空间 1byte == 8bit
	整型:short(2) int(4) long(8) (long long)
	浮点:float double 
	字符:char(1) 'a'
		man ascii
	空类型:void
	地址类型: xxx *
	复合类型: struct union

标识符:
	变量名,函数名，类型名	
	命名规范:字母、数字、下划线组成，数字不开头,避开c关键字

c关键字:
	c语法中预留的名字
	int short .....
	if else switch
	for while do break continue
	.....

变量:
	定义: type name;  分配空间
	赋值: 左值 (变量) = 右值; 
	声明: 不分配空间
	初始化: 定义的同时赋值 type name = value;

常量:
	不能改
	1 'a' "hello"
	宏
		#define N	10

运算符:
	man operator
	算术运算符
		 * / %(模) + -  
	位运算
		<< >>
		~ & | ^
		思考：如何将一个整型数的第三位置0  
						num & ~(1u << 2)
			  如何将一个整型数的第四位置1
			  			num | (1u << 3)
	逻辑运算
		&& || !
	自增自减		
		++ --
		a+++b ++a+b
	赋值运算符
		= += -= *= /= %= <<= >>= &= ^= |=
		a += b
		a = a + b
	关系运算符
		== != > < >= <=
	特殊运算符
		&变量
		*地址
		sizeof()
		(type)
		,
	三目运算符:
		a == 0 ? 1:2
*/

int main(void)
{
#if 0
	printf("%ld\n", sizeof(short));
	printf("%ld\n", sizeof(int));
	printf("%ld\n", sizeof(long));
	printf("%ld\n", sizeof(long long));
	printf("welcome to our class\n");
#endif
#if 0
	int num;

	// 读用户的输入
	scanf("%d", &num);

	// 打印读到的数值
	printf("啊！你输入的是:%d\n", num);
#endif
	int a, b, c;

	a = 10, b = 100;
	
	c = a +++ b;

	printf("a:%d, b:%d, c:%d\n", a, b, c);
	// a 11  b 100

	c = ++a + b++;
	printf("a:%d, b:%d, c:%d\n", a, b, c);

	printf("%ld\n", sizeof(a));
	printf("%ld\n", sizeof(int));
	printf("%ld\n", sizeof a);

	int m = 10;
	float n = 1.5;
	
	a = (int)(m + n);
	printf("%d\n", a);

	a > 10 ? printf("哈哈\n") : printf("嘿嘿\n");

	// a==11 b==101 
	c = (a++, a+b, b++, a-b);
	printf("a:%d, b:%d, c:%d\n", a, b, c);

	return 0;
}

