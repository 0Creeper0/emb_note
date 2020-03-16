#if 0
4. 读入用户输入的5个字符串，每个字符串不超过20个字节
存储到二维字符数组中，将所有字符串中最长的倒序输出
#endif
#include <stdio.h>

int main()
{
	char str[5][20];
	int j, count, index, max = 0;

	for (int i = 0; i < 5; i++)
	{
		printf("输入第%d个字符串:", i+1);
		j = 0;
		do {
			str[i][j] = getchar();
		} while (str[i][j++] != '\n' && j < 20);
		str[i][j-1] = '\0';
	}

	for (int i = 0; i < 5; i++)
	{
		count = 0;
		for (j = 0; str[i][j] != '\0'; j++)
		{
			count++;
		}
		if (count > max)
		{
			max = count;
			index = i;
		}
	}

	for (j = max; j >= 0; j--)
	{
		printf("%c", str[index][j]);
	}
	printf("\n");

	return 0;
}
