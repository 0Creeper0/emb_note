#if 0
4. 读入用户输入的字符串，长度不超过50，定义函数统计此字符串有多少个单词
(单词间用空格隔开)
#endif
#include <stdio.h>

int num_of_str(char *str);
int main()
{
	char str[50];
	int i;

	i = 0;
	do {
		str[i] = getchar();
	} while (str[i++] != '\n' && i < 50);
	str[i-1] = '\0';

	printf("%d个单词\n", num_of_str(str));

	return 0;
}

int num_of_str(char *str)
{
	int count = 0;
	while (*str != '\0')
	{
		if (((*str >= 65 && *str <= 90) || (*str >= 97 && *str <= 122)) && (*(str + 1) == ' ' || *(str + 1) == '\0'))
		{
			count ++;
			str ++;
		}
		else
			str ++;
	}
	return count;
}
