#if 0
3. 读入用户输入的字符串，将字符串按照空格切割
例如:"hello  world good"
输出
hello
world
good
#endif
#include <stdio.h>

int main()
{
	char str[100];
	int i;

	i = 0;
	do {
		str[i] = getchar();
	} while (str[i++] != '\n' && i < 100);
	str[i-1] = '\0';
	
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
			continue;
		else
		{
			printf("%c", str[i]);
			if (str[i+1] == ' ')
				printf("\n");
		}
	}
	printf("\n");

	return 0;
}
