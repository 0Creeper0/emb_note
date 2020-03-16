#include <stdio.h>
/*
 字符串
 字符数组
 */

int main(void)
{
	char str[] = "good afternoon";
	char str2[] = {"good afternoon"};
	char str3[5] = {'g', 'o', 'o', 'd'};
	int i;

	printf("sizeof(str):%ld\n", sizeof(str));
	for (int i = 0; str[i] != '\0'; i++)
		printf("%c", str[i]);
	printf("\n");
	
	// 读入字符串
	// scanf("%s", str);
	// gets(str);
	i = 0;
	do {
		str[i] = getchar();
	} while (str[i++] != '\n' && i < 15);
	str[i-1] = '\0';

	puts(str);

	return 0;
}

