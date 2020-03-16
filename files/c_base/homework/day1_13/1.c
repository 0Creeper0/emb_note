#if 0
1. 定义一个函数，将用户给定字符串逆序并存放到堆空间中通过参数返回,函数的返回值是字符串的长度 
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int func(char *str, char **res);
int main()
{
	char *p = "hello";
	int len;
	char *res;

	len = func(p, &res);

	printf("%s\n", res);

	printf("%d\n", len);

	return 0;
}
int func(char *str, char **res)
{
	int len, i;
	char *newstr;

	len = strlen(str);

	newstr = malloc(len + 1);

	for (i = 0; i < len; i++)
	{
		newstr[i] = *(str + len - i - 1);
	}
	newstr[i] = '\0';

	*res = newstr;

	return strlen(str);

}



