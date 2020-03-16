#include <stdio.h>

void swap2int(int *a, int *b);
int len_str(char *str);
int max2str(char *str1, char *str2);
int main()
{
#if 0
	int a, b;
	a = 2;
	b = 10;

	swap2int(&a, &b);

	printf("a:%d b:%d\n", a, b);
#endif
	char str[] = {"hello"};
	char str2[] = {"hello"};
	printf("%d\n", len_str(str));

	printf("str %c str2\n", max2str(str, str2));
	return 0;
}

// 交换两个整型
void swap2int(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// 字符串长度
int len_str(char *str)
{
	int count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return count+1;

}

// 比较两个字符串大小
int max2str(char *str1, char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 > *str2)
			return '>';
		else if (*str1 < *str2)
			return '<';
		else
		{
			str1 ++;
			str2 ++;
		}
	}
	if (*str1 == '\0' && *str2 != '\0')
		return '<';
	else if (*str1 != '\0' && *str2 == '\0')
		return '>';
	else
		return '=';
}
