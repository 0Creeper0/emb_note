#if 0
2. 读入用户输入的字符串，统计其数字字符的个数，大写字母的个数和
小写字母的个数, 并将大写转小写，小写转大写
#endif
#include <stdio.h>

int main()
{
	int num_num , C_num, c_num;
	char str[100];
	int i;

	num_num = C_num = c_num = 0;

	printf("输入字符串:");

	i = 0;
	do {
		str[i] = getchar();
	} while (str[i++] != '\n' && i < 100);
	str[i-1] = '\0';

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 65 && str[i] <= 65 + 26)
		{
			C_num++;
			str[i] += 32;
			printf("%c", str[i]);
		}
		else if (str[i] >= 97 && str[i] <= 97 + 26)
		{
			c_num++;
			str[i] -= 32;
			printf("%c", str[i]);
		}
		else if (str[i] >= 48 && str[i] <= 57)
		{
			num_num++;
			printf("%c", str[i]);
		}
		else
			printf("%c", str[i]);
	}
	printf("\n");

	printf("数字字符个数:%d\n", num_num);
	printf("大写字母个数:%d\n", C_num);
	printf("小写字母个数:%d\n", c_num);

	return 0;
}
