#if 0
2.读入用户输入的两个字符串,分别存储到char s1[80] 和 char s2[80],
	比较这两个字符串大小
#endif
#include <stdio.h>

int main()
{
	char s1[80], s2[80];
	int i;

	printf("输入第一个字符串:");

	i = 0;
	do {
		s1[i] = getchar();
	} while (s1[i++] != '\n' && i < 80);
	s1[i-1] = '\0';

	printf("输入第二个字符串:");

	i = 0;
	do {
		s2[i] = getchar();
	} while (s2[i++] != '\n' && i < 80);
	s2[i-1] = '\0';

	for (int j = 0; j < 80; j++)
	{
		if (s1[j] > s2[j])
		{
			printf("1 > 2\n");
			break;
		}
		else if (s1[j] < s2[j])
		{
			printf("1 < 2\n");
			break;
		}
		else
		{
			if (s1[j] != '\0' && s2[j] != '\0')
				continue;
			printf("1 = 2\n");
			break;
		}
			
	}
	return 0;
}
