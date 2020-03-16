#if 0
1.读入一个字符串,存储到一个char s[80]的数组中,计算此字符串的长度
#endif
#include <stdio.h>
int main()
{
	char s[80];
	int i;
	int count = 0;

	printf("输入字符串:");

	i = 0;
	do {
		s[i] = getchar();
	} while (s[i++] != '\n' && i < 80);
	s[i-1] = '\0';

	for (i = 0; s[i] != '\0'; i++)
		count++;

	printf ("%d\n", count);

	return 0;
}
