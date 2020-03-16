#if 0
1. 看手册strcpy(3) strcat(3) strchr(3) strstr(3)了解这些函数的功能
并实现
#endif
#include <stdio.h>

char *mystrcpy(char *dest, char *src);
char *mystrcat(char *dest, char *src);
char *mystrchr(char *s, int c);
char *mystrstr(char *haystack, char *needle);
int main()
{
	char str1[20];
	char str2[] = "hellllo";
	char str3[] = "llo";
	char *res;

	mystrcpy(str1, str2);
	printf("strcpy: %s\n", str1);

	mystrcat(str1, str2);
	printf("strcat: %s\n", str1);

	res = mystrchr(str2, 'l');
	printf("strchr: %s\n", res);

	res = mystrstr(str2, str3);
	if (res != NULL)
		printf("strstr: %s\n", res);
	else
		printf("strstr: 没有匹配\n");
	return 0;
}

// strcpy()
char *mystrcpy(char *dest, char *src)
{
	while (*src != '\0')
	{
		*dest = *src;
		dest ++;
		src ++;
	}
	*dest = '\0';
	return dest;
}

// strcat()
char *mystrcat(char *dest, char *src)
{
	// find '\0' of dest
	while (*dest != '\0')
		dest ++;
	while (*src != '\0')
	{
		*dest = *src;
		dest ++;
		src ++;
	}
	*dest = '\0';
	return dest;
}

// strchr()
char *mystrchr(char *s, int c)
{
	while (*s != c)
		s ++;
	return s;
}

// strstr()
char *mystrstr(char *haystack, char *needle)
{
	char *index_hay = NULL;
	char *index_nee;
	int flag = 0;
	while (*haystack != '\0')
	{
		if (*haystack == *needle)
		{
			index_hay = haystack; // 记录匹配开始的指针位置
			for (index_nee = needle; *index_nee != '\0'; index_nee++)
			{
				if (*haystack != *index_nee)
				{
					haystack--; // 匹配失败退回
					break;
				}
				haystack ++;
			}
			if (*index_nee == '\0')
			{
				// 匹配成功
				flag = 1;
				break;
			}
		}
		haystack ++;
			
	}
	if (!flag)
		index_hay = NULL;
	return index_hay;
}
