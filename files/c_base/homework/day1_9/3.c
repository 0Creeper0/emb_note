#if 0
3. 定义一个函数，将给定字符串逆序输出
#endif
#include <stdio.h>

void invert_str(char *str);
int main()
{
	char str[] = {"hello"};

	invert_str(str);

	return 0;
}

void invert_str(char *str)
{
	char *first = str;
	char *last;
	while (*str != '\0')
		str ++;
	last = --str;
	while (last != first)
	{
		printf("%c", *last--);
	}
	printf("%c\n", *last);
	return;

}
