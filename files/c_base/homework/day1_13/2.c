#if 0
2. 定义一个函数，返回一个有1024个字节的存储空间。
再定义一个函数，将用户给定两个字符串拼接到一起存放到上述1024字节的存储空间并返回
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void *create_space();
char *mystrcat(char **space, char *str1, char *str2);
int main()
{
	char *p1 = "hello";
	char *p2 = "world";
	char *res;

	mystrcat(&res, p1, p2);

	printf("%s\n", res);

	return 0;
}

// 开辟1024字节的空间
void *create_space()
{
	char *p = malloc(1024);
	return p;
}

// 拼接用户的两个字符串
char *mystrcat(char **space, char *str1, char *str2)
{
	*space = create_space();	
	return strcat(strcat(*space, str1), str2);
}
