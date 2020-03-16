#if 0
定义一个函数，得出字符串长度
定义一个函数，比较两个字符串大小
	printf("%d\n", *p);
#endif
#include <stdio.h>

int mystrcmp(char *s1, char *s2);
int mystrlen(char *p);

int main(void)
{
	char str1[] = "hello";
	char str2[] = "hel";
	
	printf("%d\n", mystrlen(str1));

	printf("%d\n", mystrcmp(str1, str2));

	return 0;
}

int mystrlen(char *p)	
{
	int len = 0;
	while (*p) {
		len ++;
		p++;
	}

	return len;
}

int mystrcmp(char *s1, char *s2)
{
	while (*s1 || *s2) {
		if (*s1 != *s2)	
			return *s1 - *s2;
		s1 ++;
		s2 ++;
	}
	return 0;
}


