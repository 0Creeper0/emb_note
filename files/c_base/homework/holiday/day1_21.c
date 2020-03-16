#if 0
1. 全局变量:
	作用域:
		整个程序
	生命周期:
		程序执行的过程,程序结束时才释放
2. 局部变量:
	作用域:
		函数内部,离开函数就无效了
		语句块内部
	命名:
		不同函数或者不同语句块之间的变量命名可以重复,互不干扰
	生命周期:
		函数或者语句块调用过程,函数或语句块结束的时候释放
#endif

//实现字符串连接函数
#include <stdio.h>

char *mystrcat(char *dest, const char *src);
int main()
{
	char str1[30] = "happy ";
	char str2[] = "spring festival";
	char *res = NULL;

	res = mystrcat(str1, str2);

	puts(res);

	return 0;
}

char *mystrcat(char *dest, const char *src)
{
	char *res = dest;
	while (*res != '\0')
		res ++;
	while (*src != '\0')
	{
		*res = *src;
		res ++;
		src ++;
	}
	*res = '\0';
	return dest;
}
